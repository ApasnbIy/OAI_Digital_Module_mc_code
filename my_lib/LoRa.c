#include "LoRa.h"
#include "string.h"






// да простят меня потомки за это
void CS_UP_DOWN(uint16_t pin_num, uint8_t SET_RESET)
{		
		//mb_gpio_outputs.gpio_out_named.gpio33 = 0;
		//mb_gpio_outputs.gpio_full = 0x0FFFFFF0;

	
		if(SET_RESET){
			switch (pin_num)
			{
			case 1:
				mb_gpio_outputs.gpio_out_named.gpio1 = 1;
				break;
			case 2:
				mb_gpio_outputs.gpio_out_named.gpio2 = 1;
				break;
			case 3:
				mb_gpio_outputs.gpio_out_named.gpio3 = 1;
				break;
			case 4:
				mb_gpio_outputs.gpio_out_named.gpio4 = 1;
				break;
			case 5:
				mb_gpio_outputs.gpio_out_named.gpio5 = 1;
				break;
			case 6:
				mb_gpio_outputs.gpio_out_named.gpio6 = 1;
				break;
			case 7:
				mb_gpio_outputs.gpio_out_named.gpio7 = 1;
				break;
			case 8:
				mb_gpio_outputs.gpio_out_named.gpio8 = 1;
				break;
			case 9:
				mb_gpio_outputs.gpio_out_named.gpio9 = 1;
				break;
			case 10:
				mb_gpio_outputs.gpio_out_named.gpio10 = 1;
				break;
			case 11:
				mb_gpio_outputs.gpio_out_named.gpio11 = 1;
				break;
			case 12:
				mb_gpio_outputs.gpio_out_named.gpio12 = 1;
				break;
			case 13:
				mb_gpio_outputs.gpio_out_named.gpio13 = 1;
				break;
			case 14:
				mb_gpio_outputs.gpio_out_named.gpio14 = 1;
				break;
			case 15:
				mb_gpio_outputs.gpio_out_named.gpio15 = 1;
				break;
			case 16:
				mb_gpio_outputs.gpio_out_named.gpio16 = 1;
				break;
			case 17:
				mb_gpio_outputs.gpio_out_named.gpio17 = 1;
				break;
			case 18:
				mb_gpio_outputs.gpio_out_named.gpio18 = 1;
				break;
			case 19:
				mb_gpio_outputs.gpio_out_named.gpio19 = 1;
				break;
			case 20:
				mb_gpio_outputs.gpio_out_named.gpio20 = 1;
				break;
			case 21:
				mb_gpio_outputs.gpio_out_named.gpio21 = 1;
				break;
			case 22:
				mb_gpio_outputs.gpio_out_named.gpio22 = 1;
				break;
			case 23:
				mb_gpio_outputs.gpio_out_named.gpio23 = 1;
				break;
			case 24:
				mb_gpio_outputs.gpio_out_named.gpio24 = 1;
				break;
			case 25:
				mb_gpio_outputs.gpio_out_named.gpio25 = 1;
				break;
			case 26:
				mb_gpio_outputs.gpio_out_named.gpio26 = 1;
				break;
			case 27:
				mb_gpio_outputs.gpio_out_named.gpio27 = 1;
				break;
			case 28:
				mb_gpio_outputs.gpio_out_named.gpio28 = 1;
				break;
			case 29:
				mb_gpio_outputs.gpio_out_named.gpio29 = 1;
				break;
			case 30:
				mb_gpio_outputs.gpio_out_named.gpio30 = 1;
				break;
			case 31:
				mb_gpio_outputs.gpio_out_named.gpio31 = 1;
				break;
			case 32:
				mb_gpio_outputs.gpio_out_named.gpio32 = 1;
				break;
			case 33:
				mb_gpio_outputs.gpio_out_named.gpio33 = 1;
				break;
			case 34:
				mb_gpio_outputs.gpio_out_named.gpio34 = 1;
				break;
			case 35:
				mb_gpio_outputs.gpio_out_named.gpio35 = 1;
				break;
			case 36:
				mb_gpio_outputs.gpio_out_named.gpio36 = 1;
				break;
			case 37:
				mb_gpio_outputs.gpio_out_named.gpio37 = 1;
				break;
			case 38:
				mb_gpio_outputs.gpio_out_named.gpio38 = 1;
				break;
			case 39:
				mb_gpio_outputs.gpio_out_named.gpio39 = 1;
				break;
			case 40:
				mb_gpio_outputs.gpio_out_named.gpio40 = 1;
				break;
			case 41:
				mb_gpio_outputs.gpio_out_named.gpio41 = 1;
				break;
			case 42:
				mb_gpio_outputs.gpio_out_named.gpio42 = 1;
				break;
			case 43:
				mb_gpio_outputs.gpio_out_named.gpio43 = 1;
				break;
			case 44:
				mb_gpio_outputs.gpio_out_named.gpio44 = 1;
				break;
			case 45:
				mb_gpio_outputs.gpio_out_named.gpio45 = 1;
				break;
			case 46:
				mb_gpio_outputs.gpio_out_named.gpio46 = 1;
				break;
			case 47:
				mb_gpio_outputs.gpio_out_named.gpio47 = 1;
				break;
			case 48:
				mb_gpio_outputs.gpio_out_named.gpio48 = 1;
				break;
			case 49:
				mb_gpio_outputs.gpio_out_named.gpio49 = 1;
				break;
			case 50:
				mb_gpio_outputs.gpio_out_named.gpio50 = 1;
				break;
			case 51:
				mb_gpio_outputs.gpio_out_named.gpio51 = 1;
				break;
			case 52:
				mb_gpio_outputs.gpio_out_named.gpio52 = 1;
				break;
			case 53:
				mb_gpio_outputs.gpio_out_named.gpio53 = 1;
				break;
			case 54:
				mb_gpio_outputs.gpio_out_named.gpio54 = 1;
				break;
			case 55:
				mb_gpio_outputs.gpio_out_named.gpio55 = 1;
				break;
			case 56:
				mb_gpio_outputs.gpio_out_named.gpio56 = 1;
				break;
			case 57:
				mb_gpio_outputs.gpio_out_named.gpio57 = 1;
				break;
			case 58:
				mb_gpio_outputs.gpio_out_named.gpio58 = 1;
				break;
			case 59:
				mb_gpio_outputs.gpio_out_named.gpio59 = 1;
				break;
			case 60:
				mb_gpio_outputs.gpio_out_named.gpio60 = 1;
				break;	
			default:
				break;
			}
		}
		else{
			switch (pin_num)
			{
			case 1:
				mb_gpio_outputs.gpio_out_named.gpio1 = 0;
				break;
			case 2:
				mb_gpio_outputs.gpio_out_named.gpio2 = 0;
				break;
			case 3:
				mb_gpio_outputs.gpio_out_named.gpio3 = 0;
				break;
			case 4:
				mb_gpio_outputs.gpio_out_named.gpio4 = 0;
				break;
			case 5:
				mb_gpio_outputs.gpio_out_named.gpio5 = 0;
				break;
			case 6:
				mb_gpio_outputs.gpio_out_named.gpio6 = 0;
				break;
			case 7:
				mb_gpio_outputs.gpio_out_named.gpio7 = 0;
				break;
			case 8:
				mb_gpio_outputs.gpio_out_named.gpio8 = 0;
				break;
			case 9:
				mb_gpio_outputs.gpio_out_named.gpio9 = 0;
				break;
			case 10:
				mb_gpio_outputs.gpio_out_named.gpio10 = 0;
				break;
			case 11:
				mb_gpio_outputs.gpio_out_named.gpio11 = 0;
				break;
			case 12:
				mb_gpio_outputs.gpio_out_named.gpio12 = 0;
				break;
			case 13:
				mb_gpio_outputs.gpio_out_named.gpio13 = 0;
				break;
			case 14:
				mb_gpio_outputs.gpio_out_named.gpio14 = 0;
				break;
			case 15:
				mb_gpio_outputs.gpio_out_named.gpio15 = 0;
				break;
			case 16:
				mb_gpio_outputs.gpio_out_named.gpio16 = 0;
				break;
			case 17:
				mb_gpio_outputs.gpio_out_named.gpio17 = 0;
				break;
			case 18:
				mb_gpio_outputs.gpio_out_named.gpio18 = 0;
				break;
			case 19:
				mb_gpio_outputs.gpio_out_named.gpio19 = 0;
				break;
			case 20:
				mb_gpio_outputs.gpio_out_named.gpio20 = 0;
				break;
			case 21:
				mb_gpio_outputs.gpio_out_named.gpio21 = 0;
				break;
			case 22:
				mb_gpio_outputs.gpio_out_named.gpio22 = 0;
				break;
			case 23:
				mb_gpio_outputs.gpio_out_named.gpio23 = 0;
				break;
			case 24:
				mb_gpio_outputs.gpio_out_named.gpio24 = 0;
				break;
			case 25:
				mb_gpio_outputs.gpio_out_named.gpio25 = 0;
				break;
			case 26:
				mb_gpio_outputs.gpio_out_named.gpio26 = 0;
				break;
			case 27:
				mb_gpio_outputs.gpio_out_named.gpio27 = 0;
				break;
			case 28:
				mb_gpio_outputs.gpio_out_named.gpio28 = 0;
				break;
			case 29:
				mb_gpio_outputs.gpio_out_named.gpio29 = 0;
				break;
			case 30:
				mb_gpio_outputs.gpio_out_named.gpio30 = 0;
				break;
			case 31:
				mb_gpio_outputs.gpio_out_named.gpio31 = 0;
				break;
			case 32:
				mb_gpio_outputs.gpio_out_named.gpio32 = 0;
				break;
			case 33:
				mb_gpio_outputs.gpio_out_named.gpio33 = 0;
				break;
			case 34:
				mb_gpio_outputs.gpio_out_named.gpio34 = 0;
				break;
			case 35:
				mb_gpio_outputs.gpio_out_named.gpio35 = 0;
				break;
			case 36:
				mb_gpio_outputs.gpio_out_named.gpio36 = 0;
				break;
			case 37:
				mb_gpio_outputs.gpio_out_named.gpio37 = 0;
				break;
			case 38:
				mb_gpio_outputs.gpio_out_named.gpio38 = 0;
				break;
			case 39:
				mb_gpio_outputs.gpio_out_named.gpio39 = 0;
				break;
			case 40:
				mb_gpio_outputs.gpio_out_named.gpio40 = 0;
				break;
			case 41:
				mb_gpio_outputs.gpio_out_named.gpio41 = 0;
				break;
			case 42:
				mb_gpio_outputs.gpio_out_named.gpio42 = 0;
				break;
			case 43:
				mb_gpio_outputs.gpio_out_named.gpio43 = 0;
				break;
			case 44:
				mb_gpio_outputs.gpio_out_named.gpio44 = 0;
				break;
			case 45:
				mb_gpio_outputs.gpio_out_named.gpio45 = 0;
				break;
			case 46:
				mb_gpio_outputs.gpio_out_named.gpio46 = 0;
				break;
			case 47:
				mb_gpio_outputs.gpio_out_named.gpio47 = 0;
				break;
			case 48:
				mb_gpio_outputs.gpio_out_named.gpio48 = 0;
				break;
			case 49:
				mb_gpio_outputs.gpio_out_named.gpio49 = 0;
				break;
			case 50:
				mb_gpio_outputs.gpio_out_named.gpio50 = 0;
				break;
			case 51:
				mb_gpio_outputs.gpio_out_named.gpio51 = 0;
				break;
			case 52:
				mb_gpio_outputs.gpio_out_named.gpio52 = 0;
				break;
			case 53:
				mb_gpio_outputs.gpio_out_named.gpio53 = 0;
				break;
			case 54:
				mb_gpio_outputs.gpio_out_named.gpio54 = 0;
				break;
			case 55:
				mb_gpio_outputs.gpio_out_named.gpio55 = 0;
				break;
			case 56:
				mb_gpio_outputs.gpio_out_named.gpio56 = 0;
				break;
			case 57:
				mb_gpio_outputs.gpio_out_named.gpio57 = 0;
				break;
			case 58:
				mb_gpio_outputs.gpio_out_named.gpio58 = 0;
				break;
			case 59:
				mb_gpio_outputs.gpio_out_named.gpio59 = 0;
				break;
			case 60:
				mb_gpio_outputs.gpio_out_named.gpio60 = 0;
				break;	
			default:
				break;
			}
			//mb_gpio_outputs.gpio_full |= 0x01<<(pin_num);
			//mb_gpio_outputs.gpio_out_named.gpio33 = 1;
		}
		
		my_gpio_set(&mb_gpio_outputs);
}




