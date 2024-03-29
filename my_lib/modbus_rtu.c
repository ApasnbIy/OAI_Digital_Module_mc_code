/**
  ******************************************************************************
  * @file           : modbus_rtu.c
  * @version        : v1.0
  * @brief          :	modbus on VCP  by A.Styuf ModBus <a-styuf@yandex.ru>
											
  * @author			: Alexey Kozlov 
  ******************************************************************************
  */
#include "modbus_rtu.h"
#include "modbus_data_formater.h"
#include "led.h"


extern type_LED_INDICATOR con_state_led;



void modbus_struct_init_constant(type_modbus_data* modbus_ptr)
{
    for(uint16_t i = 0; i < MB_DATA_SIZE; i++)
    {
      modbus_ptr->analog_inputs[i] = 0;
      modbus_ptr->analog_outputs[i]= 0;
      modbus_ptr->discret_inputs[i] = 0;
      modbus_ptr->discret_outputs[i] = 0;
    }
}


/** 
  * @brief  ModBus  parser
*/

uint8_t modbus_RX_TX_handler(type_modbus_data* modbus_ptr, type_VCP_UART* vcp_ptr){
	uint16_t addr;
	uint8_t len;
		
  if(vcp_ptr->rx_data[0] == DEVICE_ID){
		if(vcp_ptr->rx_data[1] == 0x03){ //read analog outputs (addr 0, code (0x03) 1, Hi_addr 2, Lo_addr 3, Hi_reg_num 4, Lo_reg_num5, CRC16) 
			if(MRTU_CRC(vcp_ptr->rx_data, 0x08) == 0 ){
        addr = ((vcp_ptr->rx_data[2]<<8) | vcp_ptr->rx_data[3]) & 0xFFFF;
				len = modbus_answ(vcp_ptr->rx_data[1], vcp_ptr->rx_data[5], vcp_ptr->tx_data, modbus_ptr->analog_outputs, addr);
        vcp_uart_write(vcp_ptr,vcp_ptr->tx_data,len);
			}
    }
    else if(vcp_ptr->rx_data[1] == 0x04){ //read analog inputs (addr, code (0x04), Hi_addr, Lo_addr, Hi_reg_num, Lo_reg_num, CRC16) 
			if(MRTU_CRC(vcp_ptr->rx_data, 0x08) == 0 ){
        addr = ((vcp_ptr->rx_data[2]<<8) | vcp_ptr->rx_data[3]) & 0xFFFF;
				len = modbus_answ(vcp_ptr->rx_data[1],vcp_ptr->rx_data[5],vcp_ptr->tx_data, modbus_ptr->analog_inputs, addr);
        vcp_uart_write(vcp_ptr,vcp_ptr->tx_data,len); 
			} 
    }
    else if(vcp_ptr->rx_data[1] == 0x06){ //write single analog output
      if(MRTU_CRC(vcp_ptr->rx_data, 0x08) == 0 ){ 
        addr = ((vcp_ptr->rx_data[2]<<8) | vcp_ptr->rx_data[3]) & 0xFFFF;        
        memcpy(&modbus_ptr->analog_outputs[addr], &vcp_ptr->rx_data[4], 0x02);
        modbus_answ_shrt(vcp_ptr->tx_data, vcp_ptr->rx_data);
        vcp_uart_write(vcp_ptr, vcp_ptr->tx_data, 0x08);      
			}
    }
    else if(vcp_ptr->rx_data[1] == 0x10){ //write analog outputs
      if(MRTU_CRC(vcp_ptr->rx_data, (0x09 + vcp_ptr->rx_data[0x06])) == 0 ){
        addr = ((vcp_ptr->rx_data[2]<<8) | vcp_ptr->rx_data[3]) & 0xFFFF;   
				memcpy(&modbus_ptr->analog_outputs[addr], &vcp_ptr->rx_data[7], vcp_ptr->rx_data[0x06]);
        modbus_answ_shrt(vcp_ptr->tx_data, vcp_ptr->rx_data);
        vcp_uart_write(vcp_ptr, vcp_ptr->tx_data, 0x08);
			}	
    }
		else{
		led_alt_setup(&con_state_led, LED_BLINK, 200, 100, 3000);
		}
			
	}
  else{
		led_alt_setup(&con_state_led, LED_BLINK, 200, 100, 1600);
  }
	vcp_ptr->rx_position = 0;
	vcp_ptr->rx_size = 0;
	return 0;
}

/**
  * @brief  ansver for read data
  * @param  f_code - functional code
  * @param  leng - registers count
  * @param  tx_data - pointer to tx_data_buff
	* @param  data - pointer to data to transmitt
	* @param  reg_addres - offset
  
  * @retval ?????????? ???????????? ??????
  */
uint8_t modbus_answ(uint8_t f_code, uint8_t leng, uint8_t* tx_data, uint16_t* data, uint16_t reg_addr)
{	
	uint16_t crc = 0;
	uint8_t data_len = 0;
	
	tx_data[0] = DEVICE_ID;
  tx_data[1] = f_code & 0xFF;
  tx_data[2] = (leng*2) & 0xFF;
  memcpy(&tx_data[3], &data[reg_addr], leng*2);
  data_len = 5 + leng*2;
	crc = MRTU_CRC(tx_data, data_len-2);
	tx_data[data_len-1] = (uint8_t)((crc>>8) & 0xFF);
	tx_data[data_len-2] = (uint8_t)((crc>>0) & 0xFF);
	return data_len;
}

uint8_t modbus_answ_shrt(uint8_t* tx_data, uint8_t* data)
{	
	uint16_t crc = 0;
	uint8_t data_len = 0;
	memcpy(tx_data, data, 0x06);
	crc = MRTU_CRC(tx_data, 0x06);
	tx_data[0x07] = (uint8_t)((crc>>8) & 0xFF);
	tx_data[0x06] = (uint8_t)((crc>>0) & 0xFF);
	return data_len;
}


uint8_t auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
};

uint8_t auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};


uint16_t MRTU_CRC(uint8_t *data, uint8_t len)
{
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint16_t uIndex ;
    while(len--)
    {
        uIndex = uchCRCHi ^ *data++ ;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (((uint16_t)(uchCRCLo) << 8) | (uint16_t)(uchCRCHi));
}






void MB_Data_Adress_set(type_MB_Address_space* Addr_space, uint32_t* ptr_to_destination_struct, uint32_t* ptr_to_copy_struct, uint16_t offset_c, uint16_t offset_d, uint16_t len)
{
		Addr_space->pointer_to_destination_struct = ptr_to_destination_struct;
    Addr_space->pointer_to_copy_struct = ptr_to_copy_struct;
    Addr_space->offset_in_dest = offset_c;
		Addr_space->offset_in_dest = offset_d;
    Addr_space->len = len;
}		

void MB_data_update(type_MB_Address_space* ptr_MB_Addres_space, uint16_t last_address)
{	
	for(int i = 0; i < last_address+1; i++){
		memcpy((uint8_t*)((uint8_t*)ptr_MB_Addres_space[i].pointer_to_destination_struct + (uint16_t)ptr_MB_Addres_space[i].offset_in_dest), (uint8_t*)ptr_MB_Addres_space[i].pointer_to_copy_struct  + (uint16_t)ptr_MB_Addres_space[i].offset_in_copy, ptr_MB_Addres_space[i].len);
	 }
 }




