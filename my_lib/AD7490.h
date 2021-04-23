#ifndef _AD7490_H
#define _AD7490_H


#include "my_SPI.h"
#define AD7490_NUM 2

typedef struct{
    uint16_t ADC_Data[16];
}
type_AD7490_data;

typedef struct{
    uint16_t ADC_Data;
    uint16_t chan_num;
}
type_AD7490_device;


//void AD7490_read_data(type_AD7490* AD7490_ptr);
void AD_7490_init();
void AD7490_body_read_queue(type_AD7490_device* AD7490_ptr);
void AD7490_start_read(type_AD7490_device* ad7490_ptr);
void AD7490_read_IT_callback(type_AD7490_device* ad7490_ptr);

#endif

