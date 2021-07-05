#ifndef _AD7490_H
#define _AD7490_H


#include "my_SPI.h"

typedef struct{
  uint16_t ADC_Data_last;
  uint16_t chip_select;
	uint16_t chan_num;
	uint16_t reserved;
	uint16_t ADC_Data[16];
}
type_AD7490_device;

typedef struct{
  type_AD7490_device AD_7490[2]; // нельзя делать масштабируемым, из-за предопределенности
	uint16_t device_num;
	uint16_t reserved[9];
}
type_AD7490_data;

typedef struct{
	uint16_t scaler;
	uint16_t stm_module_flag;
	uint16_t restart_stm_module;
}
type_stm_kpa_module;

void AD_7490_init(void);
void AD7490_body_read_queue(type_AD7490_data* AD7490_ptr);
void AD7490_start_read(type_AD7490_data* ad7490_ptr);
void AD7490_snake(type_AD7490_data* ad7490_ptr);


#endif

