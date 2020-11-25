#include "my_GPIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include <string.h>


void my_gpio_init(type_gpio_config_union* gpio_conf){
	gpio_conf->conf_named.on_of_mask.init_flag = 0;
	volatile int PIN_IN = 0;
	volatile int PIN_OUT = 0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	if(gpio_conf->conf_named.on_of_mask.portB ==1){
		(gpio_conf->conf_named.mask_config_named.gpio55 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO55) : (PIN_IN = PIN_IN|GPIO55);
		(gpio_conf->conf_named.mask_config_named.gpio56 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO56) : (PIN_IN = PIN_IN|GPIO56);
		(gpio_conf->conf_named.mask_config_named.gpio58 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO58) : (PIN_IN = PIN_IN|GPIO58);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	if(gpio_conf->conf_named.on_of_mask.portC ==1){
		(gpio_conf->conf_named.mask_config_named.gpio1 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO1) : (PIN_IN = PIN_IN|GPIO1);
		(gpio_conf->conf_named.mask_config_named.gpio2 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO2) : (PIN_IN = PIN_IN|GPIO2);
		(gpio_conf->conf_named.mask_config_named.gpio3 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO3) : (PIN_IN = PIN_IN|GPIO3);
		(gpio_conf->conf_named.mask_config_named.gpio4 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO4) : (PIN_IN = PIN_IN|GPIO4);
		(gpio_conf->conf_named.mask_config_named.gpio5 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO5) : (PIN_IN = PIN_IN|GPIO5);
		(gpio_conf->conf_named.mask_config_named.gpio6 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO6) : (PIN_IN = PIN_IN|GPIO6);
		(gpio_conf->conf_named.mask_config_named.gpio7 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO7) : (PIN_IN = PIN_IN|GPIO7);
		(gpio_conf->conf_named.mask_config_named.gpio8 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO8) : (PIN_IN = PIN_IN|GPIO8);
		if(PIN_OUT!=0){                                                
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	if(gpio_conf->conf_named.on_of_mask.portD ==1){
		(gpio_conf->conf_named.mask_config_named.gpio41 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO41) : (PIN_IN = PIN_IN|GPIO41);
		(gpio_conf->conf_named.mask_config_named.gpio42 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO42) : (PIN_IN = PIN_IN|GPIO42);
		(gpio_conf->conf_named.mask_config_named.gpio43 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO43) : (PIN_IN = PIN_IN|GPIO43);
		(gpio_conf->conf_named.mask_config_named.gpio44 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO44) : (PIN_IN = PIN_IN|GPIO44);
		(gpio_conf->conf_named.mask_config_named.gpio45 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO45) : (PIN_IN = PIN_IN|GPIO45);
		(gpio_conf->conf_named.mask_config_named.gpio46 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO46) : (PIN_IN = PIN_IN|GPIO46);
		(gpio_conf->conf_named.mask_config_named.gpio47 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO47) : (PIN_IN = PIN_IN|GPIO47);
		(gpio_conf->conf_named.mask_config_named.gpio48 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO48) : (PIN_IN = PIN_IN|GPIO48);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		}
	}		
	PIN_IN = 0;
	PIN_OUT = 0;
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	if(gpio_conf->conf_named.on_of_mask.portE ==1){
		(gpio_conf->conf_named.mask_config_named.gpio9  && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO9 ) :  (PIN_IN = PIN_IN|GPIO9);
		(gpio_conf->conf_named.mask_config_named.gpio10 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO10) : (PIN_IN = PIN_IN|GPIO10);
		(gpio_conf->conf_named.mask_config_named.gpio11 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO11) : (PIN_IN = PIN_IN|GPIO11);
		(gpio_conf->conf_named.mask_config_named.gpio12 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO12) : (PIN_IN = PIN_IN|GPIO12);
		(gpio_conf->conf_named.mask_config_named.gpio13 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO13) : (PIN_IN = PIN_IN|GPIO13);
		(gpio_conf->conf_named.mask_config_named.gpio14 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO14) : (PIN_IN = PIN_IN|GPIO14);
		(gpio_conf->conf_named.mask_config_named.gpio15 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO15) : (PIN_IN = PIN_IN|GPIO15);
		(gpio_conf->conf_named.mask_config_named.gpio16 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO16) : (PIN_IN = PIN_IN|GPIO16);
		(gpio_conf->conf_named.mask_config_named.gpio17 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO17) : (PIN_IN = PIN_IN|GPIO17);
		(gpio_conf->conf_named.mask_config_named.gpio18 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO18) : (PIN_IN = PIN_IN|GPIO18);
		(gpio_conf->conf_named.mask_config_named.gpio19 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO19) : (PIN_IN = PIN_IN|GPIO19);
		(gpio_conf->conf_named.mask_config_named.gpio20 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO20) : (PIN_IN = PIN_IN|GPIO20);
		(gpio_conf->conf_named.mask_config_named.gpio21 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO21) : (PIN_IN = PIN_IN|GPIO21);
		(gpio_conf->conf_named.mask_config_named.gpio22 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO22) : (PIN_IN = PIN_IN|GPIO22);
		(gpio_conf->conf_named.mask_config_named.gpio23 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO23) : (PIN_IN = PIN_IN|GPIO23);
		(gpio_conf->conf_named.mask_config_named.gpio24 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO24) : (PIN_IN = PIN_IN|GPIO24);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		}
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	if(gpio_conf->conf_named.on_of_mask.portF ==1){
		(gpio_conf->conf_named.mask_config_named.gpio49 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO49) : (PIN_IN = PIN_IN|GPIO49);
		(gpio_conf->conf_named.mask_config_named.gpio50 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO50) : (PIN_IN = PIN_IN|GPIO50);
		(gpio_conf->conf_named.mask_config_named.gpio51 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO51) : (PIN_IN = PIN_IN|GPIO51);
		(gpio_conf->conf_named.mask_config_named.gpio52 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO52) : (PIN_IN = PIN_IN|GPIO52);
		(gpio_conf->conf_named.mask_config_named.gpio53 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO53) : (PIN_IN = PIN_IN|GPIO53);
		(gpio_conf->conf_named.mask_config_named.gpio54 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO54) : (PIN_IN = PIN_IN|GPIO54);
		(gpio_conf->conf_named.mask_config_named.gpio57 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO57) : (PIN_IN = PIN_IN|GPIO57);
		(gpio_conf->conf_named.mask_config_named.gpio59 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO59) : (PIN_IN = PIN_IN|GPIO59);
		(gpio_conf->conf_named.mask_config_named.gpio60 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO60) : (PIN_IN = PIN_IN|GPIO60);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		}
	
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	if(gpio_conf->conf_named.on_of_mask.portG ==1){
		(gpio_conf->conf_named.mask_config_named.gpio25 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO25) : (PIN_IN = PIN_IN|GPIO25);
		(gpio_conf->conf_named.mask_config_named.gpio26 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO26) : (PIN_IN = PIN_IN|GPIO26);
		(gpio_conf->conf_named.mask_config_named.gpio27 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO27) : (PIN_IN = PIN_IN|GPIO27);
		(gpio_conf->conf_named.mask_config_named.gpio28 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO28) : (PIN_IN = PIN_IN|GPIO28);
		(gpio_conf->conf_named.mask_config_named.gpio29 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO29) : (PIN_IN = PIN_IN|GPIO29);
		(gpio_conf->conf_named.mask_config_named.gpio30 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO30) : (PIN_IN = PIN_IN|GPIO30);
		(gpio_conf->conf_named.mask_config_named.gpio31 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO31) : (PIN_IN = PIN_IN|GPIO31);
		(gpio_conf->conf_named.mask_config_named.gpio32 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO32) : (PIN_IN = PIN_IN|GPIO32);
		(gpio_conf->conf_named.mask_config_named.gpio33 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO33) : (PIN_IN = PIN_IN|GPIO33);
		(gpio_conf->conf_named.mask_config_named.gpio34 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO34) : (PIN_IN = PIN_IN|GPIO34);
		(gpio_conf->conf_named.mask_config_named.gpio35 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO35) : (PIN_IN = PIN_IN|GPIO35);
		(gpio_conf->conf_named.mask_config_named.gpio36 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO36) : (PIN_IN = PIN_IN|GPIO36);
		(gpio_conf->conf_named.mask_config_named.gpio37 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO37) : (PIN_IN = PIN_IN|GPIO37);
		(gpio_conf->conf_named.mask_config_named.gpio38 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO38) : (PIN_IN = PIN_IN|GPIO38);
		(gpio_conf->conf_named.mask_config_named.gpio39 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO39) : (PIN_IN = PIN_IN|GPIO39);
		(gpio_conf->conf_named.mask_config_named.gpio40 && 0x01 ) ? (PIN_OUT = PIN_OUT|GPIO40) : (PIN_IN = PIN_IN|GPIO40);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
		}
	}
	gpio_conf->conf_named.on_of_mask.init_flag = 1;
}

void my_gpio_set(type_gpio_out_union* gpio_out)
{
	volatile int PIN_HIGH = 0;
	volatile int PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio1 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO1) : (PIN_LOW = PIN_LOW|GPIO1);
	(gpio_out->gpio_out_named.gpio2 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO2) : (PIN_LOW = PIN_LOW|GPIO2);
	(gpio_out->gpio_out_named.gpio3 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO3) : (PIN_LOW = PIN_LOW|GPIO3);
	(gpio_out->gpio_out_named.gpio4 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO4) : (PIN_LOW = PIN_LOW|GPIO4);
	(gpio_out->gpio_out_named.gpio5 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO5) : (PIN_LOW = PIN_LOW|GPIO5);
	(gpio_out->gpio_out_named.gpio6 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO6) : (PIN_LOW = PIN_LOW|GPIO6);
	(gpio_out->gpio_out_named.gpio7 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO7) : (PIN_LOW = PIN_LOW|GPIO7);
	(gpio_out->gpio_out_named.gpio8 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO8) : (PIN_LOW = PIN_LOW|GPIO8);
	HAL_GPIO_WritePin (GPIOC,PIN_LOW ,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOC,PIN_HIGH ,GPIO_PIN_SET);
	
	PIN_HIGH = 0;
	PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio9  && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO9) : (PIN_LOW = PIN_LOW|GPIO9);
	(gpio_out->gpio_out_named.gpio10 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO10) : (PIN_LOW = PIN_LOW|GPIO10);
	(gpio_out->gpio_out_named.gpio11 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO11) : (PIN_LOW = PIN_LOW|GPIO11);
	(gpio_out->gpio_out_named.gpio12 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO12) : (PIN_LOW = PIN_LOW|GPIO12);
	(gpio_out->gpio_out_named.gpio13 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO13) : (PIN_LOW = PIN_LOW|GPIO13);
	(gpio_out->gpio_out_named.gpio14 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO14) : (PIN_LOW = PIN_LOW|GPIO14);
	(gpio_out->gpio_out_named.gpio15 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO15) : (PIN_LOW = PIN_LOW|GPIO15);
	(gpio_out->gpio_out_named.gpio16 && 0x01  ) ? (PIN_HIGH = PIN_HIGH|GPIO16) : (PIN_LOW = PIN_LOW|GPIO16);
	(gpio_out->gpio_out_named.gpio17 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO17) : (PIN_LOW = PIN_LOW|GPIO17);
	(gpio_out->gpio_out_named.gpio18 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO18) : (PIN_LOW = PIN_LOW|GPIO18);
	(gpio_out->gpio_out_named.gpio19 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO19) : (PIN_LOW = PIN_LOW|GPIO19);
	(gpio_out->gpio_out_named.gpio20 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO20) : (PIN_LOW = PIN_LOW|GPIO20);
	(gpio_out->gpio_out_named.gpio21 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO21) : (PIN_LOW = PIN_LOW|GPIO21);
	(gpio_out->gpio_out_named.gpio22 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO22) : (PIN_LOW = PIN_LOW|GPIO22);
	(gpio_out->gpio_out_named.gpio23 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO23) : (PIN_LOW = PIN_LOW|GPIO23);
	(gpio_out->gpio_out_named.gpio24 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO24) : (PIN_LOW = PIN_LOW|GPIO24);
	HAL_GPIO_WritePin (GPIOE,PIN_LOW ,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOE,PIN_HIGH ,GPIO_PIN_SET);
	
	PIN_HIGH = 0;
	PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio25 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO25) : (PIN_LOW = PIN_LOW|GPIO25);
	(gpio_out->gpio_out_named.gpio26 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO26) : (PIN_LOW = PIN_LOW|GPIO26);
	(gpio_out->gpio_out_named.gpio27 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO27) : (PIN_LOW = PIN_LOW|GPIO27);
	(gpio_out->gpio_out_named.gpio28 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO28) : (PIN_LOW = PIN_LOW|GPIO28);
	(gpio_out->gpio_out_named.gpio29 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO29) : (PIN_LOW = PIN_LOW|GPIO29);
	(gpio_out->gpio_out_named.gpio30 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO30) : (PIN_LOW = PIN_LOW|GPIO30);
	(gpio_out->gpio_out_named.gpio31 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO31) : (PIN_LOW = PIN_LOW|GPIO31);
	(gpio_out->gpio_out_named.gpio32 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO32) : (PIN_LOW = PIN_LOW|GPIO32);
	(gpio_out->gpio_out_named.gpio33 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO33) : (PIN_LOW = PIN_LOW|GPIO33);
	(gpio_out->gpio_out_named.gpio34 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO34) : (PIN_LOW = PIN_LOW|GPIO34);
	(gpio_out->gpio_out_named.gpio35 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO35) : (PIN_LOW = PIN_LOW|GPIO35);
	(gpio_out->gpio_out_named.gpio36 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO36) : (PIN_LOW = PIN_LOW|GPIO36);
	(gpio_out->gpio_out_named.gpio37 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO37) : (PIN_LOW = PIN_LOW|GPIO37);
	(gpio_out->gpio_out_named.gpio38 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO38) : (PIN_LOW = PIN_LOW|GPIO38);
	(gpio_out->gpio_out_named.gpio39 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO39) : (PIN_LOW = PIN_LOW|GPIO39);
	(gpio_out->gpio_out_named.gpio40 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO40) : (PIN_LOW = PIN_LOW|GPIO40);
	HAL_GPIO_WritePin (GPIOG,PIN_LOW ,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOG,PIN_HIGH ,GPIO_PIN_SET);
	
	PIN_HIGH = 0;
	PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio41 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO41) : (PIN_LOW = PIN_LOW|GPIO41);
	(gpio_out->gpio_out_named.gpio42 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO42) : (PIN_LOW = PIN_LOW|GPIO42);
	(gpio_out->gpio_out_named.gpio43 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO43) : (PIN_LOW = PIN_LOW|GPIO43);
	(gpio_out->gpio_out_named.gpio44 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO44) : (PIN_LOW = PIN_LOW|GPIO44);
	(gpio_out->gpio_out_named.gpio45 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO45) : (PIN_LOW = PIN_LOW|GPIO45);
	(gpio_out->gpio_out_named.gpio46 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO46) : (PIN_LOW = PIN_LOW|GPIO46);
	(gpio_out->gpio_out_named.gpio47 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO47) : (PIN_LOW = PIN_LOW|GPIO47);
	(gpio_out->gpio_out_named.gpio48 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO48) : (PIN_LOW = PIN_LOW|GPIO48);
	HAL_GPIO_WritePin (GPIOD,PIN_LOW,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOD,PIN_HIGH ,GPIO_PIN_SET);
	
	PIN_HIGH = 0;
	PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio49 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO49) : (PIN_LOW = PIN_LOW|GPIO49);
	(gpio_out->gpio_out_named.gpio50 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO50) : (PIN_LOW = PIN_LOW|GPIO50);
	(gpio_out->gpio_out_named.gpio51 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO51) : (PIN_LOW = PIN_LOW|GPIO51);
	(gpio_out->gpio_out_named.gpio52 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO52) : (PIN_LOW = PIN_LOW|GPIO52);
	(gpio_out->gpio_out_named.gpio53 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO53) : (PIN_LOW = PIN_LOW|GPIO53);
	(gpio_out->gpio_out_named.gpio54 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO54) : (PIN_LOW = PIN_LOW|GPIO54);
	(gpio_out->gpio_out_named.gpio57 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO57) : (PIN_LOW = PIN_LOW|GPIO57);
	(gpio_out->gpio_out_named.gpio59 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO59) : (PIN_LOW = PIN_LOW|GPIO59);
	(gpio_out->gpio_out_named.gpio60 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO60) : (PIN_LOW = PIN_LOW|GPIO60);
	HAL_GPIO_WritePin (GPIOF,PIN_LOW ,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOF,PIN_HIGH ,GPIO_PIN_SET);
	
	PIN_HIGH = 0;
	PIN_LOW = 0;
	(gpio_out->gpio_out_named.gpio55 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO55) : (PIN_LOW = PIN_LOW|GPIO55);
	(gpio_out->gpio_out_named.gpio56 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO56) : (PIN_LOW = PIN_LOW|GPIO56);
	(gpio_out->gpio_out_named.gpio58 && 0x01 ) ? (PIN_HIGH = PIN_HIGH|GPIO58) : (PIN_LOW = PIN_LOW|GPIO58);
	HAL_GPIO_WritePin (GPIOB,PIN_LOW ,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB,PIN_HIGH ,GPIO_PIN_SET);	
}
	
