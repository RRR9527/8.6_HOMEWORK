#ifndef __ALARM_SYS__
#define __ALARM_SYS__

#include "alarm_sys.h"
#include "led.h"
#include "buzzer.h"
#include <stdint.h>   

#define LED_COUNT      4U
#define STANDBY_STATE  0U
#define WORKING_STATE  1U
#define ALARMING_STATE 2U
#define DELAY_ms       300U
#define BLINK_TIMES    5U
#define BEEP_ms        300U
#define ONE_TERM       5U

void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms);
void beep(uint32_t beep_ms);
void alarm_sys_func(void); 

#endif