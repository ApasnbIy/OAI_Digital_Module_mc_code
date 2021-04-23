/**
  ******************************************************************************
  * @file           : vcp_time_segmentation.c
  * @version        : v1.0
  * @brief          :	надстройка над CubeMX для сегментации пакетов по времени
  *						для корректной работы необходимо:
							1. для работы vcp_uart необходимо наличие таймера настроенного на шаг 1 мкс, считающего вниз
							2. подключить следующие библиотеки в usb_cdc_if.c
								- 	#include "vcp_time_segmentation.h"
								-	#include "tim.h"
							3. объявить глобальную переменную в main.c:
								-	type_VCP_UART vcp;
							4. объявить глобальную переменную в usb_cdc_if.c:
								-	extern type_VCP_UART vcp; 			
							5. использовать следующие функции согласно их описаниюв usb_cdc_if.c (заменить весь код, кроме return):
								- vcp_uart_init
								- vcp_uart_CDC_Receive
							6. удаляем define-ы для длин APP_RX_DATA_SIZE и APP_TX_DATA_SIZE (определены в vcp_time_segmentation.h)
  * @author			: Стюф Алексей/Alexe Styuf <a-styuf@yandex.ru>
  ******************************************************************************
  */

#include "vcp_time_segmentation.h"

/**
  * @brief  инициализация vcp_uart для вызова в CDC_Init_FS()
  *		@note для корректной работы необходимо передать указатель на cube-таймер настроенного на шаг 1 мкс, считающего вниз
  * @param  vcp_uart_ptr: указатель на структуру управления vcp_uart
  * @param  timeout_us: таймаут для отделения пакетов в мкс (по умолчанию 1 мс)
  * @param  htim: таймер для работы с задержкой
	* @param  hUsbDeviceFS_ptr: USB-device, created by cube (offen is hUsbDeviceFS)
  * @retval статус ошибки
  */
int vcp_uart_init(type_VCP_UART* vcp_uart_ptr, uint32_t timeout_us, TIM_HandleTypeDef* htim, USBD_HandleTypeDef *hUsbDeviceFS_ptr)
{
	vcp_uart_ptr->htim = htim;
	vcp_uart_ptr->hUsbDeviceFS_ptr = hUsbDeviceFS_ptr;
	vcp_uart_ptr->htim->Instance->ARR = timeout_us;
	vcp_uart_ptr->timeout_us = timeout_us;
	vcp_uart_ptr->timeout_flag = 0;
	vcp_uart_ptr->initialized = 1;
	vcp_uart_ptr->rx_position = 0;
	vcp_uart_ptr->rx_size = 0;
	vcp_uart_ptr->rx_num = 0;
	vcp_uart_ptr->tx_num = 0;
	vcp_uart_ptr->tx_seq_num = 0;
	USBD_CDC_SetTxBuffer(vcp_uart_ptr->hUsbDeviceFS_ptr, vcp_uart_ptr->tx_data, 0);
	USBD_CDC_SetRxBuffer(vcp_uart_ptr->hUsbDeviceFS_ptr, vcp_uart_ptr->rx_data);
	USBD_CDC_ReceivePacket(vcp_uart_ptr->hUsbDeviceFS_ptr);
	return 0;
}

/**
  * @brief  отправка пакета
  * @param  vcp_uart_ptr: указатель на структуру управления vcp_uart
  * @param  buffer: указатель на буфер для отправки
  * @param  len: длина пакета
  
  * @retval количество отправленных данных
  */
int vcp_uart_write(type_VCP_UART* vcp_uart_ptr, uint8_t* buffer, uint32_t len)
{
	if (len > APP_TX_DATA_SIZE) {
		int offset = 0, i;
		for (i = 0; i < len/64; i++) {
			uint32_t todo = MIN(APP_TX_DATA_SIZE, len - i*64);  // определяем количество данных для отправки
			uint32_t done = vcp_uart_write(vcp_uart_ptr, (uint8_t*)buffer + offset, todo);  // отрпавляем данные и смотрим, сколько отправили
			offset += done;
			if (done != todo) {
				return offset;
			}
		}
		return len;
	}

	USBD_CDC_HandleTypeDef *pCDC = (USBD_CDC_HandleTypeDef *)vcp_uart_ptr->hUsbDeviceFS_ptr->pClassData;
	while(pCDC->TxState) { } //Wait for previous transfer

	USBD_CDC_SetTxBuffer(vcp_uart_ptr->hUsbDeviceFS_ptr, (uint8_t *)buffer, len);
	if (USBD_CDC_TransmitPacket(vcp_uart_ptr->hUsbDeviceFS_ptr) != USBD_OK)
		return 0;
	while(pCDC->TxState) { } //Wait until transfer is done
	vcp_uart_ptr->tx_num += 1;
	return len;
}

/**
  * @brief  чтение статуса работы таймера
  * @param  htim: указатель на структуру таймера, используемого для определения задержки
  * @retval запущен - 1, остановлен - 2
  */
uint8_t _timer_is_run(TIM_HandleTypeDef* htim){
	return ((htim->Instance->CR1)&0x01);
}

/**
  * @brief  чтение принятого пакета
  * @param  vcp_uart_ptr: указатель на структуру управления vcp_uart
  * @retval статус ошибки
  */
int vcp_uart_read(type_VCP_UART* vcp_uart_ptr)
{
	if (_timer_is_run(vcp_uart_ptr->htim)){
		return 0;
	}
	else{
		if (vcp_uart_ptr->rx_position){
			vcp_uart_ptr->rx_position = 0;
			return vcp_uart_ptr->rx_size;
		}
	}
	return 0;
}

/**
  * @brief  обработка прихода данных для вызова в CDC_Receive; buf и len берем из параметров CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
  * @param  vcp_uart: указатель на структуру управления vcp_uart
  * @param  buffer: указатель на приемный буфер
  * @param  len: длина пакета
  * @retval количество отправленных данных
  */
int vcp_uart_CDC_Receive(type_VCP_UART* vcp_uart_ptr, uint8_t* buf, uint32_t len)
{
	if(_timer_is_run(vcp_uart_ptr->htim))
	{
		memcpy(vcp_uart_ptr->rx_buff + vcp_uart_ptr->rx_position, buf, len);
		vcp_uart_ptr->rx_position += len;
		vcp_uart_ptr->rx_size = vcp_uart_ptr->rx_position;
	}
	else{
		memcpy(vcp_uart_ptr->rx_buff + vcp_uart_ptr->rx_position, buf, len);
		vcp_uart_ptr->rx_position = len;
		vcp_uart_ptr->rx_size = vcp_uart_ptr->rx_position;
		vcp_uart_ptr->rx_num += 1;
	}
	HAL_TIM_Base_Stop_IT(vcp_uart_ptr->htim);
	vcp_uart_ptr->htim->Instance->CNT = 0;
	HAL_TIM_Base_Start_IT(vcp_uart_ptr->htim);
	USBD_CDC_ReceivePacket(vcp_uart_ptr->hUsbDeviceFS_ptr);
	return (USBD_OK);
}
