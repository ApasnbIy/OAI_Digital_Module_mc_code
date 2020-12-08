#ifndef _MODBUS_DATA_FORMATER_H
#define _MODBUS_DATA_FORMATER_H


#include "modbus_rtu.h"
#include "INA226.h"

#include "my_GPIO.h"
#include "my_UART.h"
#include "my_spi.h"



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
	int16_t voltage;
	int16_t	current;
	int16_t power;
}
type_ina_226_data;




typedef struct
{
	// analog in
	type_adc_data_struct 							mb_adc; 										//+0    															  len bytes 16        8
	type_ina_226_data									ina226_3v3;									//+16 		bytes     //+8    regs			  len bytes 6	        3
	type_ina_226_data									ina226_5v;									//+22 		bytes			//+11   regs				len bytes 6					3
	type_uart_receive_struct					mb_uart1_receive_struct;		//+28 		bytes			//+14   regs				len bytes 2056			1026
	type_uart_receive_struct 					mb_uart2_receive_struct;		//+2084		bytes			//+1042 regs				len bytes 2056			1026
	type_gpio_in_union								mb_gpio_in_union;						//+4140		bytes			//+2070 regs				len bytes 8					4
	type_spi_receive_data							mb_spi_receive_data;				//+4148		bytes			//+2074 regs				len bytes 128				64
	uint16_t 													dummy1[MB_DATA_SIZE  - (sizeof(type_adc_data_struct)/2) -(sizeof(type_uart_receive_struct)) - (sizeof(type_ina_226_data)) - \
																		 (sizeof(type_gpio_in_union)/2) - (sizeof(type_spi_receive_data)/2) ]; // +0x10
	
	//analog_out			
	type_dac_data_struct							mb_dac1; 										//	+0
	type_dac_data_struct							mb_dac2; 										// 	+1056 bytes // +528  regs 0x210
	type_adc_settings									mb_adc_settings; 						//	+2112	bytes	// +1056 regs 0x420
	type_gpio_config_union						mb_gpio_config_union;				//	+2118	bytes	// +1059 regs 0x423
	type_gpio_out_union								mb_gpio_out_union;					//	+2128 bytes	// +1064 regs 0x428
	type_gpio_in_union								reserved;										//	+2136	bytes	// +1068 regs 0x42C	
	type_uart_transmit_struct					mb_uart1_transmit_struct; 	// 	+2144 bytes // +1072 regs 0x430
	type_uart_setting_union  					mb_uart1_setting_struct;		// 	+2280 bytes // +1140 regs 0x474
	type_uart_transmit_struct					mb_uart2_transmit_struct;		// 	+2300 bytes // +1150 regs 0x47E
	type_uart_setting_union  					mb_uart2_setting_struct;		//	+2436 bytes // +1218 regs 0x4C2
	type_alternative_gpio_out_struct	mb_gpio_alternative_out; 		//	+2456 bytes // +1228 regs
	type_spi_settings_struct					mb_spi_settings;						//	+2492 bytes // +1246 regs
	type_spi_transmit_struct					mb_spi_transmit;						//  +2532 bytes // +1266 regs
	type_spi_receive_struct						mb_spi_receive;							//  +2616 bytes // +1308 regs
	
	uint16_t								dummy2[MB_DATA_SIZE - (sizeof(type_uart_setting_union)/2) - (sizeof(type_dac_data_struct)) - \
		(sizeof(type_adc_settings)/2)-(sizeof(type_gpio_config_union)/2) - (sizeof(type_gpio_out_union)/2) - (sizeof(type_gpio_in_union)/2) - \
		(sizeof(type_uart_transmit_struct)) - (sizeof(type_alternative_gpio_out_struct)/2) - (sizeof(type_spi_settings_struct)/2) - \
		(sizeof(type_spi_transmit_struct)/2)]; // sizeof in bytes, uint8, massive is uint16
	uint16_t								dummy3[MB_DATA_SIZE];
	uint16_t								dummy4[MB_DATA_SIZE];
}type_modbus_data_named;

#pragma pack(pop)

//  +2490 bytes // +1245 regs
//  +2544 bytes // +1272 regs
//  +2638 bytes // +1319 regs

#endif
