/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stm32f4xx.h>


#include "vcp_time_segmentation.h"
#include "modbus_rtu.h"
#include "math.h"
#include "modbus_data_formater.h"
#include "INA226.h"
#include "my_GPIO.h"
#include "my_UART.h"
#include "my_SPI.h"
#include "led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//type_VCP_UART vcp;

#define ADC_DATA_LAST_ADDRESS 0
#define DAC_DATA_LAST_ADDRESS 1








type_VCP_UART vcp;

#pragma pack(push, 2)
type_modbus_data MB_Data;

type_adc_data_struct mb_adc;
type_adc_settings 	 mb_adc_settings;
type_dac_data_struct mb_dac1;
type_dac_data_struct mb_dac2;
type_INA226_Snake ina_226;

union{
type_modbus_data mb_data;
type_modbus_data_named mb_data_named;
}mb_data_union;

type_uart_transmit_struct mb_uart1_transmit;
type_uart_setting_union   mb_uart1_setting;
type_uart_transmit_struct mb_uart2_transmit;
type_uart_setting_union   mb_uart2_setting;
type_uart_setting_union 	UART_settings_default;
type_spi_settings_struct					mb_spi_settings;
type_spi_transmit_struct					mb_spi_transmit;
type_spi_receive_struct						mb_spi_receive;

#pragma pack(pop)
type_LED_INDICATOR mcu_state_led;
type_LED_INDICATOR con_state_led;



type_gpio_in_union 			mb_gpio_inputs;
type_gpio_out_union 		mb_gpio_outputs;
type_gpio_config_union	mb_gpio_config;
type_alternative_gpio_out_struct mb_gpio_alternative_outputs;
uint8_t timer_slot_5ms_counter = 0;
uint8_t time_slot_flag_5ms = 0;

	







