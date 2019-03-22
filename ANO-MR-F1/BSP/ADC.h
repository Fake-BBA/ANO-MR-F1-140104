#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"

extern __IO u16 ADC_ConvertedValue;

void ADC1_Init(void);

#endif /* __ADC_H */

