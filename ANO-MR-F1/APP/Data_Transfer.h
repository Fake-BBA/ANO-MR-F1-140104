#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_
#include "stm32f10x.h"
#include "MPU6050.h"
#include "sysconfig.h"
#include "imu.h"
#include "nrf24l01.h"
#include "control.h"
#include "led.h"
#include "usart.h"
#include "rc.h"

extern u8 Data_Check,Send_Status,Send_Senser,Send_RCData,Send_GpsData,Send_Offset,Send_PID1,Send_PID2,Send_PID3,Send_MotoPwm;

void Data_Receive_Anl(u8 *data_buf,u8 num);
void Data_Exchange(void);

void Data_Send_Status(void);	
void Data_Send_Senser(void);	
void Data_Send_RCData(void);	
void Data_Send_OFFSET(void);	
void Data_Send_PID1(void);
void Data_Send_PID2(void);
void Data_Send_PID3(void);
void Data_Send_MotoPWM(void);

void Data_Send_Check(u16 check);

void NRF_Send_Test(void);

#endif
