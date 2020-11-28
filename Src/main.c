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




#pragma pack(push, 2)
type_modbus_data MB_Data;
type_VCP_UART vcp;
type_adc_data_struct mb_adc;
type_adc_settings 	 mb_adc_settings;
type_dac_data_struct mb_dac1;
type_dac_data_struct mb_dac2;
type_INA226_Snake ina_226;
union{
type_modbus_data mb_data;
type_modbus_data_named mb_data_named;
}mb_data_union;
#pragma pack(pop)


type_gpio_in_union 			mb_gpio_inputs;
type_gpio_out_union 		mb_gpio_outputs;
type_gpio_config_union	mb_gpio_config;
type_uart_transmit_struct mb_uart1_transmit;
type_uart_recive_struct 	mb_uart1_recive;
type_uart_setting_union   mb_uart1_setting;
type_uart_setting_union 	UART_settings_default;








/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HardResetUSB(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
			
void MY_USART1_UART_Init(type_uart_setting_union* uart_settings);
void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings);
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
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  HardResetUSB();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_ADC3_Init();
  MX_CAN1_Init();
  //MX_DAC_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_DMA_Init();
  MX_CAN2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USB_DEVICE_Init();
  MX_TIM6_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	volatile uint16_t len_massive[] = {sizeof(type_adc_data_struct), sizeof(mb_dac1), sizeof(mb_dac2), sizeof(mb_adc_settings), sizeof(type_gpio_out_union), sizeof(type_gpio_in_union)};
	
	MX_ADC3_Init(); // переинициализация ацп для работы с ДМА инициализацию выше нужно закомментировать
	MX_DAC_Init();	// переинициализация ацп для работы с ДМА инициализацию выше нужно закомментировать
	HAL_TIM_Base_Start(&htim5);	
	HAL_TIM_Base_Start(&htim6);	
	// ADC + UART1 default start
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&mb_adc.data, 8); 
	HAL_UART_Receive_IT(&huart1, &mb_uart1_recive.data[mb_uart1_recive.write_ptr],1);
	
  ina226_init(&ina_226.INA_226[0], &hi2c1,0x40,5); // 5 volt
	ina226_init(&ina_226.INA_226[1],&hi2c1,0x41,5); // 3.3 volt
  MY_USART_UART_struct_default_init(&UART_settings_default);
  MY_USART_UART_struct_default_init(&mb_uart1_setting);
  MY_USART_UART_struct_default_init(&mb_data_union.mb_data_named.mb_uart1_setting_struct);


	
	//modbus_struct_init_constant(&mb_data_union.mb_data);
	//memset(&mb_data_union.mb_data_named.mb_uart1_recive_struct.data, 0xFF, 0xFF);
	volatile uint16_t current_time ;
	volatile uint16_t previous_time_1;
	volatile uint16_t previous_time_2;
	//volatile uint16_t aa = sizeof(type_uart_transmit_struct);
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	current_time = 0;
	previous_time_1 = 0;
	previous_time_2 = 0;
		
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
    

	
		if(mb_data_union.mb_data_named.mb_dac1.settings_scaler!= mb_dac1.settings_scaler){ // dac1 start/stop/config
				memcpy(&mb_dac1.settings_scaler, &mb_data_union.mb_data_named.mb_dac1, sizeof(mb_dac1));
				if(mb_dac1.start == 1){	
					HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)mb_dac1.data, (sizeof(mb_dac1.data)/2), DAC_ALIGN_12B_R);  
				}
				else{
					HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
				}
		}
		
		if(mb_data_union.mb_data_named.mb_dac2.settings_scaler!= mb_dac2.settings_scaler){// dac2 start/stop/config
			memcpy(&mb_dac2, &mb_data_union.mb_data_named.mb_dac2,  sizeof(mb_dac2));
			if(mb_dac2.start == 1){
					HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)mb_dac2.data, (sizeof(mb_dac2.data)/2), DAC_ALIGN_12B_R);  
				}
				else{
					HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_2);
				}	
		}
		
		if(mb_data_union.mb_data_named.mb_adc_settings.settings_scaler!= mb_adc_settings.settings_scaler){ // adc start/stop
			memcpy(&mb_adc_settings.settings_scaler, &mb_data_union.mb_data_named.mb_adc_settings, sizeof(mb_adc_settings));
			if(mb_adc_settings.start == 1){
					HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&mb_adc.data, 8);  
				}
				else{
					HAL_ADC_Stop_DMA(&hadc3);
				}
		}
		// инициализация GPIO
		if(mb_data_union.mb_data_named.mb_gpio_config_union.conf_named.on_of_mask.update_scaler != mb_gpio_config.conf_named.on_of_mask.update_scaler){
			memcpy(&mb_gpio_config.conf_named, &mb_data_union.mb_data_named.mb_gpio_config_union, sizeof(mb_gpio_config.conf_named));
			my_gpio_init(&mb_gpio_config);
		}
		//обновление состояния GPIO настроенных на выход
		if(mb_gpio_config.conf_named.on_of_mask.init_flag){
      if(mb_data_union.mb_data_named.mb_gpio_out_union.gpio_out_named.data_updater != mb_gpio_outputs.gpio_out_named.data_updater){
        memcpy(&mb_gpio_outputs, &mb_data_union.mb_data_named.mb_gpio_out_union, sizeof(mb_gpio_outputs));
        my_gpio_set(&mb_gpio_outputs);
      }
    }
		//обновление и отправка посылки по uart1
		if(mb_data_union.mb_data_named.mb_uart1_transmit_struct.scaler != mb_uart1_transmit.scaler){
			memcpy(&mb_uart1_transmit, &mb_data_union.mb_data_named.mb_uart1_transmit_struct, sizeof(mb_uart1_transmit));
			if(mb_uart1_transmit.start == 0x01 && mb_uart1_transmit.len != 0x00){
				HAL_UART_Transmit_IT(&huart1, mb_uart1_transmit.data, mb_uart1_transmit.len);
			}
		}
		//baudrate settings for UART1
		if(mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.scaler != mb_uart1_setting.settings_named.scaler){
			memcpy(&mb_uart1_setting, &mb_data_union.mb_data_named.mb_uart1_setting_struct, sizeof(type_uart_setting_union));
			if(mb_uart1_setting.settings_named.BAUD!=0){
				MY_USART1_UART_Init(&mb_uart1_setting);
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.flag = 0x01;
			}
			else{
				MY_USART1_UART_Init(&UART_settings_default);
				mb_data_union.mb_data_named.mb_uart1_setting_struct.settings_named.flag = 0x08;	
			}
		}
		
		
		
		
		
		
		
		
		
		
				
		if(vcp.rx_position>4){
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
		mb_uart1_transmit.transmit_flag = 0x01;
		USART1->SR; // неявный сброс прерывания
		USART1->DR;
	}
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1){
			mb_uart1_recive.write_ptr++;
			if(mb_uart1_recive.write_ptr == (UART_RECIVE_DATA_BUFF)){
				mb_uart1_recive.write_ptr = 0;
			}
			HAL_UART_Receive_IT(&huart1, &mb_uart1_recive.data[mb_uart1_recive.write_ptr],1);
		
	}
}

void MY_USART1_UART_Init(type_uart_setting_union* uart_settings)
{

  huart1.Instance = 					USART1;
  huart1.Init.BaudRate = 			uart_settings->settings_named.BAUD;
  huart1.Init.WordLength =		uart_settings->settings_named.WORDlenght;
  huart1.Init.StopBits = 			uart_settings->settings_named.STOPBITS;
  huart1.Init.Parity = 				uart_settings->settings_named.PARITY;
  huart1.Init.Mode = 					UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = 		UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = 	UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	HAL_UART_Receive_IT(&huart1, &mb_uart1_recive.data[mb_uart1_recive.write_ptr],1);
}
void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings)
{
  uart_settings->settings_named.BAUD = 115200;
  uart_settings->settings_named.WORDlenght = UART_WORDLENGTH_8B;
  uart_settings->settings_named.STOPBITS = UART_STOPBITS_1;
  uart_settings->settings_named.PARITY = UART_PARITY_NONE;
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