/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HardResetUSB(void);
void Reverse_Bytes_Order_16(uint16_t* word);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
			
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	 
	 
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	HardResetUSB();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
	

  /* USER CODE BEGIN SysInit */
	
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_ADC3_Init();
  MX_CAN1_Init();
  //MX_DAC_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_DMA_Init();
  MX_CAN2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USB_DEVICE_Init();
  MX_TIM6_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_TIM7_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
	//volatile uint16_t len_massive[] = {sizeof(type_adc_data_struct), sizeof(type_ina_226_data ), sizeof(type_uart_receive_struct), sizeof(type_gpio_in_union),sizeof(type_spi_receive_data),sizeof(type_uart_receive_struct)};
	/*
	type_adc_data_struct 			
	type_ina_226_data					
	type_ina_226_data					
	type_uart_receive_struct	
	type_uart_receive_struct 	
	type_gpio_in_union				
	type_spi_receive_data			
	*/
	
	
	//my_gpio_init(&mb_gpio_config);
	memset(&mb_data_union, 0, sizeof(mb_data_union));
	HAL_TIM_Base_Start(&htim8);	// таймер ModBus
	
	
	
	MX_ADC3_Init(); // переинициализация ацп для работы с ДМА инициализацию выше нужно закомментировать
	MX_DAC_Init();	// переинициализация ацп для работы с ДМА инициализацию выше нужно закомментировать
	HAL_TIM_Base_Start(&htim5); //таймер АЦП, INA	
	
	HAL_TIM_Base_Start_IT(&htim7);	//таймер светодиоды
	
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&mb_adc.data, 8); 
	HAL_UART_Receive_IT(&huart1, &mb_data_union.mb_data_named.mb_uart1_receive_struct.data[mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr],1);
	HAL_UART_Receive_IT(&huart2, &mb_data_union.mb_data_named.mb_uart2_receive_struct.data[mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr],1);
	
	ina226_init(&ina_226.INA_226[0], &hi2c1,0x40,5); // 5 volt
	ina226_init(&ina_226.INA_226[1],&hi2c1,0x41,5); // 3.3 volt

	MY_USART_UART_struct_default_init(&UART_settings_default);
	MY_USART_UART_struct_default_init(&mb_uart1_setting);
	MY_USART_UART_struct_default_init(&mb_data_union.mb_data_named.mb_uart1_setting_struct);
	MY_USART_UART_struct_default_init(&mb_uart2_setting);
	MY_USART_UART_struct_default_init(&mb_data_union.mb_data_named.mb_uart2_setting_struct);
	
	my_spi_default_settings(&mb_spi_settings);
	my_spi_default_settings(&mb_data_union.mb_data_named.mb_spi_settings);
		
	//modbus_struct_init_constant(&mb_data_union.mb_data);
	//memset(&mb_data_union.mb_data_named.mb_uart1_recive_struct.data, 0xFF, 0xFF);
	volatile uint16_t current_time ;
	volatile uint16_t previous_time_1;
	volatile uint16_t previous_time_2;
	led_init(&mcu_state_led, 0);
	led_init(&con_state_led, 1);
	led_setup(&con_state_led, LED_ON, 0, 0);
	led_setup(&mcu_state_led, LED_HEART_BEAT, 1000, 0);
	led_alt_setup(&con_state_led, LED_BLINK, 200, 127, 2000);
	led_alt_setup(&mcu_state_led, LED_BLINK, 200, 127, 2000);
	current_time = 0;
	previous_time_1 = 0;
	previous_time_2 = 0;
	timer_slot_5ms_counter = 0;
	uint32_t temp;
	
	
	
	/*
	ina226_snake(&ina_226);
	*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		current_time = (uint16_t)TIM5->CNT;
		
		if((current_time - previous_time_1)>= 400){ // запуск опроса ina226. копирование данных ацп
        memcpy(&mb_data_union.mb_data_named.mb_adc.data, &mb_adc.data, sizeof(mb_adc.data));
				
			  if(mb_gpio_alternative_outputs.start == 1 && mb_gpio_alternative_outputs.end_flag == 0){ // if alt started
					temp = ((uint32_t)(TIM2->ARR)) - ((uint32_t) TIM2->CNT);
					memcpy(&mb_data_union.mb_data_named.mb_gpio_alternative_out.LOW_time_left, &temp, 4); // update the time in alt_gpio
				}
				
				if(ina_226.ch_read_queue == 0){memcpy(&mb_data_union.mb_data_named.ina226_5v, &ina_226.INA_226[0].voltage, sizeof(type_ina_226_data));}
				else if(ina_226.ch_read_queue == 1){memcpy(&mb_data_union.mb_data_named.ina226_3v3, &ina_226.INA_226[1].voltage, sizeof(type_ina_226_data));}
   			
				ina226_snake(&ina_226); 
				previous_time_1 = current_time;				
		}
		if((current_time - previous_time_2)>=800){	// обновление состояния GPIO 
      if(mb_gpio_config.conf_named.on_of_mask.init_flag){
        my_gpio_get(&mb_gpio_inputs);
        memcpy(&mb_data_union.mb_data_named.mb_gpio_in_union, &mb_gpio_inputs, sizeof(mb_gpio_inputs));
      }
      previous_time_2 = 0;
      previous_time_1 = 0;
			current_time = 0;
			TIM5->CNT = 0;
    }
    

	
		if(mb_data_union.mb_data_named.mb_dac1.settings_scaler == 1){ // dac1 start/stop/config
				memcpy(&mb_dac1.settings_scaler, &mb_data_union.mb_data_named.mb_dac1, sizeof(mb_dac1));
				if(mb_dac1.start == 1){					
					HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)mb_dac1.data, (sizeof(mb_dac1.data)/2), DAC_ALIGN_12B_R);  
					mb_data_union.mb_data_named.mb_dac1.settings_scaler = 0;
				}
				else{
					HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
					mb_data_union.mb_data_named.mb_dac1.settings_scaler = 0;
				}
		}
		
		if(mb_data_union.mb_data_named.mb_dac2.settings_scaler == 1){// dac2 start/stop/config
			memcpy(&mb_dac2, &mb_data_union.mb_data_named.mb_dac2,  sizeof(mb_dac2));
			if(mb_dac2.start == 1){
					HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)mb_dac2.data, (sizeof(mb_dac2.data)/2), DAC_ALIGN_12B_R);  
					mb_data_union.mb_data_named.mb_dac2.settings_scaler = 0;
				}
				else{
					HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_2);
					mb_data_union.mb_data_named.mb_dac2.settings_scaler = 0;
				}	
		}
		
		if(mb_data_union.mb_data_named.mb_adc_settings.settings_scaler == 1){ // adc start/stop
			memcpy(&mb_adc_settings.settings_scaler, &mb_data_union.mb_data_named.mb_adc_settings, sizeof(mb_adc_settings));
			if(mb_adc_settings.start == 1){
					HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&mb_adc.data, 8);
					mb_data_union.mb_data_named.mb_adc_settings.settings_scaler = 0;				
				}
				else{
					HAL_ADC_Stop_DMA(&hadc3);
					mb_data_union.mb_data_named.mb_adc_settings.settings_scaler = 0;
				}
		}
		// инициализация GPIO
		if(mb_data_union.mb_data_named.mb_gpio_config_union.conf_named.mask_config_named.data_updater == 1){
			memcpy(&mb_gpio_config.conf_named, &mb_data_union.mb_data_named.mb_gpio_config_union, sizeof(mb_gpio_config.conf_named));
			my_gpio_init(&mb_gpio_config);
			mb_data_union.mb_data_named.mb_gpio_config_union.conf_named.mask_config_named.data_updater = 0;
			
		}
		//обновление состояния GPIO настроенных на выход
		if(mb_gpio_config.conf_named.on_of_mask.init_flag){
      if(mb_data_union.mb_data_named.mb_gpio_out_union.gpio_out_named.data_updater == 1){
        memcpy(&mb_gpio_outputs, &mb_data_union.mb_data_named.mb_gpio_out_union, sizeof(mb_gpio_outputs));
        my_gpio_set(&mb_gpio_outputs);
				mb_data_union.mb_data_named.mb_gpio_out_union.gpio_out_named.data_updater = 0;
      }
    }
		//обновление и отправка посылки по uart1
		if(mb_data_union.mb_data_named.mb_uart1_transmit_struct.scaler == 1){
			memcpy(&mb_uart1_transmit, &mb_data_union.mb_data_named.mb_uart1_transmit_struct, sizeof(mb_uart1_transmit));
			if(mb_uart1_transmit.start == 0x01 && mb_uart1_transmit.len != 0x00){
				mb_data_union.mb_data_named.mb_uart1_transmit_struct.transmit_flag = 0x0000;
				mb_uart1_transmit.transmit_flag = 0x0000;
				if(mb_uart1_transmit.len < UART_TRANSMIT_DATA_BUFF){
					for(int i = 0; i<= mb_uart1_transmit.len; i++){ 
						Reverse_Bytes_Order_16(&mb_uart1_transmit.data[i]);
					}
					HAL_UART_Transmit_IT(&huart1, (uint8_t*) mb_uart1_transmit.data, mb_uart1_transmit.len);
					mb_data_union.mb_data_named.mb_uart1_transmit_struct.scaler = 0;
				}
				else{
					mb_uart1_transmit.transmit_flag = 0xFF00;
					mb_data_union.mb_data_named.mb_uart1_transmit_struct.scaler = 0;
				}

			}
		}
		//Настройки ЮАРТ1, из простого, менять баудрэйт, при изменении настроек заново запускается буфер на прием
		if(mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.scaler == 1){
			memcpy(&mb_uart1_setting, &mb_data_union.mb_data_named.mb_uart1_setting_struct, sizeof(type_uart_setting_union));
			if(mb_uart1_setting.settings_named.BAUD!=0){
				HAL_UART_Abort_IT(&huart1);
				MY_USART1_UART_Init(&mb_uart1_setting);
				mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr = 0x00;
				memset(&mb_data_union.mb_data_named.mb_uart1_receive_struct.data, 0x00, sizeof(mb_data_union.mb_data_named.mb_uart1_receive_struct.data));
				HAL_UART_Receive_IT(&huart1, &mb_data_union.mb_data_named.mb_uart1_receive_struct.data[mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr],1);
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.flag = 0x01;
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.scaler =0;
			}
			else{
				HAL_UART_Abort_IT(&huart1);
				MY_USART1_UART_Init(&UART_settings_default);
				mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr = 0x00;
				memset(&mb_data_union.mb_data_named.mb_uart1_receive_struct.data, 0x00, sizeof(mb_data_union.mb_data_named.mb_uart1_receive_struct.data));
				HAL_UART_Receive_IT(&huart1, &mb_data_union.mb_data_named.mb_uart1_receive_struct.data[mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr],1);
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.flag = 0x10;
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.scaler =0;				
			}
		}
		
		//обновление и отправка посылки по uart2
		if(mb_data_union.mb_data_named.mb_uart2_transmit_struct.scaler == 1){
			memcpy(&mb_uart2_transmit, &mb_data_union.mb_data_named.mb_uart2_transmit_struct, sizeof(mb_uart2_transmit));
			if(mb_uart2_transmit.start == 0x01 && mb_uart2_transmit.len != 0x00){
				mb_data_union.mb_data_named.mb_uart2_transmit_struct.transmit_flag = 0x0000;
				mb_uart2_transmit.transmit_flag = 0x0000;
				mb_data_union.mb_data_named.mb_uart2_transmit_struct.scaler = 2;
				if(mb_uart2_transmit.len < UART_TRANSMIT_DATA_BUFF){
					for(int i = 0; i<= mb_uart2_transmit.len; i++){ 
						Reverse_Bytes_Order_16(&mb_uart2_transmit.data[i]);
					}
					HAL_UART_Transmit_IT(&huart2, (uint8_t*) mb_uart2_transmit.data, mb_uart2_transmit.len);
					mb_data_union.mb_data_named.mb_uart2_transmit_struct.scaler = 0;
				}
				else{
					mb_uart2_transmit.transmit_flag = 0xFF00;
					mb_data_union.mb_data_named.mb_uart2_transmit_struct.scaler = 0;
				}
			}
		}
		//Настройки ЮАРТ2, из простого, менять баудрэйт, при изменении настроек заново запускается буфер на прием
		if(mb_data_union.mb_data_named.mb_uart2_setting_struct.settings_named.scaler != mb_uart2_setting.settings_named.scaler){
			memcpy(&mb_uart2_setting, &mb_data_union.mb_data_named.mb_uart2_setting_struct, sizeof(type_uart_setting_union));
			if(mb_uart2_setting.settings_named.BAUD!=0){
				HAL_UART_Abort_IT(&huart2);
				MY_USART2_UART_Init(&mb_uart2_setting);
				mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr = 0x00;
				memset(&mb_data_union.mb_data_named.mb_uart2_receive_struct.data, 0x00, sizeof(mb_data_union.mb_data_named.mb_uart2_receive_struct.data));
				HAL_UART_Receive_IT(&huart2, &mb_data_union.mb_data_named.mb_uart2_receive_struct.data[mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr],1);
				mb_data_union.mb_data_named.mb_uart2_setting_struct.settings_named.flag = 0x01;
				mb_data_union.mb_data_named.mb_uart2_setting_struct.settings_named.scaler = 0;	
			}
			else{
				HAL_UART_Abort_IT(&huart2);
				MY_USART2_UART_Init(&UART_settings_default);
				mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr = 0x00;
				memset(&mb_data_union.mb_data_named.mb_uart2_receive_struct.data, 0x00, sizeof(mb_data_union.mb_data_named.mb_uart2_receive_struct.data));
				HAL_UART_Receive_IT(&huart2, &mb_data_union.mb_data_named.mb_uart2_receive_struct.data[mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr],1);
				mb_data_union.mb_data_named.mb_uart2_setting_struct.settings_named.flag = 0x01;	
				mb_data_union.mb_data_named.mb_uart2_setting_struct.settings_named.scaler =0;	
			}
		}
		
		// alternative GPIO set
		if(mb_data_union.mb_data_named.mb_gpio_alternative_out.scaler ==  1){
				memcpy(&mb_gpio_alternative_outputs, &mb_data_union.mb_data_named.mb_gpio_alternative_out, sizeof(mb_gpio_alternative_outputs));
				if(mb_gpio_alternative_outputs.start == 0x0001 && mb_gpio_alternative_outputs.stop == 0x00){
					mb_gpio_alternative_outputs.end_flag = 0;
					my_gpio_alt_set(&mb_gpio_alternative_outputs);
					mb_data_union.mb_data_named.mb_gpio_alternative_out.scaler = 0;
				}
				else if(mb_gpio_alternative_outputs.stop == 0x0001){
					HAL_TIM_Base_Stop_IT(&htim2);
					mb_gpio_alternative_outputs.end_flag = 0;
					mb_gpio_alternative_outputs.start = 0;
					my_gpio_set(&mb_gpio_outputs);
					mb_data_union.mb_data_named.mb_gpio_alternative_out.scaler = 0;
				}
		}
		
		// spi transmit
		if(mb_data_union.mb_data_named.mb_spi_transmit.scaler == 1){
			memcpy(&mb_spi_transmit, &mb_data_union.mb_data_named.mb_spi_transmit, sizeof(type_spi_settings_struct));
			if(mb_spi_transmit.start == 1){
				mb_data_union.mb_data_named.mb_spi_transmit.transaction_end = 0;
				if(mb_spi_transmit.rx_tx_flag == 1){
					my_spi_transmit_recive( &mb_data_union.mb_data_named.mb_spi_receive_data, &mb_spi_transmit);
				}
				else if(mb_spi_transmit.rx_tx_flag == 0){
					my_spi_transmit(&mb_spi_transmit);
				}
			}
			mb_data_union.mb_data_named.mb_spi_transmit.scaler = 0;
		}
		//spi receive
		if(mb_data_union.mb_data_named.mb_spi_receive.scaler != mb_spi_receive.scaler){
			memcpy(&mb_spi_receive, &mb_data_union.mb_data_named.mb_spi_receive, 20); // 20 bites are control part of struct
			if(mb_spi_receive.start == 1){
				mb_data_union.mb_data_named.mb_spi_receive.transaction_end = 0;
				my_spi_receive(&mb_spi_receive ,&mb_data_union.mb_data_named.mb_spi_receive_data);
			}
		}
		//spi settings
		if(mb_data_union.mb_data_named.mb_spi_settings.scaler != mb_spi_settings.scaler){
			memcpy(&mb_spi_settings, &mb_data_union.mb_data_named.mb_spi_settings, sizeof(type_spi_settings_struct));
			if(mb_spi_settings.set_default == 0x01){
				my_spi_default_settings(&mb_spi_settings);
				MY_SPI2_Init(&mb_spi_settings);
			}
			else{
				MY_SPI2_Init(&mb_spi_settings);
			}
				
		}
			
		



						
		if(vcp.rx_position>4){
			led_alt_setup(&con_state_led, LED_BLINK, 200, 127, 200);
			modbus_RX_TX_handler(&mb_data_union.mb_data, &vcp);
		}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
}

/* USER CODE BEGIN 4 */

