#ifndef __STM32_I2C_H
#define __STM32_I2C_H
#include "stm32f10x.h"
/*====================================================================================================*/
/*
��ӭʹ�������ƴ�STM32 IIC��  
�����ƴ�����: www.anotc.com
������̳:www.anobbs.com
*/
#define www_anotc_com____www_anobbs_com
/*====================================================================================================*/
uint8_t ANO_TC_I2C2_Write_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
//�˺���ִ�к���������أ����iic��æ������0���������д�ɹ�������1
uint8_t ANO_TC_I2C2_Write_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
//�˺���ִ�к��ȴ�д������ɺ󷵻أ���ɺ󣬷���1
uint8_t ANO_TC_I2C2_Read_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
//�˺���ִ�к���������أ����iic��æ������0���������д�ɹ�������1
uint8_t ANO_TC_I2C2_Read_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
//�˺���ִ�к��ȴ���������ɺ󷵻أ���ɺ󣬷���1

void ANO_TC_I2C2_INIT(u8 ownadd, u32 speed, u8 nvic_er_p, u8 nvic_er_s, u8 nvic_ev_p, u8 nvic_ev_s);
//ownadd��������ַ��speed��iic�ٶȣ�nvic_er_p��iic�����ж���ռ���ȼ�������������
void ANO_TC_I2C2_RESET(void);

void ANO_TC_I2C2_EV_IRQ( void );
//�˺����������stm32F1xx_it.c�е�I2C1_EV_IRQHandler������
void ANO_TC_I2C2_ER_IRQ( void );
//�˺����������stm32F1xx_it.c�е�I2C1_ER_IRQHandler������
/*====================================================================================================*/
/*====================================================================================================*/
#endif
