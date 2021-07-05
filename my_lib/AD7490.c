#include "AD7490.h"
#include "modbus_data_formater.h"

extern SPI_HandleTypeDef hspi2;
extern type_gpio_out_union 		mb_gpio_outputs;
extern type_gpio_config_union	mb_gpio_config;
extern type_mb_data_union mb_data_union;
uint16_t ad_7490_cs_mask;
uint16_t* ad_7490_cs_mask_p =  &ad_7490_cs_mask;
type_spi_settings_struct ad_7490_spi_settings;
type_spi_chipselect_settings ad_7490_cs_settings;
/**
  * @brief  инициализация SPI и структур для работы с 2мя AD7490
*/
void AD_7490_init(void){
  HAL_SPI_Abort_IT(&hspi2);
	
  my_spi_default_settings(&ad_7490_spi_settings);
  MY_SPI2_Init(&ad_7490_spi_settings);
  ad_7490_cs_settings.cs_1 = 1; 
  ad_7490_cs_settings.cs_2 = 2;
  my_spi_chip_select_init(&ad_7490_cs_settings, &mb_gpio_config);
  mb_data_union.mb_data_named.mb_AD7490.device_num = 0;
  ad_7490_cs_mask = 1;
  mb_data_union.mb_data_named.mb_AD7490.AD_7490[mb_data_union.mb_data_named.mb_AD7490.device_num].chan_num = 0; 
		
}

void AD7490_body_read_queue(type_AD7490_data* AD7490_ptr){
  uint16_t control_register = 0x00;
  uint16_t ch_num = 0x00;
	volatile uint16_t last_read_ch = 0x00;
  ch_num = AD7490_ptr->AD_7490[AD7490_ptr->device_num].chan_num;
  if(AD7490_ptr->device_num == 0){
    ad_7490_cs_mask = 1; // 0b0**0001
  }
  else if(AD7490_ptr->device_num == 1){
    ad_7490_cs_mask = 2; // 0b0**0010
  }
  my_spi_chip_deselect(ad_7490_cs_mask_p, &ad_7490_cs_settings, &mb_gpio_outputs);
	my_spi_chip_select(ad_7490_cs_mask_p, &ad_7490_cs_settings, &mb_gpio_outputs);
  control_register = ((0x02 << 10) | ((ch_num & 0x0F) << 6) | (0x03 << 4) | (0x01 << 2) | (0x01 << 0)) << 4;
	last_read_ch = (AD7490_ptr->AD_7490[AD7490_ptr->device_num].ADC_Data_last & 0xF000) >> 12;
	AD7490_ptr->AD_7490[AD7490_ptr->device_num].ADC_Data[last_read_ch] = AD7490_ptr->AD_7490[AD7490_ptr->device_num].ADC_Data_last;
	HAL_SPI_TransmitReceive_IT(&hspi2,(uint8_t*) &control_register,(uint8_t*) &AD7490_ptr->AD_7490[AD7490_ptr->device_num].ADC_Data_last, 1);
	
	AD7490_ptr->AD_7490[AD7490_ptr->device_num].chan_num++;
  if(AD7490_ptr->AD_7490[AD7490_ptr->device_num].chan_num >15){
		AD7490_ptr->device_num++;
    AD7490_ptr->AD_7490[AD7490_ptr->device_num].chan_num = 0; 
    ad_7490_cs_mask++;
    if(AD7490_ptr->device_num>1) {
      AD7490_ptr->device_num = 0;
      ad_7490_cs_mask = 1;
			AD7490_ptr->AD_7490[AD7490_ptr->device_num].chan_num = 0; 
      }
  }
	
}



