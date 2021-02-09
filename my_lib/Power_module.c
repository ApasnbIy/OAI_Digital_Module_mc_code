/**
  ******************************************************************************
  * @file           : ina226.c
  * @version        : v1.0
  * @brief          : надстройка над CubeMX для удобного управления INA226 через I2C
  * @author			: Стюф Алексей/Alexe Styuf <a-styuf@yandex.ru>
  ******************************************************************************
  */

#include "Power_module.h"
#include "tim.h"
TIM_HandleTypeDef htim3;


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
	/*
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
	*/
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

uint8_t ina226_power_allert_set(type_INA226_DEVICE* ina226_ptr, uint16_t voltage_lim_v)
{
	uint8_t i2c_rx_data[16] = {0}, validate_data[16] = {0};
	uint8_t i2c_tr_data[8] = {0};
	uint16_t i2c_reg_val = 0;
	
	// устанавливаем ограничение по overvoltage
	
	i2c_reg_val = voltage_lim_v;
	i2c_tr_data[0] = ALERT_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+4, i2c_tr_data+1, 2);
	
	HAL_I2C_Master_Transmit(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(ina226_ptr->i2c_ptr, ina226_ptr->addr<< 1, i2c_rx_data+4, 2, 100);
	
	// устанавливаем тип alert
	i2c_reg_val = POWER_ALERT_MODE_DEF;
	i2c_tr_data[0] = MODE_REGISTER_ADDR;
	i2c_tr_data[1] = (i2c_reg_val>>8) & 0xFF;
	i2c_tr_data[2] = (i2c_reg_val>>0) & 0xFF;
	memcpy(validate_data+6, i2c_tr_data+1, 2);
	HAL_I2C_Master_Transmit(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, i2c_tr_data, 3, 100);
	HAL_I2C_Master_Receive(ina226_ptr->i2c_ptr, ina226_ptr->addr << 1, i2c_rx_data+6, 2, 100);
	//
	
	return 1;
	
}


uint8_t power_module_init(type_power_module* pwr_module_ptr){
	
	power_module_gpio_init();
	MY_TIM3_Init();

	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 8000); //
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 8000); // 
	
	HAL_TIM_Base_Start_IT(&htim9);	
	pwr_module_ptr ->it_is_power_module = 1;
	if(pwr_module_ptr ->overcurrent == 0 || pwr_module_ptr ->overcurrent >= 1500){
		pwr_module_ptr ->overcurrent = 1500; // задаем ограничение по току по умолчанию. если нужно поменять, для этого есть функционал
	}
	return 0;
}

void power_module_voltage_on_off(type_power_module* pwr_mdl_ptr){
	if(pwr_mdl_ptr->on_off == 1){
		HAL_GPIO_WritePin (GPIOC,GPIO1 ,GPIO_PIN_SET);
		
	}
	else{
		HAL_GPIO_WritePin (GPIOC,GPIO1, GPIO_PIN_RESET);
		
	}
}


void power_module_voltage_set(type_power_module* pwr_mdl_ptr){
	power_module_pwm_calculate(pwr_mdl_ptr);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwr_mdl_ptr->pwm_1); 
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwr_mdl_ptr->pwm_2);  
}

void power_module_pwm_calculate(type_power_module* pwr_mdl_ptr){
	pwr_mdl_ptr->pwm_1 = 8022 - 0.000005*pwr_mdl_ptr->voltage_aligned*pwr_mdl_ptr->voltage_aligned + 0.0114*pwr_mdl_ptr->voltage_aligned;
	pwr_mdl_ptr->pwm_2 = pwr_mdl_ptr->pwm_1;

}

void power_module_gpio_init(void){
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO1|GPIO3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO2;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	HAL_GPIO_WritePin (GPIOC,GPIO1|GPIO2, GPIO_PIN_RESET);
}

void MY_TIM3_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM3 GPIO Configuration    
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 5;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 8000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
  
}
