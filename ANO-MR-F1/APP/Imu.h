#ifndef _IMU_H_
#define _IMU_H_
#include "stm32f10x.h"
#include "sysconfig.h"

extern float 	AngleOffset_Rol,AngleOffset_Pit; 

void Prepare_Data(T_int16_xyz *acc_in,T_int16_xyz *acc_out);

void IMUupdate(T_int16_xyz *gyr, T_int16_xyz *acc, T_float_angle *angle);


#endif
