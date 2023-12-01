#ifndef _LoRa_H
#define _LoRa_H


#include "my_SPI.h"
#include "my_GPIO.h"


extern type_gpio_out_union 		mb_gpio_outputs;

#pragma pack(push, 2)

typedef struct{
	uint16_t scaler;     //1407
	uint16_t Len;				//1408
	uint16_t SPI_NUM; 	//1409 // 0 - SPI2   1 - SPI1
	uint16_t cs_num;  	//1410 // Pin Number from 1 to 60
	uint16_t t_r_flag;	//1411 // 0 - recieve 1 - transmit 2 - transmit receive
	uint16_t Data[256];	//1412 
	uint16_t SPI_Tranzaction_flag; // for detecting
}
type_SPI_RW_data;


typedef struct{
	uint16_t Data[255];
}
type_SPI_Ansver;

#pragma pack(pop, 2)

void SPI_RW_routine(type_SPI_RW_data* spi_rw_data, type_SPI_Ansver* spi_answer);
void CS_UP_DOWN(uint16_t pin_num, uint8_t SET_RESET);


#endif

