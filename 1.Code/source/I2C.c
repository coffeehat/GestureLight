#include "Global.h"
#include "I2C.h"

sbit IIC_SDA = P2^4; //I2C时钟
sbit IIC_SCL = P2^6;//I2C数据

//void Delay_nms(unsigned int ms);



void Delay_5us()
{
	_nop_();
	_nop_();
}

void IIC_Start()
{
	IIC_SDA = 1;
	IIC_SCL = 1;
	Delay_5us();
	IIC_SDA = 0;
	Delay_5us();
	IIC_SCL= 0;
}

void IIC_stop()
{
	IIC_SDA = 0;
	IIC_SCL = 1;
	Delay_5us();
	IIC_SDA = 1;
	Delay_5us();
}
	
void iic_SendACK(bit ack)
{
    IIC_SDA = ack;                  //写应答信号
    IIC_SCL = 1;                    //拉高时钟线
    Delay_5us();                 //延时
    IIC_SCL = 0;                    //拉低时钟线
    Delay_5us();                 //延时
}

bit IIC_Wait_Ack()		//原有的IIC等待确认函数耗时太长（2.2ms），目前对其进行重写
{
    IIC_SCL = 1;                    //拉高时钟线
    Delay_5us();                 //延时
	if(IIC_SDA == 0)
	{//收到确认的情况
		IIC_SCL = 0;
		return 0;
	}
	else
	{//没有收到的情况
		IIC_Stop();
		return 1;
	}
}

void IIC_Send_Byte(unsigned char dat)
{
    unsigned char i,j = 0;
	unsigned char dat_temp = dat;
	do
	{
		if(j > 0)
			IIC_Start();
		for (i=0; i<8; i++)         //8位计数器
		{       
			IIC_SDA=(dat&0x80)>>7;;               //送数据口
			dat <<= 1;              //移出数据的最高位
			IIC_SCL = 1;                //拉高时钟线
			Delay_5us();             //延时
			IIC_SCL = 0;                //拉低时钟线
			//Delay_5us();             //延时(因为IIC_SDA=(dat&0x80)>>7;;dat<<= 1;IIC_SCL=1;这三条指令已经占据5us时间。故此步可忽略)
		}
		dat = dat_temp;
		j++;
	}
    while(IIC_Wait_Ack());			//增加总线接收不到重传的机制
}

unsigned char IIC_Read_Byte()
{
    unsigned char i;
    unsigned char dat = 0;

    IIC_SDA = 1;                    //使能内部上拉,准备读取数据
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        IIC_SCL = 1;                //拉高时钟线
        Delay_5us();             //延时
        dat |= IIC_SDA;             //读数据
        IIC_SCL = 0;                //拉低时钟线
        Delay_5us();             //延时
    }
    return dat;
}

//void Single_Byte_Write(unsigned char iic_add,unsigned char reg_add,unsigned char wdata)
//{
//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add);     //发送设备地址+写信号
//    IIC_Send_Byte(reg_add);     //发送存储单元地址

//	IIC_Send_Byte(wdata);
//	
//    IIC_Stop();             //停止信号
//    Delay_nms(5);
//}

//unsigned char Single_Byte_Read(unsigned char iic_add,unsigned char reg_add)
//{
//	unsigned char rdata;
//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add);     //发送设备地址+写信号
//    IIC_Send_Byte(reg_add);     //发送存储单元地址
//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add | 1);     //发送设备地址+读信号

//	rdata = IIC_Read_Byte();
//	iic_SendACK(1); //最后一个数据需要会NAK
//    IIC_Stop();             //停止信号

//	return rdata;
//}

//void Multi_Write(unsigned char iic_add,unsigned char reg_add,unsigned char *s,unsigned char len )//多字节写入，有页面约定
//{
//    unsigned char i;

//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add);     //发送设备地址+写信号
//    IIC_Send_Byte(reg_add);     //发送存储单元地址
//    for (i = 0;i < len;i ++)
//    {
//        IIC_Send_Byte(*s ++);
//    }
//    IIC_Stop();             //停止信号
//    Delay_nms(5);
//}

//void Multi_Read(unsigned char iic_add,unsigned char reg_add,unsigned char *s,unsigned char len )//多字节读出，无页面约定
//{
//    unsigned char i;

//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add);     //发送设备地址+写信号
//    IIC_Send_Byte(reg_add);     //发送存储单元地址
//    IIC_Start();            //起始信号
//    IIC_Send_Byte(iic_add | 1);     //发送设备地址+读信号
//    for (i = 0;i < len - 1;i ++)
//    {
//        *s ++ = IIC_Read_Byte();
//		iic_SendACK(0); //回应ACK            
//    }
//	*s = IIC_Read_Byte();
//	iic_SendACK(1); //最后一个数据需要会NAK
//    IIC_Stop();             //停止信号
//}

//void Delay_nms(unsigned int ms)
//{
//  	unsigned int De_Cnt;
//  	while( (ms--) != 0)
//   	{
//    	for(De_Cnt = 0; De_Cnt < 600; De_Cnt++); 
//   	}             
//}
