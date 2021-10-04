#ifndef _MY_MKO_H
#define _MY_MKO_H

#include <stdint.h>
#include "led.h"
#include "gpio.h"
#include "tim.h"
#include "my_GPIO.h"
#include <string.h>

extern type_LED_INDICATOR mcu_state_led;
/*
GPIO29 MKO_ENABLE
GPIO30 MKO_iak
GPIO31 MKO_PWRite
*/
typedef struct{
  uint16_t LH_word;
  uint16_t HH_word;
}type_two_half_word;

typedef union{
  uint32_t word;
  type_two_half_word two_half_word;
}type_word_union;

typedef struct {
  uint16_t ComandWord;		//1349
	uint16_t AnswerWord;		//1350
  uint16_t Data[32];			//1351
} type_MKO_Data;

typedef struct{
	uint16_t Cntrl;		//1383
	uint16_t Data;		//1384
	uint16_t Word_clk;//1385	
	uint16_t Len;			//1386
  uint16_t TimeOutFlag;//1387
	uint16_t MKO_initFlag;//1388
} type_MKO_Cntrl;

typedef struct{
	uint16_t scaler;  				//1348  
	//[0] - собственно scaler - старт транзакции
  //[1] - выбор канала
  //[2] - признак отсутствия ответа/данных по таймауту
  //[3] - признак окончания обмена
  type_MKO_Data MKO_Data;		//1349
	type_MKO_Cntrl MKO_Cntrl;	//1383	
}type_MKO_Struct;




/*
typedef struct {
  uint16 Data;
  uint8 Ctrl;
  // (R)   [7] - признак cmdstat
  // (R/W) [6] - 1=передаваемое слово - команда
	// (R/W) [5] - cfg - 
  // (R/W) [4] - 0-основной канал, 1-резервный
  // (R)   [3] - ошибка четности
  // (R)   [2] - таймаут в ожидании ответа
  // (R)   [1] - признак приема слова
  // (R)   [0] - готовность буфера передатчика
} typeMKOBCRegs;
*/


void MKO_init_command_wires(void);
void MKO_callback(void);
void MKO_config_port_in(void);
void MKO_config_port_out(void);
void MKO_Init(void);
void MKO_transmitt(void);
void MKO_Exchange(type_MKO_Struct* MKO_Struct_ptr);
void MKO_Reset(void);
void MKO_Write_reg(uint16_t addr, uint16_t* data_ptr);
void MKO_Read_reg(uint16_t addr, uint16_t* data_ptr);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void EXTI0_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
#endif

