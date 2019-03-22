/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sysconfig.h"
#include "bsp.h"
#include "led.h"
#include "tim3.h"	
#include "usart.h"
#include "ANO_TC_STM32F1_I2C.h"
#include "MPU6050.h"
#include "moto.h"
#include "spi.h"
#include "nrf24l01.h"
#include "tim_pwm_in.h"
#include "rc.h"
#include "imu.h"
#include "control.h"
#include "data_transfer.h"

u8 SYS_INIT_OK=0;
////////////////////////////////////////////////////////////////////////////////
void SYS_INIT(void)
{
	LED_INIT();
	LED_FLASH();
	Moto_Init();
	Uart1_Init(115200);	
	Tim3_Init(500);
#ifdef CONTROL_USE_RC
	Tim_Pwm_In_Init();
#endif
	Nvic_Init();
	ANO_TC_I2C2_INIT(0xA6,400000,1,1,3,3);
	MPU6050_Init();
	
	Spi1_Init();
	Nrf24l01_Init(MODEL_TX2,40);
 	if(Nrf24l01_Check())	
		Uart1_Put_String("NRF24L01 IS OK !\r\n");
 	else 									
		Uart1_Put_String("NRF24L01 IS NOT OK !\r\n");
		
	FLASH_Unlock();
	EE_INIT();
	EE_READ_ACC_OFFSET();
	EE_READ_GYRO_OFFSET();
	EE_READ_PID();
	
	Tim3_Control(1);
}
////////////////////////////////////////////////////////////////////////////////
u8 FLAG_ATT=0;
T_int16_xyz 		Acc,Gyr;	//两次综合后的传感器数据
T_int16_xyz			Acc_AVG;
T_float_angle 		Att_Angle;	//ATT函数计算出的姿态角
vs32				Alt;
T_RC_Data 			Rc_D;		//遥控通道数据
T_RC_Control		Rc_C;		//遥控功能数据
int main(void)
{
	static u8 att_cnt=0;
	static u8 rc_cnt=0;
	static T_int16_xyz mpu6050_dataacc1,mpu6050_dataacc2,mpu6050_datagyr1,mpu6050_datagyr2;
	static u8 senser_cnt=0,status_cnt=0,dt_rc_cnt=0,dt_moto_cnt=0;
	
	SYS_INIT();
	
	while (1)
	{			     
		if(FLAG_ATT)
		{
			FLAG_ATT = 0;
			att_cnt++;
			rc_cnt++;
			
			if(rc_cnt==20)
			{
				rc_cnt = 0;
				#ifdef CONTROL_USE_RC
				Rc_GetValue(&Rc_D);
				#endif
				Rc_Fun(&Rc_D,&Rc_C);
			}
			if(att_cnt==1)
				MPU6050_Dataanl(&mpu6050_dataacc1,&mpu6050_datagyr1);
			else
			{
				att_cnt = 0;
				MPU6050_Dataanl(&mpu6050_dataacc2,&mpu6050_datagyr2);
				Acc.X = (mpu6050_dataacc1.X+mpu6050_dataacc2.X)/2;
				Acc.Y = (mpu6050_dataacc1.Y+mpu6050_dataacc2.Y)/2;
				Acc.Z = (mpu6050_dataacc1.Z+mpu6050_dataacc2.Z)/2;
				Gyr.X = (mpu6050_datagyr1.X+mpu6050_datagyr2.X)/2;
				Gyr.Y = (mpu6050_datagyr1.Y+mpu6050_datagyr2.Y)/2;
				Gyr.Z = (mpu6050_datagyr1.Z+mpu6050_datagyr2.Z)/2;
				Prepare_Data(&Acc,&Acc_AVG);
				IMUupdate(&Gyr,&Acc_AVG,&Att_Angle);
				Control(&Att_Angle,&Gyr,&Rc_D,Rc_C.ARMED);
				if(Rc_C.ARMED)
					LED1_ONOFF();
				else
					LED1_OFF;
					
				senser_cnt++;
				status_cnt++;
				dt_rc_cnt++;
				dt_moto_cnt++;
				if(senser_cnt==5)
				{
					senser_cnt = 0;
					Send_Senser = 1;
				}
				if(status_cnt==5)
				{
					status_cnt = 0;
					Send_Status = 1;
				}
				if(dt_rc_cnt==10)
				{
					dt_rc_cnt=0;
					Send_RCData = 1;
				}
				if(dt_moto_cnt==10)
				{
					dt_moto_cnt=0;
					Send_MotoPwm = 1;
				}
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

