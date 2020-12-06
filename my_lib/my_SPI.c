#include "my_SPI.h"
#include "spi.h"




void MY_SPI2_Init(type_spi_settings_struct* spi_settings)
{

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
			hspi2.Init.DataSize = SPI_POLARITY_LOW;			
			break;
		case 1:
			hspi2.Init.DataSize = SPI_POLARITY_HIGH;	
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
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
}

void my_spi_default_settings(type_spi_settings_struct* spi_settings){
	spi_settings->mode 		  	= SPI_MODE_MASTER;
	spi_settings->direction 	= SPI_DIRECTION_2LINES;
	spi_settings->data_size	 	= SPI_DATASIZE_8BIT;
	spi_settings->polarity 		= SPI_POLARITY_LOW;
	spi_settings->phase				= SPI_PHASE_1EDGE;
	spi_settings->baud			  = SPI_BAUDRATEPRESCALER_2;
	spi_settings->firs_bit		= SPI_FIRSTBIT_MSB;
	spi_settings->ti_mode			= SPI_TIMODE_DISABLE;
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








