#ifndef _MODBUS_DATA_FORMATER_H
#define _MODBUS_DATA_FORMATER_H


#include "modbus_rtu.h"
#include "INA226.h"
#include "my_GPIO.h"

#define UART_TRANSMIT_DATA_BUFF 128
#define UART_RECIVE_DATA_BUFF 2048

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
	uint16_t scaler;
	uint16_t start;
	uint16_t transmit_flag;
	uint16_t len;
	uint8_t	 data[UART_TRANSMIT_DATA_BUFF];
}
type_uart_transmit_struct;
typedef struct
{
	uint16_t scaler;
	uint16_t start;
	uint16_t write_ptr;
	uint16_t len;
	uint8_t	 data[UART_RECIVE_DATA_BUFF];
	
}
type_uart_recive_struct;

typedef struct
{
	uint16_t scaler;
	uint16_t HIGH_BAUD;
	uint16_t LOW_BAUD;
	uint16_t HIGH_WORDlenght;
	uint16_t LOW_WORDlenght;
	uint16_t HIGH_STOPBITS;
	uint16_t LOW_STOPBITS;
	uint16_t HIGH_PARITY;
	uint16_t LOW_PARITY;
	uint16_t flag;							// 10regs
}
type_uart_setting_struct;

typedef struct
{
	uint16_t scaler;
	uint32_t BAUD;			
	uint32_t WORDlenght;
	uint32_t STOPBITS;
	uint32_t PARITY;
	uint16_t flag;
}
type_uart_setting_named_struct;

typedef union
{
	type_uart_setting_struct         settings;
	type_uart_setting_named_struct	 settings_named;	
}
type_uart_setting_union;

typedef struct
{
	int16_t voltage;
	int16_t	current;
	int16_t power;
}
type_ina_226_data;




typedef struct
{
	// analog in
	type_adc_data_struct 		mb_adc; 										//+0
	type_ina_226_data				ina226_3v3;									//+16 bytes     //+8    regs
	type_ina_226_data				ina226_5v;									//+22 bytes			//+11   regs
	type_uart_recive_struct	mb_uart1_recive_struct;			//+28 bytes			//+14   regs
	uint16_t 								dummy1[MB_DATA_SIZE - (sizeof(type_adc_data_struct)/2) -(sizeof(type_uart_recive_struct)/2) - (sizeof(type_ina_226_data))]; // +0x10
	//analog_out
	type_dac_data_struct		mb_dac1; 										// 	+0
	type_dac_data_struct		mb_dac2; 										//  +1056 bytes // + 528 regs  0x210
	type_adc_settings				mb_adc_settings; 						//  +2112	bytes	// + 1056 regs 0x420
	type_gpio_config_union	mb_gpio_config_union;				// 	+2118	bytes	// + 1059 regs 0x423
	type_gpio_out_union			mb_gpio_out_union;					//	+2128 bytes	// + 1064 regs 0x428
	type_gpio_in_union			mb_gpio_in_union;						//	+2136	bytes	// + 1068 regs 0x42C	
	type_uart_transmit_struct	mb_uart1_transmit_struct; //  +2144 bytes // + 1072 regs 0x430
	type_uart_setting_union  mb_uart1_setting_struct;		//  +2280 bytes // + 1140 regs 0x474
	uint16_t								dummy2[MB_DATA_SIZE - (sizeof(type_uart_setting_union)/2) - (sizeof(type_dac_data_struct)/2)-(sizeof(type_dac_data_struct)/2) - (sizeof(type_adc_settings)/2)-(sizeof(type_gpio_config_union)/2) - (sizeof(type_gpio_out_union)/2) - (sizeof(type_gpio_in_union)/2)]; // sizeof in bytes, uint8, massive is uint16
	uint16_t								dummy3[MB_DATA_SIZE];
	uint16_t								dummy4[MB_DATA_SIZE];
}type_modbus_data_named;
#pragma pack(pop)





#endif
