#ifndef _MPP_Module_H
#define _MPP_Module_H
#include "main.h"

typedef struct{
	uint16_t	  scaler;	//+0
	uint16_t  	Low_U; 	//+1		// Voltage нижний уровень сигнала      0-4095 0 - -15 4095 - +15
	uint16_t  	High_U;	//+2		// Voltage высокий уровень сигнала		 0-4095 0 - -15 4095 - +15
	uint16_t  	N;			//+3		// число импульсов в пачке
	uint16_t  	M; 			//+4		// число пачек в полном воздействии		
	uint16_t  	T; 			//+5		// период пачки (в мс)	
	uint16_t  	t; 			//+6		// период импульсов в пачке кратно 100 мкс (1 - 100мкс)
}	
type_MPP_kpa_module;
typedef struct {
	uint16_t V_high; // 
	uint16_t V_low;
	uint16_t Number_period;					 	// число импульсов в пачке
	uint16_t Number_period_original; 	// число импульсов в пачке исходное
	uint8_t Period_cycler; 					 	// период импульсов в пачке (1 - 100мкс)
	uint8_t Period_leng;  						// длина периода
	uint8_t Half_period_state; 				//флаг половины периода
	uint8_t Flag; //
	/*
	0 - ќбщий флаг генерации
	1 - флаг половины периода
	2 - флаг генераци¤ 
	3 - флаг пауза. мб нужен.
	*/
	uint32_t Pack_period; 						// период пачки
	uint32_t Pack_period_original;		// период пачки
	uint8_t Pack_number;							// число пачек	
	uint8_t Channel;
}type_MPP_Parametres;
//выходы от -15 до +15 В
//0    -> -15
//4095 -> +15

void MX_MPP_Module_DMA_Init(void);
void TIM_MPP_interrupt(type_MPP_Parametres* MPP);


#endif
 
