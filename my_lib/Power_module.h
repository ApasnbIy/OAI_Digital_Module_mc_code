#ifndef _Power_Module_
#define _Power_Module_

#include "i2c.h"
#include "string.h"
#include "INA226.h"

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
#define POWER_ALERT_MODE_DEF (1<<13|1)  // overvolatge, + latch/ if return to normal value, not go to work
//Calibration register: This value is needed to recalculate for each shunt
#define POWER_CURRENT_LSB (0.001)  //A  
#define POWER_CURRENT_R_SHUNT (0.05)  //Ом
#define POWER_CAL_VAL (0.00512/(POWER_CURRENT_LSB*POWER_CURRENT_R_SHUNT))



typedef struct{
	uint16_t scaler;
	uint16_t voltage;
	uint16_t current;
	uint16_t overvoltage;
	uint16_t on_of;
	uint16_t allert;
	uint16_t it_is_power_module;


}
type_power_module;


typedef struct
{
	uint16_t real_voltage;
	uint16_t current;
	uint16_t allert;
}
type_power_module_output_data;


uint8_t ina226_power_module_init(type_INA226_DEVICE* ina226_ptr, I2C_HandleTypeDef* i2c_ptr, uint8_t addr, uint16_t voltage_lim_v);


#endif
