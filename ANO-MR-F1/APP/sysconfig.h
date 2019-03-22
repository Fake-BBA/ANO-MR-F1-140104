#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_

#define CLI()      __set_PRIMASK(1)  
#define SEI()      __set_PRIMASK(0)

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define NVIC_UART_P	5
#define NVIC_UART_S	1
#define NVIC_TIM3_P	2
#define NVIC_TIM3_S	1
#define NVIC_TIM4_P	0
#define NVIC_TIM4_S	1

//#define DATA_TRANSFER_USE_USART
#define DATA_TRANSFER_USE_SPI_NRF

//#define CONTROL_USE_RC
#define CONTROL_USE_DATATRANSFER

#define RC_FUN_MIN	1200
#define RC_FUN_MAX	1800

typedef struct{
				float rol;
				float pit;
				float yaw;}T_float_angle;
typedef struct{
				float X;
				float Y;
				float Z;}T_float_xyz;
typedef struct{
				int16_t X;
				int16_t Y;
				int16_t Z;}T_int16_xyz;
typedef struct int16_rcget{
				int16_t ROLL;
				int16_t PITCH;
				int16_t THROTTLE;
				int16_t YAW;
				int16_t AUX1;
				int16_t AUX2;
				int16_t AUX3;
				int16_t AUX4;
				int16_t AUX5;
				int16_t AUX6;}T_RC_Data;
typedef struct{
				u8	ARMED;}T_RC_Control;

extern u8 FLAG_ATT;
extern T_int16_xyz 		Acc,Gyr;	//两次综合后的传感器数据
extern T_float_angle 	Att_Angle;	//ATT函数计算出的姿态角
extern vs32				Alt;
extern T_RC_Data 		Rc_D;		//遥控通道数据
extern T_RC_Control		Rc_C;		//遥控功能数据
extern u32				Debug_cnt;
#endif