void SPI_RW_routine(type_SPI_RW_data* spi_rw_data, type_SPI_Ansver* spi_answer){
	if(spi_rw_data->SPI_Tranzaction_flag){
		// мы либо в прерывании, либо зашли сюда из-за того что рано пришел новый пакет по ModBus
		// если из-за нового пакета, то надо отсюда вывалиться. потому что рано еще. Если в прерывании и типа заканчивается транзакция то надо все обнулить.
		if(spi_rw_data->scaler == 1){ // попали сюда из-за нового пакета по modbus ничего не надо делать	проигнорировать пока не освободится
		}
		else{//попали потому что прерывание// особо ничего делать не надо
			if(spi_rw_data->SPI_NUM == 0){
					HAL_SPI_Abort_IT(&hspi2);
				}
				else {
					HAL_SPI_Abort_IT(&hspi1);
				}		
			// здесь соответсвенно чип селект снимаем
			CS_UP_DOWN(spi_rw_data->cs_num, 1);
			//memset((uint8_t*) &spi_rw_data->Data, 0, sizeof(spi_rw_data->Data));
			spi_rw_data->SPI_Tranzaction_flag = 0;
		}
	}
	else{ //попали сюда потому что пришел новый пакет и надо бы понять чего делать.
		if(spi_rw_data->scaler == 1){ // попали сюда из-за нового пакета // надо отправить принять и ли что там еще
			// раз будем отправлять, будем делать чипселект
			CS_UP_DOWN(spi_rw_data->cs_num, 0);
			spi_rw_data->SPI_Tranzaction_flag = 1;
			spi_rw_data->scaler = 0;
			switch (spi_rw_data->t_r_flag)
			{
			case 0: // прием
				if(spi_rw_data->SPI_NUM == 0){
					HAL_SPI_Receive_IT(&hspi2, (uint8_t*) &spi_answer->Data, spi_rw_data->Len);
				}
				else {
					HAL_SPI_Receive_IT(&hspi1, (uint8_t*) &spi_answer->Data, spi_rw_data->Len);
				}
				break;
			case 1: // передача
				if(spi_rw_data->SPI_NUM == 0){
					HAL_SPI_Transmit_IT(&hspi2, (uint8_t*) &spi_rw_data->Data, spi_rw_data->Len);
				}
				else {
					HAL_SPI_Transmit_IT(&hspi1, (uint8_t*) &spi_rw_data->Data, spi_rw_data->Len);
				}
				break;
			case 2: // приемопередача
				if(spi_rw_data->SPI_NUM == 0){
					HAL_SPI_TransmitReceive_IT(&hspi2, (uint8_t*) &spi_rw_data->Data, (uint8_t*)&spi_answer->Data, spi_rw_data->Len);
				}
				else {
					HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) &spi_rw_data->Data, (uint8_t*)&spi_answer->Data, spi_rw_data->Len);
				}
				break;	
			default:
				break;
			}
		}
	}	
}
