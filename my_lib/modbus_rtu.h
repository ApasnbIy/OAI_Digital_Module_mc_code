#ifndef _MODBUS_RTU_H
#define _MODBUS_RTU_H

#include "main.h"
#include "vcp_time_segmentation.h"

#define MB_DATA_SIZE 8192






/** 
  * @brief  ModBus  
*/

#define DEVICE_ID 0x01

#pragma pack(push, 2)
typedef struct
{
	uint16_t analog_inputs[MB_DATA_SIZE];
	uint16_t analog_outputs[MB_DATA_SIZE];
	uint16_t discret_inputs[MB_DATA_SIZE];
	uint16_t discret_outputs[MB_DATA_SIZE];
} type_modbus_data;





typedef struct
{
    uint32_t* pointer_to_copy_struct; // аддрес структуры с данными
		uint32_t* pointer_to_destination_struct;
		uint16_t 	offset_in_copy; 
		uint16_t 	offset_in_dest;	
    uint16_t  len; // длина данных
		
} type_MB_Address_space;
#pragma pack(pop)


uint8_t modbus_RX_TX_handler(type_modbus_data* modbus_ptr,type_VCP_UART* vcp_ptr );
void modbus_struct_init_constant(type_modbus_data* modbus_data_ptr);
uint16_t MRTU_CRC(uint8_t *data, uint8_t len);
uint8_t modbus_answ(uint8_t f_code, uint8_t leng, uint8_t* com_data, uint16_t* data,uint16_t reg_addr);
uint8_t modbus_answ_shrt(uint8_t* tx_data, uint8_t* data);	

void data_copy(uint32_t* ptr_a,uint32_t* ptr_b, uint32_t len);
void MB_Data_Adress_set(type_MB_Address_space* Addr_space, uint32_t* ptr_to_destination_struct, uint32_t* ptr_to_copy_struct, uint16_t offset_c, uint16_t offset_d, uint16_t len);
void MB_data_update(type_MB_Address_space* ptr_MB_Addres_space, uint16_t last_address);

#endif
