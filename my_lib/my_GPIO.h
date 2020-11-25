#ifndef _MY_GPIO_H
#define _MY_GPIO_H
#include "main.h"
//#include "string.h"

//portC
#define GPIO1  GPIO_PIN_0
#define GPIO2  GPIO_PIN_1
#define GPIO3  GPIO_PIN_2
#define GPIO4  GPIO_PIN_3
#define GPIO5  GPIO_PIN_4
#define GPIO6  GPIO_PIN_5
#define GPIO7  GPIO_PIN_6
#define GPIO8  GPIO_PIN_7
//portE
#define GPIO9  	GPIO_PIN_0
#define GPIO10  GPIO_PIN_1
#define GPIO11  GPIO_PIN_2
#define GPIO12  GPIO_PIN_3
#define GPIO13  GPIO_PIN_4
#define GPIO14  GPIO_PIN_5
#define GPIO15  GPIO_PIN_6
#define GPIO16  GPIO_PIN_7
#define GPIO17  GPIO_PIN_8
#define GPIO18  GPIO_PIN_9
#define GPIO19  GPIO_PIN_10
#define GPIO20  GPIO_PIN_11
#define GPIO21  GPIO_PIN_12
#define GPIO22  GPIO_PIN_13
#define GPIO23  GPIO_PIN_14
#define GPIO24  GPIO_PIN_15
//portG
#define GPIO25 	GPIO_PIN_0
#define GPIO26  GPIO_PIN_1
#define GPIO27  GPIO_PIN_2
#define GPIO28  GPIO_PIN_3
#define GPIO29  GPIO_PIN_4
#define GPIO30  GPIO_PIN_5
#define GPIO31  GPIO_PIN_6
#define GPIO32  GPIO_PIN_7
#define GPIO33  GPIO_PIN_8
#define GPIO34  GPIO_PIN_9
#define GPIO35  GPIO_PIN_10
#define GPIO36  GPIO_PIN_11
#define GPIO37  GPIO_PIN_12
#define GPIO38  GPIO_PIN_13
#define GPIO39  GPIO_PIN_14
#define GPIO40  GPIO_PIN_15
//portD
#define GPIO41  GPIO_PIN_8
#define GPIO42  GPIO_PIN_9
#define GPIO43  GPIO_PIN_10
#define GPIO44  GPIO_PIN_11
#define GPIO45  GPIO_PIN_12
#define GPIO46  GPIO_PIN_13
#define GPIO47  GPIO_PIN_14
#define GPIO48  GPIO_PIN_15
//portF
#define GPIO49  GPIO_PIN_10
#define GPIO50  GPIO_PIN_11
#define GPIO51  GPIO_PIN_12
#define GPIO52  GPIO_PIN_13
#define GPIO53  GPIO_PIN_14
#define GPIO54  GPIO_PIN_15
#define GPIO57 	GPIO_PIN_4
#define GPIO59  GPIO_PIN_2
#define GPIO60  GPIO_PIN_3

//portB
#define GPIO55  GPIO_PIN_8
#define GPIO56  GPIO_PIN_9
#define GPIO58	GPIO_PIN_11
	
#pragma pack(push, 1)

typedef struct
{	
	
	unsigned gpio12:1;
	unsigned gpio11:1;
	unsigned gpio10:1;
	unsigned gpio9:1;
	unsigned gpio8:1;
	unsigned gpio7:1;
	unsigned gpio6:1;
	unsigned gpio5:1;
	unsigned gpio4:1;
	unsigned gpio3:1;
	unsigned gpio2:1;
	unsigned gpio1:1;
	unsigned data_updater:		4;
	
	unsigned gpio28:1;
	unsigned gpio27:1;
	unsigned gpio26:1;
	unsigned gpio25:1;	
	unsigned gpio24:1;
	unsigned gpio23:1;
	unsigned gpio22:1;
	unsigned gpio21:1;
	unsigned gpio20:1;
	unsigned gpio19:1;
	unsigned gpio18:1;
	unsigned gpio17:1;
	unsigned gpio16:1;
	unsigned gpio15:1;
	unsigned gpio14:1;
	unsigned gpio13:1;
	
	unsigned gpio44:1;
	unsigned gpio43:1;
	unsigned gpio42:1;
	unsigned gpio41:1;
	unsigned gpio40:1;
	unsigned gpio39:1;
	unsigned gpio38:1;
	unsigned gpio37:1;
	unsigned gpio36:1;
	unsigned gpio35:1;
	unsigned gpio34:1;
	unsigned gpio33:1;
	unsigned gpio32:1;
	unsigned gpio31:1;
	unsigned gpio30:1;
	unsigned gpio29:1;
	
	unsigned gpio60:1;
	unsigned gpio59:1;
	unsigned gpio58:1;
	unsigned gpio57:1;
	unsigned gpio56:1;
	unsigned gpio55:1;
	unsigned gpio54:1;
	unsigned gpio53:1;
	unsigned gpio52:1;
	unsigned gpio51:1;
	unsigned gpio50:1;
	unsigned gpio49:1;
	unsigned gpio48:1;
	unsigned gpio47:1;
	unsigned gpio46:1;
	unsigned gpio45:1;
	
}
type_gpio_named; // 64 bits

typedef struct
{	// using port flags
	
	unsigned portC:1;
	unsigned portE:1;
	unsigned portG:1;
	unsigned portD:1;
	unsigned portF:1;
	unsigned portB:1;
	unsigned reserved:1;
	unsigned init_flag:1;
	unsigned update_scaler:8;
}
type_on_off_mask;

typedef struct
{
	
	type_on_off_mask			 on_of_mask;
	type_gpio_named				 mask_config_named;
}
type_gpio_conf_named;

typedef union
{
	//type_gpio_conf				conf;
	type_gpio_conf_named	conf_named;
}
type_gpio_config_union;


/*
typedef struct
{
	// if input - result
	unsigned portC_in:8;	// 1 - 8								// 0xFF
	unsigned portE_in:16;	// 9 - 24								// 0xFFFF
	unsigned portG_in:16;	// 25 - 40							// 0xFFFF	
	unsigned portD_in:8;  // 41 - 48							// 0xFF
	unsigned portF_in:9; 	// 49 - 54, 57, 59, 60	// 0x1FF
	unsigned portB_in:3; 	// 55, 56, 58						// 0x7	
	unsigned data_updater:		3;									// 0x7
	unsigned init_flag:	1;												// 0x1
}
type_gpio_in; //64 bits

typedef struct
{
	// if output - state
	unsigned portC_out:8;	// 1 - 8
	unsigned portE_out:16;	// 9 - 24
	unsigned portG_out:16;	// 25 - 40
	unsigned portD_out:8;  // 41 - 48
	unsigned portF_out:9; 	// 49 - 54, 57, 59, 60
	unsigned portB_out:3; 	// 55, 56, 58	
	unsigned data_updater:		3;
	unsigned init_flag:	1;
}
type_gpio_out;
*/


typedef union
{
	//type_gpio_out		gpio_out;
	type_gpio_named		gpio_out_named;
}
type_gpio_out_union;

typedef union
{
	//type_gpio_in		gpio_in;
	type_gpio_named 	gpio_in_named;
}
type_gpio_in_union;
#pragma pack(pop)



void my_gpio_init(type_gpio_config_union* gpio_conf);
void my_gpio_set(type_gpio_out_union* gpio_out);
void my_gpio_get(type_gpio_in_union* gpio_in);





#endif
