#ifndef _MY_UART_H
#define _MY_UART_H

#include "main.h"
#include "usart.h"
#include "my_GPIO.h"

#define UART_TRANSMIT_DATA_BUFF 128
#define UART_RECIVE_DATA_BUFF 2048

#pragma pack(push, 2)

typedef struct
{																											//UART1
	uint16_t scaler;															//+0		+1072		+1150
	uint16_t start;																//+1		+1073		+1151 
	uint16_t transmit_flag;												//+2		+1074		+1152
	uint16_t len;																	//+3		+1075		+1153
	uint16_t data[UART_TRANSMIT_DATA_BUFF/2];			//+4		+1076		+1154
}
type_uart_transmit_struct;

typedef struct
{
	uint16_t scaler;										  //+0   	+14 UART1 	+1042
	uint16_t start;												//+1   	+15 				+1043
	uint16_t len;													//+2 	 	+16  				+1044
	uint16_t write_ptr;										//+3	 	+17 				+1045
	uint8_t data[UART_RECIVE_DATA_BUFF]; //+4 		+18					+1046
}
type_uart_receive_struct;

typedef struct											// 1140 UART1 1218 UART2
{
	uint16_t scaler;									//1140		/1218
	uint16_t LOW_BAUD;								//1141		/1219
	uint16_t HIGH_BAUD;								//1142		/1220
	uint16_t UART_STOP_BITS;					//1143		/1221	
	uint16_t UART_PAIRITY;						//1144		/1222
	uint16_t UART_WORD_LENGH;					//1145		/1223
	uint16_t Default;									//1146		/1224
	uint16_t Duplex;									//1147		/1225
	uint16_t Reserved;								//1148		/1226
	uint16_t flag;										//1149		/1227											// 10regs
}
type_uart_setting_struct;

typedef struct
{
	uint16_t scaler;
	uint32_t BAUD;			
	uint16_t UART_STOP_BITS;
	uint16_t UART_PARITY;
	uint16_t UART_WORD_LENGH;
	uint16_t Default;
	uint16_t Duplex;
	uint16_t Reserved;
	uint16_t flag;
}
type_uart_setting_named_struct;

typedef union
{
	type_uart_setting_struct         settings;
	type_uart_setting_named_struct	 settings_named;	
}
type_uart_setting_union;

#pragma pack(pop)


void MY_USART1_UART_Init(type_uart_setting_union* uart_settings, type_gpio_config_union* gpio_conf);
void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings);
void MY_USART2_UART_Init(type_uart_setting_union* uart_settings, type_gpio_config_union* gpio_conf);


#endif

