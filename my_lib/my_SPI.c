#include "my_SPI.h"
#include "spi.h"





void MY_SPI2_Init(type_spi_settings_struct* spi_settings)
{
	HAL_SPI_DeInit(&hspi2);
 	hspi2.Instance = SPI2;
	switch (spi_settings->mode){
		case 0:
			hspi2.Init.Mode = SPI_MODE_MASTER;
			break;
		case 1:
			hspi2.Init.Mode = SPI_MODE_SLAVE;
			break;
	}
	
	
  switch (spi_settings->direction){
		case 0:
			hspi2.Init.Direction = SPI_DIRECTION_2LINES;
			break;
		case 1:
			hspi2.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
			break;
		case 2:
			hspi2.Init.Mode = SPI_DIRECTION_1LINE;
			break;
	}
	
	switch (spi_settings->data_size){
		case 0:
			hspi2.Init.DataSize = SPI_DATASIZE_8BIT;			
			break;
		case 1:
			hspi2.Init.DataSize = SPI_DATASIZE_16BIT;	
			break;
	}
	
  switch (spi_settings->polarity){
		case 0:
			hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;			
			break;
		case 1:
			hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;	
			break;
	}
	switch (spi_settings->phase){
		case 0:
			hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
			break;
		case 1:
			hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
			break;
	}
	
	
  hspi2.Init.NSS = SPI_NSS_SOFT;
	
	switch (spi_settings->baud){
		case 0:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
			break;
		case 1:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
			break;
		case 2:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
			break;
		case 3:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;	
			break;
		case 4:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
			break;
		case 5:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;	
			break;
		case 6:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
			break;
		case 7:
			hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
			break;
		
	}
	
	switch (spi_settings->firs_bit){
		case 0:
			hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
			break;
		case 1:
			hspi2.Init.FirstBit = SPI_FIRSTBIT_LSB;
			break;
	}
	
	switch (spi_settings->ti_mode){
		case 0:
			hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
			break;
		case 1:
			hspi2.Init.TIMode = SPI_TIMODE_ENABLE;
			break;
	}
	
  
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
	HAL_SPI_MspInit(&hspi2);
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
	
}

void my_spi_default_settings(type_spi_settings_struct* spi_settings){
	spi_settings->mode 		  	= 0;//SPI_MODE_MASTER;
	spi_settings->direction 	= 0;//SPI_DIRECTION_2LINES;
	spi_settings->data_size	 	= 1;//SPI_DATASIZE_16BIT;
	spi_settings->polarity 		= 0;//SPI_POLARITY_LOW;
	spi_settings->phase				= 1;//SPI_PHASE_2EDGE;
	spi_settings->baud			  = 4;//SPI_BAUDRATEPRESCALER_64;
	spi_settings->firs_bit		= 0;//SPI_FIRSTBIT_MSB;
	spi_settings->ti_mode			= 0;//SPI_TIMODE_DISABLE;
}
		

void my_spi_transmit(type_spi_transmit_struct* spi_transmit)
{
	HAL_SPI_Transmit_IT(&hspi2, (uint8_t*) &spi_transmit->data, spi_transmit->len);
}


void my_spi_receive(type_spi_receive_struct* spi_receive, type_spi_receive_data* spi_receive_data)
{
	HAL_SPI_Receive_IT(&hspi2, (uint8_t*) &spi_receive_data->data, spi_receive->len);
}

void my_spi_transmit_recive(type_spi_receive_data* spi_receive_data, type_spi_transmit_struct* spi_transmit_str){
	HAL_SPI_TransmitReceive_IT(&hspi2,(uint8_t*) spi_transmit_str->data, (uint8_t*) spi_receive_data->data, spi_transmit_str->len);
}

void my_spi_chip_select_init(type_spi_chipselect_settings* chip_select_init, type_gpio_config_union* gpio_cnfg_union)
{
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_1));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_2));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_3));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_4));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_5));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_6));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_7));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_8));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_9));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_10));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_11));
	gpio_cnfg_union->gpio.gpio |= (1 << (12 - chip_select_init->cs_12));
	my_gpio_init(gpio_cnfg_union);
	chip_select_init->init_flag = 1;
}











void my_spi_chip_deselect(uint16_t* chip_mask, type_spi_chipselect_settings* chip_select_init, type_gpio_out_union* gpio_out)
{
	//volatile uint16_t temp_chip_mask = spi_transmit->chip_mask;
	if(*chip_mask  & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_1);
	}
	 if((*chip_mask>>1) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_2);
	}
	 if((*chip_mask>>2) & 0x01){
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_3);
	}
	 if((*chip_mask>>3) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_4);
	}
	 if((*chip_mask>>4) & 0x01){
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_5);
	}
	 if((*chip_mask>>5) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_6);
	}
	 if((*chip_mask>>6) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_7);
	}
	 if((*chip_mask>>7) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_8);
	}
	 if((*chip_mask>>8) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_9);
	}
	 if((*chip_mask>>9) & 0x01) {
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_10);
	}
	 if((*chip_mask>>10) & 0x01){
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_11);
	}
	 if((*chip_mask>>11) & 0x01){
		gpio_out->gpio |= 1 << (12 - chip_select_init->cs_12);
	}
	my_gpio_set(gpio_out);
}

void my_spi_chip_select(uint16_t* chip_mask, type_spi_chipselect_settings* chip_select_init, type_gpio_out_union* gpio_out)
{
	if((*chip_mask>>0) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_1));
	}
	 if((*chip_mask>>1) & 0x01) {
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_2));
	}
	 if((*chip_mask>>2) & 0x01) {
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_3));
	}
	 if((*chip_mask>>3) & 0x01) {
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_4));
	}
	 if((*chip_mask>>4) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_5));
	}
	 if((*chip_mask>>5) & 0x01) {
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_6));
	}
	 if((*chip_mask>>6) & 0x01) {
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_7));
	}
	 if((*chip_mask>>7) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_8));
	}
	 if((*chip_mask>>8) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_9));
	}
	 if((*chip_mask>>9) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_10));
	}
	 if((*chip_mask>>10) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_11));
	}
	 if((*chip_mask>>11) & 0x01){
		gpio_out->gpio &= ~(1 << (12 - chip_select_init->cs_12));
	}
	my_gpio_set(gpio_out);
}
