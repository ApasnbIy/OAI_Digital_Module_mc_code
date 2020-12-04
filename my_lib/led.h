#ifndef _LED_H
#define _LED_H

#include "main.h"

#define LED_HEART_BEAT 3
#define LED_BLINK 2
#define LED_OFF 0
#define LED_ON 1

#define DEFAULT_BLINK_PERIOD_MS 1000 
#define DEFAULT_BLINK_DUTY 128 // 255 - максимум
#define DEFAULT_BLINK_MODE LED_BLINK

/** 
  * @brief  структура хранения всех настроек vcp_uart
  * @note   для работы vcp_uart необходимо наличие таймера настроенного на шаг 1 мкс, считающего вниз, в one-pulse режиме
  
  */
typedef struct  
{
	uint8_t led_num;  //0 - State PD3, 1 - Connection PD4
	uint8_t mode;
	uint16_t period_ms;
	uint8_t duty;
	uint32_t time_ms;
	uint32_t alt_timeout_ms;
	uint8_t alt_mode;
	uint16_t alt_period_ms;
	uint8_t alt_duty;	
}type_LED_INDICATOR;


void led_init(type_LED_INDICATOR* led_ptr, uint8_t led_num);
void led_processor(type_LED_INDICATOR* led_ptr, uint32_t process_period_ms);
void led_setup(type_LED_INDICATOR* led_ptr, uint8_t mode, uint16_t period_ms, uint8_t duty);
void led_alt_setup(type_LED_INDICATOR* led_ptr, uint8_t mode, uint16_t period_ms, uint8_t duty, uint32_t timeout_ms);
void led_gpio_set(type_LED_INDICATOR* led_ptr, uint8_t state);
#endif
