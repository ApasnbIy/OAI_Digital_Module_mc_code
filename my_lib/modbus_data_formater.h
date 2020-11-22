#ifndef _MODBUS_DATA_FORMATER_H
#define _MODBUS_DATA_FORMATER_H


#include "modbus_rtu.h"
#include "INA226.h"


#pragma pack(push, 2)
typedef struct
{	
	uint16_t data[8];
}type_adc_data_struct;

typedef struct
{
	uint16_t settings_scaler;
	uint16_t start;
	uint16_t settings;
}type_adc_settings;


typedef struct
{
	uint16_t settings_scaler;
	uint16_t timer_counter;
	uint16_t timer_prescaler;
	uint16_t dma_cycl_single;
	uint16_t start;
	uint16_t reserved[11];
	uint16_t data[512];	
}type_dac_data_struct;






typedef struct
{
	type_adc_data_struct 		mb_adc;  
	uint16_t 								dummy1[MB_DATA_SIZE - (sizeof(type_adc_data_struct)/2)]; // 
	type_dac_data_struct		mb_dac1;
	type_dac_data_struct		mb_dac2;
	type_adc_settings				mb_adc_settings;	
	uint16_t								dummy2[MB_DATA_SIZE - (sizeof(type_dac_data_struct)/2)-(sizeof(type_dac_data_struct)/2) - (sizeof(type_adc_settings)/2)];
	uint16_t								dummy3[MB_DATA_SIZE];
	uint16_t								dummy4[MB_DATA_SIZE];
}type_modbus_data_named;
#pragma pack(pop)





#endif
