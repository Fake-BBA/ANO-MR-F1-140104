#ifndef _BSP_USART_H_
#define _BSP_USART_H_

void Uart1_Init(u32 br_num);
void Uart1_IRQ(void);

void Uart1_Put_String(unsigned char *Str);
void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num);

#endif
