#ifndef _MY_SPI_H
#define _MY_SPI_H

#include "main.h"

/*
mode 				 	master - 0, slave -1
direction 	 	2Line - 0, 2Line_rx_only - 1, 1Line - 2
data_size		 	8bit - 0, 16bit -1
polarity 			low - 0, high - 1
phase					one_edge - 0, two_edge - 1
slave					not_used_et
baud					0 - 21MB/s, 1 - 10,5 MB/s, 2 - 5,25 MB/s, 3 - 2,625 MB/s, 4 - 1,3125 MB/s, 5 - 656,25 kB/s, 6 - 328,125 kB/s, 7 - 164,062 kB/s.
firs_bit			0 - MSB_first, 1 - LSB_first
ti_mode				0 - disable, 1 - enable

 
*/
#pragma pack(push, 2)

typedef struct
{
	uint16_t	scaler; 			//+0
	uint16_t	mode; 				//+1
	uint16_t  direction; 		//+2
	uint16_t  data_size;		//+3
	uint16_t  polarity; 		//+4
	uint16_t  phase;				//+5
	uint16_t  slave;				//+6
	uint16_t  baud;					//+7
	uint16_t  firs_bit;			//+8
	uint16_t	ti_mode;			//+9
	uint16_t	init_flag;		//+10
	uint16_t  set_default;	//+10
	uint16_t  reserved[8];	//+11
}
type_spi_settings_struct;

typedef struct
{
	uint16_t scaler;					//+0												
	uint16_t reserved0;				//+1												
	uint16_t len;							//+2
	uint16_t start;						//+3	
	uint16_t transaction_end;	//+4
	uint16_t rx_tx_flag;
	uint16_t reserved[4];			//+5	
	uint16_t data[32];				//+10
	
}
type_spi_transmit_struct;

typedef struct
{
	uint16_t scaler;					//+0												
	uint16_t reg_addres;			//+1												
	uint16_t len;							//+2
	uint16_t start;						//+3	
	uint16_t transaction_end;	//+4
	uint16_t reserved[5];			//+5	len =10
	
}
type_spi_receive_struct;

#pragma pack(pop, 2)

typedef struct
{
	uint16_t data[64];				// len == 64 regs
}
type_spi_receive_data;


void MY_SPI2_Init(type_spi_settings_struct* spi_settings);
void my_spi_transmit(type_spi_transmit_struct* spi_transmit);
void my_spi_receive(type_spi_receive_struct* spi_receive, type_spi_receive_data* spi_receive_data);
void my_spi_default_settings(type_spi_settings_struct* spi_settings);
void my_spi_transmit_recive(type_spi_receive_data* spi_receive_data, type_spi_transmit_struct* spi_transmit_str);

#endif

