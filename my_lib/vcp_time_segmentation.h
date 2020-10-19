#ifndef _VCP_TIME_SEGMENTATION_H
#define _VCP_TIME_SEGMENTATION_H

#include "usbd_cdc_if.h"
#include "usbd_cdc.h"

// размер приемных и передающих пакетов
#define APP_RX_DATA_SIZE (64)
#define APP_TX_DATA_SIZE (64)

/** 
  * @brief  структура хранения всех настроек vcp_uart
  * @note   для работы vcp_uart необходимо наличие таймера настроенного на шаг 1 мкс, считающего вниз, в one-pulse режиме
  
  */
typedef struct  
{
	TIM_HandleTypeDef* htim;
	USBD_HandleTypeDef* hUsbDeviceFS_ptr;
	uint16_t timeout_us;  // время для таймаута в мкс
	uint8_t timeout_flag;
	char initialized;
	uint8_t rx_data[APP_RX_DATA_SIZE];
	uint8_t tx_data[APP_TX_DATA_SIZE];
	uint8_t rx_buff[256];
	uint8_t tx_buff[256];
  	uint32_t rx_position;
	uint32_t rx_size;
	uint32_t tx_size;
	uint32_t rx_num;
	uint32_t tx_num;
	uint8_t tx_seq_num;
}type_VCP_UART;

int vcp_uart_init(type_VCP_UART* vcp_uart_ptr, uint32_t timeout_us, TIM_HandleTypeDef* htim, USBD_HandleTypeDef *hUsbDeviceFS_ptr);
int vcp_uart_read(type_VCP_UART* vcp_uart_ptr);
int vcp_uart_write(type_VCP_UART* vcp_uart_ptr, uint8_t* buffer, uint32_t len);
int vcp_uart_CDC_Receive(type_VCP_UART* vcp_uart_ptr, uint8_t* buf, uint32_t len);
#endif
