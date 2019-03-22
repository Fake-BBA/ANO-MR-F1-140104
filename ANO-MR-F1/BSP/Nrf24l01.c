#include "nrf24l01.h"

uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
u8  TX_ADDRESS[TX_ADR_WIDTH]= {0xE1,0xE2,0xE3,0xE4,0xE5};	//本地地址
u8  RX_ADDRESS[RX_ADR_WIDTH]= {0xE1,0xE2,0xE3,0xE4,0xE5};	//接收地址
/*
*****************************************************************
* 写寄存器
*****************************************************************
*/
uint8_t NRF_Write_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	SPI_CSN_L();					  /* 选通器件 */
	status = Spi_RW(reg);  /* 写寄存器地址 */
	Spi_RW(value);		  /* 写数据 */
	SPI_CSN_H();					  /* 禁止该器件 */
  return 	status;
}
/*
*****************************************************************
* 读寄存器
*****************************************************************
*/
uint8_t NRF_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	SPI_CSN_L();					  /* 选通器件 */
	Spi_RW(reg);			  /* 写寄存器地址 */
	reg_val = Spi_RW(0);	  /* 读取该寄存器返回数据 */
	SPI_CSN_H();					  /* 禁止该器件 */
    return 	reg_val;
}
/*
*****************************************************************
*
* 写缓冲区
*
*****************************************************************
*/
uint8_t NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars)
{
	uint8_t i;
	uint8_t status;
	SPI_CSN_L();				        /* 选通器件 */
	status = Spi_RW(reg);	/* 写寄存器地址 */
	for(i=0; i<uchars; i++)
	{
		Spi_RW(pBuf[i]);		/* 写数据 */
	}
	SPI_CSN_H();						/* 禁止该器件 */
    return 	status;	
}
/*
*****************************************************************
* 读缓冲区
*****************************************************************
*/
uint8_t NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars)
{
	uint8_t i;
	uint8_t status;
	SPI_CSN_L();						/* 选通器件 */
	status = Spi_RW(reg);	/* 写寄存器地址 */
	for(i=0; i<uchars; i++)
	{
		pBuf[i] = Spi_RW(0); /* 读取返回数据 */ 	
	}
	SPI_CSN_H();						/* 禁止该器件 */
    return 	status;
}
/*
*****************************************************************
* 写数据包
*****************************************************************
*/
void NRF_TxPacket(uint8_t * tx_buf, uint8_t len)
{	
	SPI_CE_L();		 //StandBy I模式	
	
	NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // 装载接收端地址
	NRF_Write_Buf(WR_TX_PLOAD, tx_buf, len); 			 // 装载数据	
	SPI_CE_H();		 //置高CE，激发数据发送
}
void NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len)
{	
	SPI_CE_L();		 //StandBy I模式	
	NRF_Write_Buf(0xa8, tx_buf, len); 			 // 装载数据
	SPI_CE_H();		 //置高CE
}
u8 Nrf24l01_Check(void)
{ 
	u8 buf1[5]; 
	u8 i; 
	/*写入5个字节的地址. */ 
	NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5); 
	/*读出写入的地址 */ 
	NRF_Read_Buf(TX_ADDR,buf1,5); 
	/*比较*/ 
	for(i=0;i<5;i++) 
	{ 
		if(buf1[i]!=TX_ADDRESS[i]) 
			break; 
	} 
	if(i==5)
		return SUCCESS ; //MCU与NRF成功连接 
	else
		return ERROR ; //MCU与NRF不正常连接 
}
void Nrf24l01_Init(u8 model, u8 ch)
{
	SPI_CE_L();
	NRF_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);	//写RX节点地址 
	NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH); 		//写TX节点地址  
	NRF_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); 													//使能通道0的自动应答 
	NRF_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);											//使能通道0的接收地址 
	NRF_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);											//设置自动重发间隔时间:500us;最大自动重发次数:10次 
	NRF_Write_Reg(NRF_WRITE_REG+RF_CH,40);														//设置RF通道为CHANAL
	NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); 												//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	//NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x07); 												//设置TX发射参数,0db增益,1Mbps,低噪声增益开启
/////////////////////////////////////////////////////////
	if(model==1)				//RX
	{
		NRF_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//选择通道0的有效数据宽度 
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ收发完成中断开启,16位CRC,主接收
	}
	else if(model==2)		//TX
	{
		NRF_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//选择通道0的有效数据宽度 
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
	}
	else if(model==3)		//RX2
	{
		NRF_Write_Reg(FLUSH_TX,0xff);
		NRF_Write_Reg(FLUSH_RX,0xff);
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ收发完成中断开启,16位CRC,主接收
		
		Spi_RW(0x50);
		Spi_RW(0x73);
		NRF_Write_Reg(NRF_WRITE_REG+0x1c,0x01);
		NRF_Write_Reg(NRF_WRITE_REG+0x1d,0x06);
	}
	else								//TX2
	{
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
		NRF_Write_Reg(FLUSH_TX,0xff);
		NRF_Write_Reg(FLUSH_RX,0xff);
		
		Spi_RW(0x50);
		Spi_RW(0x73);
		NRF_Write_Reg(NRF_WRITE_REG+0x1c,0x01);
		NRF_Write_Reg(NRF_WRITE_REG+0x1d,0x06);
	}
	SPI_CE_H();
}
////////////////////////////////////////////////////////////////////////////////
