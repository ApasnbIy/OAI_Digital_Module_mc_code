#include "my_GPIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_rcc.h"


void init(type_gpio_config* gpio_conf){
	int len = 0;
	uint32_t PIN_IN = 0;
	uint32_t PIN_OUT = 0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	if(gpio_conf-> portB ==1){
		(gpio_conf.portB_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO55) : (GPIO_IN = PIN_IN|GPIO55);
		(gpio_conf.portB_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO56) : (GPIO_IN = PIN_IN|GPIO56);
		(gpio_conf.portB_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO58) : (GPIO_IN = PIN_IN|GPIO58);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	GPIO_InitStruct = {0};
	if(gpio_conf-> portC ==1){
		(gpio_conf.portC_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO1) : (GPIO_IN = PIN_IN|GPIO1);
		(gpio_conf.portC_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO2) : (GPIO_IN = PIN_IN|GPIO2);
		(gpio_conf.portC_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO3) : (GPIO_IN = PIN_IN|GPIO3);
		(gpio_conf.portC_mask>>3 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO4) : (GPIO_IN = PIN_IN|GPIO4);
		(gpio_conf.portC_mask>>4 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO5) : (GPIO_IN = PIN_IN|GPIO5);
		(gpio_conf.portC_mask>>5 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO6) : (GPIO_IN = PIN_IN|GPIO6);
		(gpio_conf.portC_mask>>6 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO7) : (GPIO_IN = PIN_IN|GPIO7);
		(gpio_conf.portC_mask>>7 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO8) : (GPIO_IN = PIN_IN|GPIO8);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	GPIO_InitStruct = {0};
	if(gpio_conf-> portD ==1){
		(gpio_conf.portD_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO41) : (GPIO_IN = PIN_IN|GPIO41);
		(gpio_conf.portD_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO42) : (GPIO_IN = PIN_IN|GPIO42);
		(gpio_conf.portD_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO43) : (GPIO_IN = PIN_IN|GPIO43);
		(gpio_conf.portD_mask>>3 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO44) : (GPIO_IN = PIN_IN|GPIO44);
		(gpio_conf.portD_mask>>4 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO45) : (GPIO_IN = PIN_IN|GPIO45);
		(gpio_conf.portD_mask>>5 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO46) : (GPIO_IN = PIN_IN|GPIO46);
		(gpio_conf.portD_mask>>6 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO47) : (GPIO_IN = PIN_IN|GPIO47);
		(gpio_conf.portD_mask>>7 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO48) : (GPIO_IN = PIN_IN|GPIO48);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		}
	}		
	PIN_IN = 0;
	PIN_OUT = 0;
	GPIO_InitStruct = {0};
	if(gpio_conf-> portE ==1){
		(gpio_conf.portE_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO9) : (GPIO_IN = PIN_IN|GPIO9);
		(gpio_conf.portE_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO10) : (GPIO_IN = PIN_IN|GPIO10);
		(gpio_conf.portE_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO11) : (GPIO_IN = PIN_IN|GPIO11);
		(gpio_conf.portE_mask>>3 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO12) : (GPIO_IN = PIN_IN|GPIO12);
		(gpio_conf.portE_mask>>4 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO13) : (GPIO_IN = PIN_IN|GPIO13);
		(gpio_conf.portE_mask>>5 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO14) : (GPIO_IN = PIN_IN|GPIO14);
		(gpio_conf.portE_mask>>6 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO15) : (GPIO_IN = PIN_IN|GPIO15);
		(gpio_conf.portE_mask>>7 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO16) : (GPIO_IN = PIN_IN|GPIO16);
		(gpio_conf.portE_mask>>8 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO17) : (GPIO_IN = PIN_IN|GPIO17);
		(gpio_conf.portE_mask>>9 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO18) : (GPIO_IN = PIN_IN|GPIO18);
		(gpio_conf.portE_mask>>10 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO19) : (GPIO_IN = PIN_IN|GPIO19);
		(gpio_conf.portE_mask>>11 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO20) : (GPIO_IN = PIN_IN|GPIO20);
		(gpio_conf.portE_mask>>12 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO21) : (GPIO_IN = PIN_IN|GPIO21);
		(gpio_conf.portE_mask>>13 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO22) : (GPIO_IN = PIN_IN|GPIO22);
		(gpio_conf.portE_mask>>14 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO23) : (GPIO_IN = PIN_IN|GPIO23);
		(gpio_conf.portE_mask>>15 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO24) : (GPIO_IN = PIN_IN|GPIO24);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		}
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	GPIO_InitStruct = {0};
	if(gpio_conf-> portF ==1){
		(gpio_conf.portF_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO41) : (GPIO_IN = PIN_IN|GPIO41);
		(gpio_conf.portF_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO42) : (GPIO_IN = PIN_IN|GPIO42);
		(gpio_conf.portF_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO43) : (GPIO_IN = PIN_IN|GPIO43);
		(gpio_conf.portF_mask>>3 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO44) : (GPIO_IN = PIN_IN|GPIO44);
		(gpio_conf.portF_mask>>4 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO45) : (GPIO_IN = PIN_IN|GPIO45);
		(gpio_conf.portF_mask>>5 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO46) : (GPIO_IN = PIN_IN|GPIO46);
		(gpio_conf.portF_mask>>6 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO47) : (GPIO_IN = PIN_IN|GPIO47);
		(gpio_conf.portF_mask>>7 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO48) : (GPIO_IN = PIN_IN|GPIO48);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		}
	
	}
	PIN_IN = 0;
	PIN_OUT = 0;
	GPIO_InitStruct = {0};
	if(gpio_conf-> portG ==1){
		(gpio_conf.portG_mask>>0 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO25) : (GPIO_IN = PIN_IN|GPIO25);
		(gpio_conf.portG_mask>>1 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO26) : (GPIO_IN = PIN_IN|GPIO26);
		(gpio_conf.portG_mask>>2 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO27) : (GPIO_IN = PIN_IN|GPIO27);
		(gpio_conf.portG_mask>>3 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO28) : (GPIO_IN = PIN_IN|GPIO28);
		(gpio_conf.portG_mask>>4 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO29) : (GPIO_IN = PIN_IN|GPIO29);
		(gpio_conf.portG_mask>>5 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO30) : (GPIO_IN = PIN_IN|GPIO30);
		(gpio_conf.portG_mask>>6 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO31) : (GPIO_IN = PIN_IN|GPIO31);
		(gpio_conf.portG_mask>>7 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO32) : (GPIO_IN = PIN_IN|GPIO32);
		(gpio_conf.portG_mask>>8 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO33) : (GPIO_IN = PIN_IN|GPIO33);
		(gpio_conf.portG_mask>>9 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO34) : (GPIO_IN = PIN_IN|GPIO34);
		(gpio_conf.portG_mask>>10 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO35) : (GPIO_IN = PIN_IN|GPIO35);
		(gpio_conf.portG_mask>>11 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO36) : (GPIO_IN = PIN_IN|GPIO36);
		(gpio_conf.portG_mask>>12 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO37) : (GPIO_IN = PIN_IN|GPIO37);
		(gpio_conf.portG_mask>>13 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO38) : (GPIO_IN = PIN_IN|GPIO38);
		(gpio_conf.portG_mask>>14 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO39) : (GPIO_IN = PIN_IN|GPIO39);
		(gpio_conf.portG_mask>>15 == 1 ) ? (PIN_OUT = PIN_OUT|GPIO40) : (GPIO_IN = PIN_IN|GPIO40);
		if(PIN_OUT!=0){
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
		}		
		if(PIN_IN!=0){
			GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = PIN_OUT;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
		}
	}
}