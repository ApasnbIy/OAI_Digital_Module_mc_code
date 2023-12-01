#include "my_UART.h"
#include "my_GPIO.h"








void MY_USART1_UART_Init(type_uart_setting_union* uart_settings, type_gpio_config_union* gpio_conf)
{
  huart1.Instance = 					USART1;
  huart1.Init.BaudRate = 			uart_settings->settings_named.BAUD;
	switch(uart_settings->settings_named.UART_WORD_LENGH){
		case 0:
			 huart1.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		case 1:
			 huart1.Init.WordLength = UART_WORDLENGTH_8B;

//			 huart1.Init.WordLength = UART_WORDLENGTH_9B;
			break;
		
	}
	
  switch(uart_settings->settings_named.UART_STOP_BITS){
		case 0:
			 huart1.Init.StopBits = UART_STOPBITS_1;
			break;
		case 1:
			 huart1.Init.StopBits = UART_STOPBITS_2;
			break;
		
	}
  
	switch(uart_settings->settings_named.UART_PARITY){
		case 0:
			huart1.Init.Parity = UART_PARITY_NONE;
		  huart1.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		case 1:
			 huart1.Init.WordLength = UART_WORDLENGTH_9B;
			 huart1.Init.Parity = UART_PARITY_ODD;
			break;
		case 2:
			 huart1.Init.WordLength = UART_WORDLENGTH_9B;
			 huart1.Init.Parity = UART_PARITY_EVEN;
			break;
	}
	
 
  huart1.Init.Mode = 					UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = 		UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = 	UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	
	if(uart_settings->settings_named.Duplex){
		gpio_conf->conf_named.mask_config_named.gpio2 = 1;
		my_gpio_init(gpio_conf);
	}
	
}

void MY_USART2_UART_Init(type_uart_setting_union* uart_settings, type_gpio_config_union* gpio_conf)
{	

	
  huart2.Instance = 					USART2;
  huart2.Init.BaudRate = 			uart_settings->settings_named.BAUD;
	switch(uart_settings->settings_named.UART_WORD_LENGH){
		case 0:
			 huart2.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		case 1:
			 //huart2.Init.WordLength = UART_WORDLENGTH_9B;
			huart2.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		
	}
	
  switch(uart_settings->settings_named.UART_STOP_BITS){
		case 0:
			 huart2.Init.StopBits = UART_STOPBITS_1;
			break;
		case 1:
			 huart2.Init.StopBits = UART_STOPBITS_2;
			break;
		
	}
  
	switch(uart_settings->settings_named.UART_PARITY){
		case 0:
			 huart2.Init.Parity = UART_PARITY_NONE;
			 huart2.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		case 1:
			 huart2.Init.Parity = UART_PARITY_ODD;
			 huart2.Init.WordLength = UART_WORDLENGTH_9B;
			break;
		case 2:
			 huart2.Init.Parity = UART_PARITY_EVEN;
			 huart2.Init.WordLength = UART_WORDLENGTH_9B;
			break;
	}
  huart2.Init.Mode = 					UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = 		UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = 	UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	if(uart_settings->settings_named.Duplex){
		gpio_conf->conf_named.mask_config_named.gpio1 = 1;
		my_gpio_init(gpio_conf);
	}
	
}


void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings)
{
  uart_settings->settings_named.BAUD = 250000;
  uart_settings->settings_named.UART_WORD_LENGH = UART_WORDLENGTH_8B;
  uart_settings->settings_named.UART_STOP_BITS = UART_STOPBITS_1;
  uart_settings->settings_named.UART_PARITY = UART_PARITY_NONE;
	//uart_settings->settings_named.Duplex = 1;
}



