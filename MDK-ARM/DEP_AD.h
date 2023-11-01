#ifndef _DEP_Module_H
#define _DEP_Module_H
#include "main.h"


typedef struct{
	uint16_t scaler;
	uint16_t start;
}
type_DEP_kpa_module;

typedef struct{
	uint16_t ADC_data[2000];
	uint16_t Freq_Data[2000];
	uint16_t last_data_pointer;	
}
type_DEP_Data;







#endif
