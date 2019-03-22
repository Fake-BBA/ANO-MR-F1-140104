#ifndef _BSP_MOTO_H_
#define _BSP_MOTO_H_
#include "stm32f10x.h"

#define Moto_PwmMax 999

void Moto_PwmRflash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM);
void Moto_Init(void);

#endif
