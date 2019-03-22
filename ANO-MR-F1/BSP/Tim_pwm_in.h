#ifndef _TIM_PWM_IN_H_
#define _TIM_PWM_IN_H_
#include "stm32f10x.h"
#include "sysconfig.h"

void Rc_GetValue(T_RC_Data *temp);

void Tim_Pwm_In_Init(void);
void Tim4_Pwm_In_Irq(void);

#endif
