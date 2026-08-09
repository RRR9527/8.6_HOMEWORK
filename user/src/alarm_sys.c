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


void alarm_sys_func(void){
	static uint8_t current_state = STANDBY_STATE ; 
	uint8_t current_led = 1U ; 
	static uint16_t count = 0U;
	
	switch (current_state){
		
		case STANDBY_STATE:
			for (current_led = 1U; current_led <= LED_COUNT; current_led++){
				led_off(current_led);
			}
			buzzer_off();
			// HAL_Delay(DELAY_ms);
			break;
			
		case WORKING_STATE:
			for (current_led = 1U; current_led <= LED_COUNT; current_led++){
				blink_led(current_led, BLINK_TIMES, DELAY_ms);
			}
			buzzer_off();
			HAL_Delay(DELAY_ms);
			break;
			
		case ALARMING_STATE:
			for (current_led = 1U; current_led <= LED_COUNT; current_led++){
				 blink_led(current_led, BLINK_TIMES, DELAY_ms / 3U);
			}
			beep(BEEP_ms);
			break;
			
		default:
			current_state = STANDBY_STATE;
			break ;
	}
	count ++;
	if (count >= ONE_TERM){
		current_state ++;
		count = 0U;
		if (current_state > 2U){
			current_state = STANDBY_STATE;			
		}
	}
	
}
	
void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
  uint16_t i = 0U; /* 循环计数变量 */

  /* if 判断：LED 编号只允许 1~4 */
  if (led_num > LED_COUNT)
  {
    return; /* return 直接结束当前函数 */
  }

  /* for 循环：初始化; 判断条件; 每次循环后执行 */
  for (i = 0U; i < times ; i++)
  {
    led_on(led_num);          /* 点亮指定 LED */
    HAL_Delay(delay_ms);      /* 延时一段时间 */
    led_off(led_num);         /* 熄灭指定 LED */
    HAL_Delay(delay_ms);
  }
}

void beep(uint32_t beep_ms)
{
  buzzer_on();          /* 打开蜂鸣器 */
  HAL_Delay(beep_ms);   /* 保持响一段时间 */
  buzzer_off();         /* 关闭蜂鸣器 */
}