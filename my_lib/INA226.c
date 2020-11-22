/**
  ******************************************************************************
  * @file           : ina226.c
  * @version        : v1.0
  * @brief          : надстройка над CubeMX для удобного управления INA226 через I2C
  * @author			: Стюф Алексей/Alexe Styuf <a-styuf@yandex.ru>
  ******************************************************************************
  */

#include "INA226.h"

/**
  * @brief  инициализация работы с INA226: специально использую блокирующий режим
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @param  addr: адрес INA226
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
uint8_t ina226_init(type_INA226_DEVICE* ina226_ptr, I2C_HandleTypeDef* i2c_ptr, uint8_t addr, uint16_t power_lim_Wt)
{
	uint8_t i2c_rx_data[16] = {0}, validate_data[16] = {0};
	uint8_t i2c_tr_data[8] = {0};
	uint16_t i2c_reg_val = 0;
	//создаем структуру
	ina226_ptr->addr = addr;
	ina226_ptr->i2c_ptr = i2c_ptr;
	ina226_ptr->voltage = 0;
	ina226_ptr->current = 0;
	ina226_ptr->power = 0;
	ina226_ptr->queue_state = 0;
	ina226_ptr->error_cnt = 0;
	memset(ina226_ptr->validate_data, 0x00, 8);
	// устанавливаем режим работы
	i2c_reg_val = (1 << 14)| (AVEREGES_DEF<<9) | (CONV_TIME_DEF<<6) | (CONV_TIME_DEF<<3) | (MODE_DEF<<0);
	i2c_tr_data[0] = CONFIG_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data, 2, 100);
	// устанавливаем калибровки
	i2c_reg_val = CAL_VAL;
	i2c_tr_data[0] = CAL_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+2, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+2, 2, 100);
	// устанавливаем ограничение по мощности
	i2c_reg_val = POWER_KOEFF_FROM_WT_TO_ADC*power_lim_Wt;
	i2c_tr_data[0] = ALERT_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+4, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+4, 2, 100);
	// устанавливаем тип alert
	i2c_reg_val = ALERT_MODE_DEF;
	i2c_tr_data[0] = MODE_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+6, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+6, 2, 100);
	//
	i2c_tr_data[0] = MANUFACTURED_ID_REG_ADDR;
	i2c_reg_val = 0x4954;
	memcpy(validate_data+8, (uint8_t*)&i2c_reg_val, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 1, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+8, 2, 100);
	//
	i2c_tr_data[0] = DIE_ID_REG_ADDR;
	i2c_reg_val = 0x6022;
	memcpy(validate_data+10, (uint8_t*)&i2c_reg_val, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 1, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+10, 2, 100);
	//
	memcpy(ina226_ptr->validate_data, i2c_rx_data, 16);
	// проверка на привильность записи
	if (memcmp((uint8_t*)i2c_rx_data, (uint8_t*)validate_data, 16) == 0){
		return 1;
	}
	return 0;
}

/**
  * @brief  проверка связи с INA226
  * @param  ina226_ptr: структура CubeMX для управления INA226
  */
uint8_t ina226_check(type_INA226_DEVICE* ina226_ptr)
{
	uint8_t reg_addr = 0xFE;
	uint8_t i2c_rx_data[16] = {0};
	HAL_I2C_Master_Transmit(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, &reg_addr, 1, 100);
	HAL_I2C_Master_Receive(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, i2c_rx_data, 2, 100);
	if (i2c_rx_data[0] == 'T' && i2c_rx_data[1] == 'I')
	{
		return 1;
	}
	return 0;
}

/**
  * @brief  установка адреса подадреса INA226 для работы в режиме с прерыванием
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @param  reg_addr: адрес INA226
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
uint16_t ina226_reg_addr_set(type_INA226_DEVICE* ina226_ptr, uint8_t reg_addr)
{
	
	ina226_ptr->tx_data[0]  = reg_addr;
	ina226_ptr->rx_reg_addr = reg_addr;
	HAL_I2C_Master_Transmit_IT(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, ina226_ptr->tx_data, 1);
	return 0;
}

/**
  * @brief  запрос данных из INA226 для работы в режиме с прерыванием
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
uint16_t ina226_read_request(type_INA226_DEVICE* ina226_ptr)
{
	HAL_I2C_Master_Receive_IT(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, (uint8_t*)&ina226_ptr->rx_data, 2);
	return 0;
}

/**
  * @brief  запрос данных из INA226 для работы в режиме с прерыванием
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
uint16_t ina226_read_data_process(type_INA226_DEVICE* ina226_ptr)
{
	if (ina226_ptr->rx_data == 0xFFFF){
		ina226_ptr->error_cnt += 1;
		return 0;
	}
	switch(ina226_ptr->rx_reg_addr){
		case VBUS_REGISTER_ADDR:
			ina226_ptr->voltage = ina226_ptr->rx_data; //значение, где старший байт - вольты, младший - дробная часть в 1/256 В
			break;
		case CURRENT_REGISTER_ADDR:
			ina226_ptr->current = ina226_ptr->rx_data; //значение, где старший байт - амперы, младший - дробная часть в 1/256 В
			break;
		case POWER_REGISTER_ADDR: // todo: не опрашивается
			ina226_ptr->power = ina226_ptr->rx_data; //значение, где старший байт - вольты, младший - дробная часть в 1/256 В
			break;
	}
	return 0;
}

/**
  * @brief  обработка ошибок общения с перефеией I2C для вызова в ErrorCB
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
void ina226_error_process(type_INA226_DEVICE* ina226_ptr)
{
	ina226_ptr->error_cnt += 1;
	ina226_ptr->queue_state = 0;
}

/**
  * @brief  старт чтения данных из INA226 c использованием очереди на прерываниях
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  */
void ina226_start_read_queue(type_INA226_DEVICE* ina226_ptr)
{
	ina226_ptr->queue_state = 1;
	ina226_reg_addr_set(ina226_ptr, VBUS_REGISTER_ADDR);
}

/**
  * @brief  развертывание очереди на прерываниях 
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  */
void ina226_body_read_queue(type_INA226_DEVICE* ina226_ptr)
{
		switch (ina226_ptr->queue_state){
			case 1:
				ina226_read_request(ina226_ptr);
				break;
			case 2:
				
				ina226_read_data_process(ina226_ptr);
				ina226_reg_addr_set(ina226_ptr, CURRENT_REGISTER_ADDR);
				break;
			case 3:
				ina226_read_request(ina226_ptr);
				break;
			case 4:
				ina226_read_data_process(ina226_ptr);
				ina226_ptr->queue_state = 0;
				return;
			default:
				break;
		}
 		ina226_ptr->queue_state++;
}




void ina226_snake(type_INA226_Snake* Snake){
		Snake->ch_read_queue += 1;
		if(Snake->ch_read_queue > 1){
					Snake->ch_read_queue = 0;					
				}
		ina226_start_read_queue(&Snake->INA_226[Snake->ch_read_queue]);
}

