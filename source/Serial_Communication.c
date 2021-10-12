#include "Global.h"
#include "Serial_Communication.h"
//此文件为串口通信应用文件

//uchar a;
//uint temp = 0;
//uchar code table[]="I get ";

/**************************************************************** 
 * Function Name: SerialInit
 * Description: 串口通信初始化程序，这里设定波特率为9600
 * Parameters: none
 * Return: none
****************************************************************/ 
void SerialInit()
{
	TMOD |= 0x20;			//将定时器1设置成工作方式2（8位自动重装）
	TH1 = 0xfd;			//装载初值
	TL1 = 0xfd;
	TR1 = 1;				//使能定时器1
	REN = 0;				//允许串口接收数据
	SM0 = 0;				//设定串口工作方式为1
	SM1 = 1;
	EA = 1;				//开总中断
	ES = 0;				//串口中断
}

//void ser() interrupt 4
//{
//	RI=0;
//	a=SBUF;
//	temp=1;
//}