#ifndef _MPP_Module_H
#define _MPP_Module_H
#include "main.h"

typedef struct{
	uint16_t	scaler;
	uint16_t  Low_U;	// Voltage (end voltage)
	uint16_t  High_U;	// Voltage
	uint16_t 	N;
	uint16_t  M;
	uint16_t  T;
	uint16_t  t;
	
}
type_MPP_module;

//

void MX_MPP_Module_DMA_Init(void);




#endif