void HardResetUSB(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init (GPIOA, & GPIO_InitStruct);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_Delay (1000);
  
}

void Reverse_Bytes_Order_16(uint16_t* word){
	volatile uint16_t temp; 
	temp = *word;  			// berem snachenie po ukasately
	temp = ((temp<<8)&0xFF00)| ((temp>>8)&0xFF); // delaem vsiakie nepotrebnocty
	*word = temp;									// sapisivaem obratno chto poluchilos
}
	



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC3)
    {
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == &hi2c1){
		ina226_body_read_queue(&ina_226.INA_226[ina_226.ch_read_queue]);
	}
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == &hi2c1){
		ina226_body_read_queue(&ina_226.INA_226[ina_226.ch_read_queue]);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1){
		//mb_uart_transmit.transmit_flag = 1;
		mb_data_union.mb_data_named.mb_uart1_transmit_struct.transmit_flag = 0x01;
		mb_data_union.mb_data_named.mb_uart1_transmit_struct.start = 0x0;
		mb_uart1_transmit.transmit_flag = 0x01;
		HAL_UART_AbortTransmit_IT(&huart1);
	}
	else if(huart == &huart2){
		//mb_uart_transmit.transmit_flag = 1;
		mb_data_union.mb_data_named.mb_uart2_transmit_struct.transmit_flag = 0x01;
		mb_data_union.mb_data_named.mb_uart2_transmit_struct.start = 0x0;
		mb_uart2_transmit.transmit_flag = 0x01;
		HAL_UART_AbortTransmit_IT(&huart2);
	}	
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1){
			mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr++;
			if(mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr == (UART_RECIVE_DATA_BUFF)){
				mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr = 0;
			}
			HAL_UART_Receive_IT(&huart1, &mb_data_union.mb_data_named.mb_uart1_receive_struct.data[mb_data_union.mb_data_named.mb_uart1_receive_struct.write_ptr],1);
		
	}
	else if(huart == &huart2){
			mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr++;
			if(mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr == (UART_RECIVE_DATA_BUFF)){
				mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr = 0;
			}
			HAL_UART_Receive_IT(&huart2, &mb_data_union.mb_data_named.mb_uart2_receive_struct.data[mb_data_union.mb_data_named.mb_uart2_receive_struct.write_ptr],1);
		
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim7) {
    timer_slot_5ms_counter += 1;
    if (timer_slot_5ms_counter >= 2){ //создание искусственного события c периодом 10 мс
      timer_slot_5ms_counter = 0;
    }
    led_processor(&mcu_state_led, 5);
    led_processor(&con_state_led, 5);
		time_slot_flag_5ms = 5;
	}
	
	if(htim == &htim2){
		//HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
			if(mb_gpio_alternative_outputs.it_scaler == 0){
				mb_gpio_alternative_outputs.it_scaler = 1;
			}
			else if(mb_gpio_alternative_outputs.it_scaler == 1){
				my_gpio_set(&mb_gpio_outputs);
				mb_gpio_alternative_outputs.end_flag = 0x0001;
				mb_gpio_alternative_outputs.start = 0x0000;
				HAL_TIM_Base_Stop_IT(&htim2);	
				//TIM2->CNT = 0x0;	
			
			}
		}
	}

	
	
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi2)
  {
    if(hspi2.TxXferCount==0)
    {
      HAL_SPI_Abort_IT(&hspi2);
			mb_data_union.mb_data_named.mb_spi_transmit.transaction_end = 1;
			mb_data_union.mb_data_named.mb_spi_transmit.start = 0;
    }
  }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi2)
  {
    if(hspi2.TxXferCount==0 && hspi2.TxXferCount==0)
    {
      HAL_SPI_Abort_IT(&hspi2);
			mb_data_union.mb_data_named.mb_spi_transmit.transaction_end = 1;
			mb_data_union.mb_data_named.mb_spi_transmit.start = 0;
			mb_data_union.mb_data_named.mb_spi_receive.transaction_end = 1;
			mb_data_union.mb_data_named.mb_spi_receive.start = 0;
    }
  }
}
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi2)
  {
    if(hspi2.RxXferCount==0)
    {
      HAL_SPI_Abort_IT(&hspi2);
			mb_data_union.mb_data_named.mb_spi_receive.transaction_end = 1;
			mb_data_union.mb_data_named.mb_spi_receive.start = 0;
    }
  }
}
	
	
	
	

/* USER CODE BEGIN 0 */




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
