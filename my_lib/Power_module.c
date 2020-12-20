/**
  ******************************************************************************
  * @file           : ina226.c
  * @version        : v1.0
  * @brief          : надстройка над CubeMX для удобного управления INA226 через I2C
  * @author			: Стюф Алексей/Alexe Styuf <a-styuf@yandex.ru>
  ******************************************************************************
  */

#include "Power_module.h"

/**
	* @brief  инициализация работы с INA226 power module: специально использую блокирующий режим
  * @param  i2c_ptr: структура CubeMX для управления ядром I2C
  * @param  addr: адрес INA226
  * @retval статус ошибки: 1 - все хорошо, 0 - есть ошибка
  */
uint8_t ina226_power_module_init(type_INA226_DEVICE* ina226_ptr, I2C_HandleTypeDef* i2c_ptr, uint8_t addr, uint16_t voltage_lim_v)
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
	i2c_reg_val = (1 << 14)| (POWER_AVEREGES_DEF<<9) | (POWER_AVEREGES_DEF<<6) | (POWER_CONV_TIME_DEF<<3) | (POWER_MODE_DEF<<0);
	i2c_tr_data[0] = CONFIG_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data, 2, 100);
	// устанавливаем калибровки
	i2c_reg_val = POWER_CAL_VAL;
	i2c_tr_data[0] = CAL_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+2, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+2, 2, 100);
	// устанавливаем ограничение по overvoltage
	
	i2c_reg_val = voltage_lim_v;
	i2c_tr_data[0] = ALERT_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+4, i2c_tr_data+1, 2);
	
	HAL_I2C_Master_Transmit(i2c_ptr, addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(i2c_ptr, addr << 1, i2c_rx_data+4, 2, 100);
	
	// устанавливаем тип alert
	i2c_reg_val = POWER_ALERT_MODE_DEF;
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

