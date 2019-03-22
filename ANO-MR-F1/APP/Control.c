#include "control.h"

PID PID_ROL,PID_PIT,PID_YAW,PID_ALT,PID_POS,PID_PID_1,PID_PID_2;

int16_t getlast_roll=0,geilast_pitch=0;
float rol_i=0,pit_i=0,yaw_p=0;

vs16 Moto_PWM_1=0,Moto_PWM_2=0,Moto_PWM_3=0,Moto_PWM_4=0,Moto_PWM_5=0,Moto_PWM_6=0,Moto_PWM_7=0,Moto_PWM_8=0;

void Control(T_float_angle *att_in,T_int16_xyz *gyr_in, T_RC_Data *rc_in, u8 armed)
{
	T_float_angle angle;
	angle.rol = att_in->rol - (rc_in->ROLL-1500)/12;
	angle.pit = att_in->pit + (rc_in->PITCH-1500)/12;
	
	rol_i += angle.rol;
	if(rol_i>2000)
	rol_i=2000;
	if(rol_i<-2000)
	rol_i=-2000;

	PID_ROL.pout = PID_ROL.P * angle.rol;
	PID_ROL.dout = -PID_ROL.D * gyr_in->Y;
	PID_ROL.iout = PID_ROL.I * PID_ROL.dout;

	pit_i += angle.pit;
	if(pit_i>2000)
	pit_i=2000;
	if(pit_i<-2000)
	pit_i=-2000;

	PID_PIT.pout = PID_PIT.P * angle.pit;
	PID_PIT.dout = PID_PIT.D * gyr_in->X;
	PID_PIT.iout = PID_PIT.I * pit_i;
	if(rc_in->YAW<1400||rc_in->YAW>1600)
	{gyr_in->Z=gyr_in->Z+(rc_in->YAW-1500)*2;}
	yaw_p+=gyr_in->Z*0.0609756f*0.002f;// +(Rc_Get.YAW-1500)*30
	if(yaw_p>20)
		yaw_p=20;
	if(yaw_p<-20)
		yaw_p=-20;


	PID_YAW.pout=PID_YAW.P*yaw_p;
	PID_YAW.dout = PID_YAW.D * gyr_in->Z;				   
	
	if(rc_in->THROTTLE<1200)
	{		
		pit_i=0;
		rol_i=0;
		yaw_p=0;
	}

	PID_ROL.OUT =  (-PID_ROL.pout)-PID_ROL.iout +PID_ROL.dout;//
	PID_PIT.OUT = PID_PIT.pout + PID_PIT.iout + PID_PIT.dout;
	PID_YAW.OUT = PID_YAW.pout + PID_YAW.iout + PID_YAW.dout;
 
	if(rc_in->THROTTLE>1200&&armed)
	{
		Moto_PWM_1 = rc_in->THROTTLE - 1000 - PID_ROL.OUT - PID_PIT.OUT + PID_YAW.OUT;
		Moto_PWM_2 = rc_in->THROTTLE - 1000 + PID_ROL.OUT - PID_PIT.OUT - PID_YAW.OUT;
		Moto_PWM_3 = rc_in->THROTTLE - 1000 + PID_ROL.OUT + PID_PIT.OUT + PID_YAW.OUT;
		Moto_PWM_4 = rc_in->THROTTLE - 1000 - PID_ROL.OUT + PID_PIT.OUT - PID_YAW.OUT;
	}
	else
	{
		Moto_PWM_1 = 0;
		Moto_PWM_2 = 0;
		Moto_PWM_3 = 0;
		Moto_PWM_4 = 0;
	}
	Moto_PwmRflash(Moto_PWM_1,Moto_PWM_2,Moto_PWM_3,Moto_PWM_4);
}
