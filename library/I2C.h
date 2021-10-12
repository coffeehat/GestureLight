#ifndef _I2C_H_
#define _I2C_H_

#include <intrins.h>


void Delay_5us(void);
void IIC_Start(void);
void IIC_Stop(void);
void iic_SendACK(bit ack);
bit IIC_Wait_Ack();
void IIC_Send_Byte(unsigned char dat);
unsigned char IIC_Read_Byte(void);
//void Single_Byte_Write(unsigned char iic_add,unsigned char reg_add,unsigned char wdata);
//unsigned char Single_Byte_Read(unsigned char iic_add,unsigned char reg_add);
//void Multi_Write(unsigned char iic_add,unsigned char reg_add,unsigned char *s,unsigned char len );
//void Multi_Read(unsigned char iic_add,unsigned char reg_add,unsigned char *s,unsigned char len );


#endif //_I2C_H_