#ifndef _MY_SPI_H
#define _MY_SPI_H

#include "main.h"

typedef struct
{
	uint16_t	scaler;
	uint16_t  reserved;
}
type_spi_settings_struct;

typedef struct
{
	uint16_t reserved;
}
type_spi_transmit_struct;

typedef struct
{
	uint16_t reserved;
}
type_spi_recive_struct;

#endif

