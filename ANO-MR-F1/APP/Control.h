#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "stm32f10x.h"
#include "sysconfig.h"
#include "moto.h"

typedef struct PID{float P,pout,I,iout,D,dout,IMAX,OUT;}PID;

extern PID PID_ROL,PID_PIT,PID_YAW,PID_ALT,PID_POS,PID_PID_1,PID_PID_2;
extern vs16 Moto_PWM_1,Moto_PWM_2,Moto_PWM_3,Moto_PWM_4,Moto_PWM_5,Moto_PWM_6,Moto_PWM_7,Moto_PWM_8;

void Control(T_float_angle *att_in,T_int16_xyz *gyr_in, T_RC_Data *rc_in, u8 armed);

#endif
