#ifndef _MODBUS_RTU_H
#define _MODBUS_RTU_H

#include "main.h"
#include "vcp_time_segmentation.h"

#define DISCRET_INPUTS_OUTPUTS_Size 0x270F
#define ANALOG_INPUTS_OUTPUTS_Size 	0x270F //9999 standart ModBus addres space



/** 
  * @brief  ModBus  
*/

#define DEVICE_ID 0x01


typedef struct
{
	uint16_t discret_inputs[DISCRET_INPUTS_OUTPUTS_Size];
	uint16_t discret_outputs[DISCRET_INPUTS_OUTPUTS_Size];
	uint16_t analog_inputs[ANALOG_INPUTS_OUTPUTS_Size];
	uint16_t analog_outputs[ANALOG_INPUTS_OUTPUTS_Size];
} type_modbus_data;





uint8_t modbus_RX_TX_handler(type_modbus_data* modbus_ptr,type_VCP_UART* vcp_ptr );
void modbus_struct_init_constant(type_modbus_data* modbus_data_ptr);
uint16_t MRTU_CRC(uint8_t *data, uint8_t len);
uint8_t modbus_answ(uint8_t f_code, uint8_t leng, uint8_t* com_data, uint16_t* data,uint16_t reg_addr);
uint8_t modbus_answ_shrt(uint8_t* tx_data, uint8_t* data);	

#endif
