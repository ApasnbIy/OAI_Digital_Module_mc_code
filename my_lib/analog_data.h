#ifndef _ANALOG_DATA_H
#define _ANALOG_DATA_H
#include "main.h"
#pragma pack(push, 2)
typedef struct
{	
	uint16_t data[8];
}type_adc_data_struct;

typedef struct
{
	uint16_t settings_scaler;
	uint16_t start;
	uint16_t stop;
}type_adc_settings;

typedef struct
{
	uint16_t temperature;
}
type_temperature_data;


typedef struct
{																//dac1		//dac2
	uint16_t settings_scaler;			// +0			//+528
	uint16_t start;								//+1			//+529
	uint16_t stop;								//+2			//+530
	uint16_t timer_prescaler;			//+3			//+531
	uint16_t dma_cycl_single;			//+4			//+532
	uint16_t timer_counter;				//+5			//+533
	uint16_t reserved[10];				//+6			//+534
	uint16_t data[512];						//+16			//+544  //1056
}type_dac_data_struct;



typedef struct
{
	uint16_t voltage;
	uint16_t	current;
	uint16_t power;
}
type_ina_226_data;




#pragma pack(pop)

//  +2490 bytes // +1245 regs
//  +2544 bytes // +1272 regs
//  +2638 bytes // +1319 regs

#endif
