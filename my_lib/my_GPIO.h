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
	unsigned init_flag:1;
	unsigned reserved:15;
}
type_on_off_mask;

typedef struct
{
	type_on_off_mask			 on_of_mask;
	type_gpio_named				 mask_config_named;
}
type_gpio_conf_named;

typedef struct
{
	uint16_t							formater;
	uint32_t 							gpio;
	uint32_t 							gpio_1;
}
gpio_formater;

typedef union
{
	gpio_formater 				gpio;
	type_gpio_conf_named	conf_named;
}
type_gpio_config_union;


typedef struct
{
	uint32_t gpio_Hi;
	uint32_t gpio_Lo;
}
type_gpio_full_stack;
typedef union
{
	uint32_t 					gpio;
	type_gpio_full_stack gpio_stack;
	type_gpio_named		gpio_out_named;
}
type_gpio_out_union;

typedef struct
{
	uint16_t		scaler; 									// +0		1228							scaler; 				
	uint16_t		start; 										// +1		1229              LOW_time;  мкс			
	uint16_t		stop; 										// +2		1230              HIGH_time; мкс			
	uint16_t		end_flag;									// +3		1231              start;					
	uint16_t		process_flag;							// +4		1232              end_flag;				
	uint16_t		LOW_time;									// +5		1233              stop;						
	uint16_t		HIGH_time;								// +6		1234              process_flag;		
	uint16_t		LOW_time_left;						// +7		1235              it_scaler;			
	uint16_t		HIGH_time_left;						// +8		1236              LOW_time_left;	мкс
	uint16_t		it_scaler;								// +9		1237              HIGH_time_left;	мкс
	uint16_t		reserved[4];							// +10	1238/39/40/41     reserved[4];		
	type_gpio_out_union		gpio_out_named; // +14	1242/43/44/45 
}
type_alternative_gpio_out_struct;




typedef union
{
	type_gpio_named 	gpio_in_named;
}
type_gpio_in_union;
#pragma pack(pop)



void my_gpio_init(type_gpio_config_union* gpio_conf);
void my_gpio_set(type_gpio_out_union* gpio_out);
void my_gpio_get(type_gpio_in_union* gpio_in);
void my_gpio_alt_set(type_alternative_gpio_out_struct* gpio_out);





#endif
