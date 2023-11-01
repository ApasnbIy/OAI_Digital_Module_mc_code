#ifndef _LoRa_H
#define _loRa_H


#include "my_SPI.h"



typedef struct{
  uint16_t Reg_addr; 
	uint16_t Len;
	uint16_t Data[256];
}
type_Lora_RdWr_data;



typedef struct{
  uint8_t ChipNum;
	uint8_t Scaler;
	uint16_t Reg_addr;
	uint16_t Len;
	type_Lora_RdWr_data Data[4];
}
type_Lora_Command;


void LoRa_init(void);
//void AD7490_body_read_queue(type_AD7490_data* AD7490_ptr);
//void AD7490_start_read(type_AD7490_data* ad7490_ptr);
//void AD7490_snake(type_AD7490_data* ad7490_ptr);


#endif

