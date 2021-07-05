#ifndef _MY_SPI_H
#define _MY_SPI_H

#include "main.h"
#include "my_GPIO.h"

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
	uint16_t	scaler; 			//+0 	1246   	//1
	uint16_t	mode; 				//+1 	1247		//0
	uint16_t  direction; 		//+2 	1248		//0
	uint16_t  data_size;		//+3 	1249		//1
	uint16_t  polarity; 		//+4 	1250		//0
	uint16_t  phase;				//+5	1251		//1
	uint16_t  slave;				//+6	1252		//0
	uint16_t  baud;					//+7	1253		//5
	uint16_t  firs_bit;			//+8	1254		//0	
	uint16_t	ti_mode;			//+9	1255		//0
	uint16_t	init_flag;		//+10	1256
	uint16_t  set_default;	//+10	1257
	uint16_t  reserved[8];	//+11	1258
}
type_spi_settings_struct;

//15......0
//cs16...cs1
typedef struct
{
	uint16_t scaler;				//+1318
	uint16_t num;						//+1319
	uint16_t init_flag;			//+1320
	uint16_t cs_1;					//+1321
	uint16_t cs_2;					//+1322
	uint16_t cs_3;					//+1323
	uint16_t cs_4;					//+1324
	uint16_t cs_5;					//+1325
	uint16_t cs_6;					//+1326
	uint16_t cs_7;					//+1327
	uint16_t cs_8;					//+1328
	uint16_t cs_9;					//+1329	
	uint16_t cs_10;					//+1330
	uint16_t cs_11;					//+1331
	uint16_t cs_12;					//+1332	
	uint16_t cs_13;					//+1333
	uint16_t cs_14;					//+1334
	uint16_t cs_15;					//+1335
	uint16_t cs_16;					//+1336
}
type_spi_chipselect_settings;

typedef struct
{
	uint16_t scaler;					//+0 	1266											
	uint16_t reserved0;				//+1	1267												
	uint16_t len;							//+2	1268
	uint16_t start;						//+3	1269
	uint16_t transaction_end;	//+4	1270
	uint16_t rx_tx_flag;			//+5	1271
	uint16_t chip_mask;				//+6  1272
	uint16_t reserved[3];			//+7	1273
	uint16_t data[32];				//+10	1276
	
}
type_spi_transmit_struct;

typedef struct
{
	uint16_t scaler;					//+0		1308										
	uint16_t reserved1;				//+1		1309											
	uint16_t len;							//+2		1310
	uint16_t start;						//+3		1311
	uint16_t transaction_end;	//+4		1312
	uint16_t reserved[5];			//+5	len =10
}
type_spi_receive_struct;


typedef struct
{
	uint16_t scaler; //
	uint16_t len;	
	uint16_t end_flag;
	uint16_t error_code;
	uint16_t copy_data_to_onebuff_flag;
}
type_spi_command_bank_control;

#pragma pack(pop, 2)

typedef struct
{
	uint16_t data[64];				// len == 64 regs // +2074
}
type_spi_receive_data;


void MY_SPI2_Init(type_spi_settings_struct* spi_settings);
void my_spi_transmit(type_spi_transmit_struct* spi_transmit);
void my_spi_receive(type_spi_receive_struct* spi_receive, type_spi_receive_data* spi_receive_data);
void my_spi_default_settings(type_spi_settings_struct* spi_settings);
void my_spi_transmit_recive(type_spi_receive_data* spi_receive_data, type_spi_transmit_struct* spi_transmit_str);
void my_spi_chip_select(uint16_t* chip_mask, type_spi_chipselect_settings* chip_select_init, type_gpio_out_union* gpio_out);
void my_spi_chip_deselect(uint16_t* chip_mask, type_spi_chipselect_settings* chip_select_init, type_gpio_out_union* gpio_out);
void my_spi_chip_select_init(type_spi_chipselect_settings* chip_select_init, type_gpio_config_union* gpio_union);

#endif