void my_gpio_get(type_gpio_in_union* gpio_in)	
{
	(GPIOC -> IDR & GPIO1)	? (gpio_in->gpio_in_named.gpio1 = 0x01) : (gpio_in->gpio_in_named.gpio1 = 0x00);
	(GPIOC -> IDR & GPIO2)	? (gpio_in->gpio_in_named.gpio2 = 0x01) : (gpio_in->gpio_in_named.gpio2 = 0x00);
	(GPIOC -> IDR & GPIO3)	? (gpio_in->gpio_in_named.gpio3 = 0x01) : (gpio_in->gpio_in_named.gpio3 = 0x00);
	(GPIOC -> IDR & GPIO4)	? (gpio_in->gpio_in_named.gpio4 = 0x01) : (gpio_in->gpio_in_named.gpio4 = 0x00);
	(GPIOC -> IDR & GPIO5)	? (gpio_in->gpio_in_named.gpio5 = 0x01) : (gpio_in->gpio_in_named.gpio5 = 0x00);
	(GPIOC -> IDR & GPIO6)	? (gpio_in->gpio_in_named.gpio6 = 0x01) : (gpio_in->gpio_in_named.gpio6 = 0x00);
	(GPIOC -> IDR & GPIO7)	? (gpio_in->gpio_in_named.gpio7 = 0x01) : (gpio_in->gpio_in_named.gpio7 = 0x00);
	(GPIOC -> IDR & GPIO8)	? (gpio_in->gpio_in_named.gpio8 = 0x01) : (gpio_in->gpio_in_named.gpio8 = 0x00);

	(GPIOE -> IDR & GPIO9  )	? (gpio_in->gpio_in_named.gpio9  = 0x01) : (gpio_in->gpio_in_named.gpio9  = 0x00);
	(GPIOE -> IDR & GPIO10 )	? (gpio_in->gpio_in_named.gpio10 = 0x01) : (gpio_in->gpio_in_named.gpio10 = 0x00);
	(GPIOE -> IDR & GPIO11 )	? (gpio_in->gpio_in_named.gpio11 = 0x01) : (gpio_in->gpio_in_named.gpio11 = 0x00);
	(GPIOE -> IDR & GPIO12 )	? (gpio_in->gpio_in_named.gpio12 = 0x01) : (gpio_in->gpio_in_named.gpio12 = 0x00);
	(GPIOE -> IDR & GPIO13 )	? (gpio_in->gpio_in_named.gpio13 = 0x01) : (gpio_in->gpio_in_named.gpio13 = 0x00);
	(GPIOE -> IDR & GPIO14 )	? (gpio_in->gpio_in_named.gpio14 = 0x01) : (gpio_in->gpio_in_named.gpio14 = 0x00);
	(GPIOE -> IDR & GPIO15 )	? (gpio_in->gpio_in_named.gpio15 = 0x01) : (gpio_in->gpio_in_named.gpio15 = 0x00);
	(GPIOE -> IDR & GPIO16 )	? (gpio_in->gpio_in_named.gpio16 = 0x01) : (gpio_in->gpio_in_named.gpio16 = 0x00);
	(GPIOE -> IDR & GPIO17 )	? (gpio_in->gpio_in_named.gpio17 = 0x01) : (gpio_in->gpio_in_named.gpio17 = 0x00);
	(GPIOE -> IDR & GPIO18 )	? (gpio_in->gpio_in_named.gpio18 = 0x01) : (gpio_in->gpio_in_named.gpio18 = 0x00);
	(GPIOE -> IDR & GPIO19 )	? (gpio_in->gpio_in_named.gpio19 = 0x01) : (gpio_in->gpio_in_named.gpio19 = 0x00);
	(GPIOE -> IDR & GPIO20 )	? (gpio_in->gpio_in_named.gpio20 = 0x01) : (gpio_in->gpio_in_named.gpio20 = 0x00);
	(GPIOE -> IDR & GPIO21 )	? (gpio_in->gpio_in_named.gpio21 = 0x01) : (gpio_in->gpio_in_named.gpio21 = 0x00);
	(GPIOE -> IDR & GPIO22 )	? (gpio_in->gpio_in_named.gpio22 = 0x01) : (gpio_in->gpio_in_named.gpio22 = 0x00);
	(GPIOE -> IDR & GPIO23 )	? (gpio_in->gpio_in_named.gpio23 = 0x01) : (gpio_in->gpio_in_named.gpio23 = 0x00);
	(GPIOE -> IDR & GPIO24 )	? (gpio_in->gpio_in_named.gpio24 = 0x01) : (gpio_in->gpio_in_named.gpio24 = 0x00);
	
	(GPIOG -> IDR & GPIO25 )	? (gpio_in->gpio_in_named.gpio25 = 0x01) : (gpio_in->gpio_in_named.gpio25 = 0x00);
	(GPIOG -> IDR & GPIO26 )	? (gpio_in->gpio_in_named.gpio26 = 0x01) : (gpio_in->gpio_in_named.gpio26 = 0x00);
	(GPIOG -> IDR & GPIO27 )	? (gpio_in->gpio_in_named.gpio27 = 0x01) : (gpio_in->gpio_in_named.gpio27 = 0x00);
	(GPIOG -> IDR & GPIO28 )	? (gpio_in->gpio_in_named.gpio28 = 0x01) : (gpio_in->gpio_in_named.gpio28 = 0x00);
	(GPIOG -> IDR & GPIO29 )	? (gpio_in->gpio_in_named.gpio29 = 0x01) : (gpio_in->gpio_in_named.gpio29 = 0x00);
	(GPIOG -> IDR & GPIO30 )	? (gpio_in->gpio_in_named.gpio30 = 0x01) : (gpio_in->gpio_in_named.gpio30 = 0x00);
	(GPIOG -> IDR & GPIO31 )	? (gpio_in->gpio_in_named.gpio31 = 0x01) : (gpio_in->gpio_in_named.gpio31 = 0x00);
	(GPIOG -> IDR & GPIO32 )	? (gpio_in->gpio_in_named.gpio32 = 0x01) : (gpio_in->gpio_in_named.gpio32 = 0x00);
	(GPIOG -> IDR & GPIO33 )	? (gpio_in->gpio_in_named.gpio33 = 0x01) : (gpio_in->gpio_in_named.gpio33 = 0x00);
	(GPIOG -> IDR & GPIO34 )	? (gpio_in->gpio_in_named.gpio34 = 0x01) : (gpio_in->gpio_in_named.gpio34 = 0x00);
	(GPIOG -> IDR & GPIO35 )	? (gpio_in->gpio_in_named.gpio35 = 0x01) : (gpio_in->gpio_in_named.gpio35 = 0x00);
	(GPIOG -> IDR & GPIO36 )	? (gpio_in->gpio_in_named.gpio36 = 0x01) : (gpio_in->gpio_in_named.gpio36 = 0x00);
	(GPIOG -> IDR & GPIO37 )	? (gpio_in->gpio_in_named.gpio37 = 0x01) : (gpio_in->gpio_in_named.gpio37 = 0x00);
	(GPIOG -> IDR & GPIO38 )	? (gpio_in->gpio_in_named.gpio38 = 0x01) : (gpio_in->gpio_in_named.gpio38 = 0x00);
	(GPIOG -> IDR & GPIO39 )	? (gpio_in->gpio_in_named.gpio39 = 0x01) : (gpio_in->gpio_in_named.gpio39 = 0x00);
	(GPIOG -> IDR & GPIO40 )	? (gpio_in->gpio_in_named.gpio40 = 0x01) : (gpio_in->gpio_in_named.gpio40 = 0x00);
	
	(GPIOD -> IDR & GPIO41 )	? (gpio_in->gpio_in_named.gpio41 = 0x01) : (gpio_in->gpio_in_named.gpio41 = 0x00);
	(GPIOD -> IDR & GPIO42 )	? (gpio_in->gpio_in_named.gpio42 = 0x01) : (gpio_in->gpio_in_named.gpio42 = 0x00);
	(GPIOD -> IDR & GPIO43 )	? (gpio_in->gpio_in_named.gpio43 = 0x01) : (gpio_in->gpio_in_named.gpio43 = 0x00);
	(GPIOD -> IDR & GPIO44 )	? (gpio_in->gpio_in_named.gpio44 = 0x01) : (gpio_in->gpio_in_named.gpio44 = 0x00);
	(GPIOD -> IDR & GPIO45 )	? (gpio_in->gpio_in_named.gpio45 = 0x01) : (gpio_in->gpio_in_named.gpio45 = 0x00);
	(GPIOD -> IDR & GPIO46 )	? (gpio_in->gpio_in_named.gpio46 = 0x01) : (gpio_in->gpio_in_named.gpio46 = 0x00);
	(GPIOD -> IDR & GPIO47 )	? (gpio_in->gpio_in_named.gpio47 = 0x01) : (gpio_in->gpio_in_named.gpio47 = 0x00);
	(GPIOD -> IDR & GPIO48 )	? (gpio_in->gpio_in_named.gpio48 = 0x01) : (gpio_in->gpio_in_named.gpio48 = 0x00);

	(GPIOF -> IDR & GPIO49 )	? (gpio_in->gpio_in_named.gpio49 = 0x01) : (gpio_in->gpio_in_named.gpio49 = 0x00);
	(GPIOF -> IDR & GPIO50 )	? (gpio_in->gpio_in_named.gpio50 = 0x01) : (gpio_in->gpio_in_named.gpio50 = 0x00);
	(GPIOF -> IDR & GPIO51 )	? (gpio_in->gpio_in_named.gpio51 = 0x01) : (gpio_in->gpio_in_named.gpio51 = 0x00);
	(GPIOF -> IDR & GPIO52 )	? (gpio_in->gpio_in_named.gpio52 = 0x01) : (gpio_in->gpio_in_named.gpio52 = 0x00);
	(GPIOF -> IDR & GPIO53 )	? (gpio_in->gpio_in_named.gpio53 = 0x01) : (gpio_in->gpio_in_named.gpio53 = 0x00);
	(GPIOF -> IDR & GPIO54 )	? (gpio_in->gpio_in_named.gpio54 = 0x01) : (gpio_in->gpio_in_named.gpio54 = 0x00);
	(GPIOF -> IDR & GPIO57 )	? (gpio_in->gpio_in_named.gpio57 = 0x01) : (gpio_in->gpio_in_named.gpio57 = 0x00);
	(GPIOF -> IDR & GPIO59 )	? (gpio_in->gpio_in_named.gpio59 = 0x01) : (gpio_in->gpio_in_named.gpio59 = 0x00);

	(GPIOB -> IDR & GPIO55 )	? (gpio_in->gpio_in_named.gpio55 = 0x01) : (gpio_in->gpio_in_named.gpio55 = 0x00);
	(GPIOB -> IDR & GPIO56 )	? (gpio_in->gpio_in_named.gpio56 = 0x01) : (gpio_in->gpio_in_named.gpio56 = 0x00);
	(GPIOB -> IDR & GPIO58 )	? (gpio_in->gpio_in_named.gpio58 = 0x01) : (gpio_in->gpio_in_named.gpio58 = 0x00);

}

