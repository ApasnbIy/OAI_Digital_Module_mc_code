#ifndef _MY_MKO_H
#define _MY_MKO_H

#include "main.h"

typedef struct {
  uint16_t StatWord;  
  uint16_t Data[32];
} typeMKOData;


void MKO_init_command_wires(void);
void MKO_callback(void);
void MKO_config_port_in(void);
void MKO_config_port_out(void);
void MKO_transmitt(void);
void MKO_receive(void);


#endif
