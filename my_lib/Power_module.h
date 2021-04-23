#ifndef _Power_Module_
#define _Power_Module_

#include "i2c.h"
#include "string.h"
#include "INA226.h"
#include "tim.h"
#include "my_GPIO.h"
#include "analog_data.h"

//#include "debug.h"


// Параметры усреднения
#define POWER_AVERAGES_NUM_1 0x00
#define POWER_AVERAGES_NUM_4 0x01
#define POWER_AVERAGES_NUM_16 0x02
#define POWER_AVERAGES_NUM_64 0x03
#define POWER_AVERAGES_NUM_128 0x04
#define POWER_AVERAGES_NUM_256 0x05
#define POWER_AVERAGES_NUM_512 0x06
#define POWER_AVERAGES_NUM_1024 0x07
//Время преобразования для тока или напряжения
#define POWER_CONV_TIME_140us 0x00
#define POWER_CONV_TIME_204us 0x01
#define POWER_CONV_TIME_332us 0x02
#define POWER_CONV_TIME_588us 0x03
#define POWER_CONV_TIME_1100us 0x04
#define POWER_CONV_TIME_2116us 0x05
#define POWER_CONV_TIME_4156us 0x06
#define POWER_CONV_TIME_8244us 0x07
//режимы оперирования
#define POWER_SHUTDOWN 0x00
#define POWER_SHUNT_TRIG 0x01
#define POWER_VOLTAGE_TRIG 0x02
#define POWER_SHUNT_VOLTAGE_TRIG 0x03
#define POWER_SHUTDOWN_ALT 0x04
#define POWER_SHUNT_CONT 0x05
#define POWER_VOLTAGE_CONT 0x06
#define POWER_SHUNT_VOLTAGE_CONT 0x07
// проверочные регистры

// настройки INA226
// адреса регистров
#define POWER_VBUS_REGISTER_ADDR 0x02
#define POWER_CURRENT_REGISTER_ADDR 0x04
#define POWER_POWER_REGISTER_ADDR 0x03
#define POWER_CAL_REGISTER_ADDR 0x05
#define POWER_ALERT_REGISTER_ADDR 0x07
#define POWER_MODE_REGISTER_ADDR 0x06
#define POWER_MANUFACTURED_ID_REG_ADDR 0xFE
#define POWER_DIE_ID_REG_ADDR 0xFF

//Configuration_register
#define POWER_AVEREGES_DEF AVERAGES_NUM_64
#define POWER_CONV_TIME_DEF CONV_TIME_1100us
#define POWER_MODE_DEF SHUNT_VOLTAGE_CONT
#define POWER_ALERT_MODE_DEF (1<<13)  // overvolatge, //no lath  + latch/ if return to normal value, not go to work
//Calibration register: This value is needed to recalculate for each shunt
#define POWER_CURRENT_LSB (0.001)  //A  
#define POWER_CURRENT_R_SHUNT (0.05)  //Ом
#define POWER_CAL_VAL (0.00512/(POWER_CURRENT_LSB*POWER_CURRENT_R_SHUNT))

#define VOLTAGE_DEVIATION 25 //mV

// backside struct
typedef struct{												
	uint16_t it_is_power_module;	//1		
	uint16_t voltage_aligned;			// приведенное к ацп 1lsb - 12.5 mV
	uint16_t voltage_aligned_temp;
	uint16_t over_voltage_aligned;
	uint16_t overvoltage;				// в мВ
	uint16_t overcurrent;
	uint16_t pwm_1;
	uint16_t pwm_2;
	uint16_t voltage_1;
	uint16_t voltage_2;
	int16_t delta_1;
	int16_t delta_2;
	int16_t summ_1;
	int16_t summ_2;
	uint16_t power_on_delay;
	uint16_t constrain_avalible;
	uint16_t on_off;
}
type_power_module;


typedef struct{
	uint16_t scaler;						//0
	uint16_t voltage;						// мВ						//2	 in mV
	uint16_t on_off;						// 1/0				// 0/1
	uint16_t overvoltage;					// мВ				//5	 in mV 			
	uint16_t overcurent;					// мА				//6	 in mA
	int16_t delta_1;							// мВ				// in mV					
	int16_t delta_2;							// мВ	
	uint16_t new_constrain;				// показывает что обновились ограничения	
	uint16_t new_constant;				// показывает что обновились калибровки
	uint16_t it_is_power_module;	//
	uint16_t ina_error_reset;			//
	uint16_t power_on_delay;

}
type_power_module_settings;



typedef struct
{
	uint16_t voltage;								// in mV	+2141
	uint16_t current;								// in mA	+2142
	uint16_t allert;								// 0/1		+2143
	uint16_t ina_error;								//			+2144	
	uint16_t voltage_control;						// in mV	+2145
	uint16_t voltage_module_1;					// in mV  +2146
	uint16_t voltage_module_2;					// in mV +2147
	uint16_t ina_aligned_voltage;
}
type_power_module_output_data;


uint8_t ina226_power_module_init(type_INA226_DEVICE* ina226_ptr, I2C_HandleTypeDef* i2c_ptr, uint8_t addr, uint16_t voltage_lim_v);
uint8_t power_module_init(type_power_module* pwr_module_ptr);
void MY_TIM3_Init(void);
void power_module_PWM_calculate(type_adc_data_struct* adc_ptr, type_power_module* pwr_mdl_ptr);
void power_on(type_power_module* pwr_mdl_ptr);
void power_module_pwm_calculate(type_power_module* pwr_mdl_ptr);
void power_module_gpio_init(void);
void power_module_voltage_set(type_power_module* pwr_mdl_ptr);
void power_module_voltage_on_off(type_power_module* pwr_mdl_ptr);
uint8_t ina226_power_allert_set(type_INA226_DEVICE* ina226_ptr, uint16_t voltage_lim_v);
#endif
