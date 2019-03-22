#ifndef _LED_H_
#define _LED_H_
#include "stm32f10x.h"
#include "tim3.h"		

#define LED1_OFF  		GPIO_SetBits(GPIOA, GPIO_Pin_15);
#define LED1_ON 		GPIO_ResetBits(GPIOA, GPIO_Pin_15);

void LED_INIT(void);
void LED_FLASH(void);
void LED1_ONOFF(void);

#endif
