#include "AD7490.h"
#include "modbus_data_formater.h"

extern type_mb_data_union mb_data_union; // 
extern SPI_HandleTypeDef hspi2;

void AD_7490_init(){
    HAL_SPI_Abort_IT(&hspi2);
	my_spi_default_settings(&mb_data_union.mb_data_named.mb_spi_settings);
    MY_SPI2_Init(&mb_data_union.mb_data_named.mb_spi_settings);    
}



void AD7490_body_read_queue(type_AD7490_device* AD7490_ptr){
    uint16_t control_register = 0x00;
    uint16_t ch_num = AD7490_ptr->chan_num;
    control_register = ((0x02 << 10) | ((ch_num & 0x0F) << 6) | (0x03 << 4) | (0x01 << 2) | (0x01 << 0)) << 4;
    HAL_SPI_TransmitReceive_IT(&hspi2, &control_register, &AD7490_ptr->ADC_Data, 2);
    AD7490_ptr->chan_num++;
}

