#ifndef _BSP_TIM3_H_
#define _BSP_TIM3_H_
#include "stm32f10x.h"

extern u32 TIM3_IRQCNT;

void Tim3_Init(u16 period_num);//���ھ�ȷ��ʱ
void Tim3_Control(u8 sta);
#endif
