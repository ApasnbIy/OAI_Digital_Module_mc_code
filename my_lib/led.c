/**
  ******************************************************************************
  * @file           : led.c
  * @version        : v1.0
  * @brief          :	надстройка над CubeMX для удобного управления индикаторными светодиодами
  * @author			: Стюф Алексей/Alexe Styuf <a-styuf@yandex.ru>
  ******************************************************************************
  */

#include "led.h"
#include "gpio.h"

/**
  * @brief  инициализация led-индикатора
	*					led_num - номер индикатора. 0 - State PD3, 1 - Connection PD4
  */
void led_init(type_LED_INDICATOR* led_ptr, uint8_t led_num)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	if(led_num == 0){
			led_ptr->led_num = 0;
			GPIO_InitStruct.Pin = GPIO_PIN_3;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
	else if(led_num == 1){
			GPIO_InitStruct.Pin = GPIO_PIN_4;
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
			led_ptr->led_num = 1;
	}
	
	
		
	led_ptr->mode = DEFAULT_BLINK_MODE;
	led_ptr->period_ms = DEFAULT_BLINK_PERIOD_MS;
	led_ptr->duty = DEFAULT_BLINK_DUTY;
	led_ptr->alt_mode = DEFAULT_BLINK_MODE;
	led_ptr->alt_period_ms = DEFAULT_BLINK_PERIOD_MS;
	led_ptr->alt_duty = DEFAULT_BLINK_DUTY;
	led_ptr->time_ms = 0;
	led_ptr->alt_timeout_ms = 0;
}

void led_processor(type_LED_INDICATOR* led_ptr, uint32_t process_period_ms)
{
	uint8_t led_val;
	uint16_t period_time = 0;
	led_ptr->time_ms += process_period_ms;
	period_time = led_ptr->time_ms % led_ptr->period_ms;
	if (led_ptr->alt_timeout_ms == 0){
		switch (led_ptr->mode){
		case LED_OFF:
			led_val = 0;
			break;
		case LED_ON:
			led_val = 1;
			break;
		case LED_BLINK:
			if (period_time > ((led_ptr->period_ms*led_ptr->duty) >> 8)){
				led_val = 1;
			}
			else{
				led_val = 0;
			}
			break;
		case LED_HEART_BEAT:
			if ((period_time > (led_ptr->period_ms * 0 / 100)) && (period_time <= (led_ptr->period_ms * 15 / 100))){
				led_val = 1;
			}
			else if ((period_time > (led_ptr->period_ms * 30 / 100)) && (period_time <= (led_ptr->period_ms * 45 / 100))){
				led_val = 1;
			}
			else{
				led_val = 0;
			}
			break;
		default:
			led_val = 0;
			break;
		}
	}
	else{
		if (led_ptr->alt_timeout_ms <= process_period_ms){
			led_ptr->alt_timeout_ms = 0;
		}
		else{
			led_ptr->alt_timeout_ms -= process_period_ms;
		}
		switch (led_ptr->alt_mode){
		case LED_OFF:
			led_val = 0;
			break;
		case LED_ON:
			led_val = 1;
			break;
		case LED_BLINK:
			if ((led_ptr->time_ms % led_ptr->alt_period_ms) > ((led_ptr->alt_period_ms*led_ptr->alt_duty) >> 8)){
				led_val = 1;
			}
			else{
				led_val = 0;
			}
			break;
		default:
			led_val = 0;
			break;
		}
	}
	led_gpio_set(led_ptr, led_val);
}

void led_setup(type_LED_INDICATOR* led_ptr, uint8_t mode, uint16_t period_ms, uint8_t duty)
{
	led_ptr->mode = mode;
	led_ptr->period_ms = period_ms;
	led_ptr->duty = duty;
}

void led_alt_setup(type_LED_INDICATOR* led_ptr, uint8_t mode, uint16_t period_ms, uint8_t duty, uint32_t timeout_ms)
{
	led_ptr->alt_mode = mode;
	led_ptr->alt_period_ms = period_ms;
	led_ptr->alt_duty = duty;
	led_ptr->alt_timeout_ms = timeout_ms;
}
//0 - State PD3, 1 - Connection PD4
void led_gpio_set(type_LED_INDICATOR* led_ptr, uint8_t state)
{
	if(led_ptr->led_num == 0){
		if(state){
			HAL_GPIO_WritePin (GPIOD,GPIO_PIN_3, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin (GPIOD,GPIO_PIN_3 ,GPIO_PIN_RESET);
		}
	}
	else if(led_ptr->led_num == 1){
		if(state){
			HAL_GPIO_WritePin (GPIOD,GPIO_PIN_4, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin (GPIOD,GPIO_PIN_4 ,GPIO_PIN_RESET);
		}
	}
}
