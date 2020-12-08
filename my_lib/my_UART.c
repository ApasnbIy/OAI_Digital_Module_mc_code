#include "my_UART.h"









void MY_USART1_UART_Init(type_uart_setting_union* uart_settings)
{
  huart1.Instance = 					USART1;
  huart1.Init.BaudRate = 			uart_settings->settings_named.BAUD;
	switch(uart_settings->settings_named.UART_WORD_LENGH){
		case 0:
			 huart1.Init.WordLength = UART_WORDLENGTH_8B;
			break;
		case 1:
			 huart1.Init.WordLength = UART_WORDLENGTH_9B;
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
			break;
		case 1:
			 huart1.Init.Parity = UART_PARITY_EVEN;
			break;
		case 2:
			 huart1.Init.Parity = UART_PARITY_ODD;
			break;
	}
 
 
  huart1.Init.Mode = 					UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = 		UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = 	UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

void MY_USART2_UART_Init(type_uart_setting_union* uart_settings)
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
			break;
		case 1:
			 huart2.Init.Parity = UART_PARITY_EVEN;
			break;
		case 2:
			 huart2.Init.Parity = UART_PARITY_ODD;
			break;
	}
  huart2.Init.Mode = 					UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = 		UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = 	UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}


void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings)
{
  uart_settings->settings_named.BAUD = 115200;
  uart_settings->settings_named.UART_WORD_LENGH = UART_WORDLENGTH_8B;
  uart_settings->settings_named.UART_STOP_BITS = UART_STOPBITS_1;
  uart_settings->settings_named.UART_PARITY = UART_PARITY_NONE;
}



