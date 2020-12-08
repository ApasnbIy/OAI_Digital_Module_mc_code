#ifndef _MY_UART_H
#define _MY_UART_H

#include "main.h"
#include "usart.h"

#define UART_TRANSMIT_DATA_BUFF 128
#define UART_RECIVE_DATA_BUFF 2048

#pragma pack(push, 2)

typedef struct
{
	uint16_t scaler;
	uint16_t start;
	uint16_t transmit_flag;
	uint16_t len;
	uint16_t data[UART_TRANSMIT_DATA_BUFF/2];
}
type_uart_transmit_struct;

typedef struct
{
	uint16_t scaler;  //+0
	uint16_t start;		//+1
	uint16_t len;				//+2
	uint16_t write_ptr;	//+3
	uint8_t	 data[UART_RECIVE_DATA_BUFF]; //+4 	
}
type_uart_receive_struct;

typedef struct		// 1140 UART1 1218 UART2
{
	uint16_t scaler;		
	uint16_t LOW_BAUD;
	uint16_t HIGH_BAUD;
	uint16_t UART_STOP_BITS;
	uint16_t UART_PAIRITY;
	uint16_t UART_WORD_LENGH;
	uint16_t Default;
	uint16_t Reserved[2];
	uint16_t flag;							// 10regs
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
	uint16_t Reserved[2];
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


void MY_USART1_UART_Init(type_uart_setting_union* uart_settings);
void MY_USART_UART_struct_default_init(type_uart_setting_union* uart_settings);
void MY_USART2_UART_Init(type_uart_setting_union* uart_settings);


#endif

