#include "my_UART.h"



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
}

void MY_USART2_UART_Init(type_uart_setting_union* uart_settings)
{
  huart2.Instance = 					USART2;
  huart2.Init.BaudRate = 			uart_settings->settings_named.BAUD;
  huart2.Init.WordLength =		uart_settings->settings_named.WORDlenght;
  huart2.Init.StopBits = 			uart_settings->settings_named.STOPBITS;
  huart2.Init.Parity = 				uart_settings->settings_named.PARITY;
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
  uart_settings->settings_named.WORDlenght = UART_WORDLENGTH_8B;
  uart_settings->settings_named.STOPBITS = UART_STOPBITS_1;
  uart_settings->settings_named.PARITY = UART_PARITY_NONE;
}



