#include "tim3.h"

u32 TIM3_IRQCNT = 0;
/**************************实现函数********************************************
*函数原型:		
*功　　能:1ms中断一次,计数器为1000		
*******************************************************************************/
void Tim3_Init(u16 period_num)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_DeInit(TIM3);

	TIM_TimeBaseStructure.TIM_Period=period_num;//装载值
	//prescaler is 1200,that is 72000000/72/500=2000Hz;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//分频系数
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//clear the TIM2 overflow interrupt flag
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//TIM2 overflow interrupt enable
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//enable TIM2
	//TIM_Cmd(TIM3,ENABLE);
}
void Tim3_Control(u8 sta)
{
	if(sta==0)
		TIM_Cmd(TIM3,DISABLE);
	if(sta==1)
		TIM_Cmd(TIM3,ENABLE);
}
