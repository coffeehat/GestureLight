#include "Global.h"
#include "Gesture_Module.h"
#include "Gesture_Module_Private.h"
#include "I2C.h"
#include "Timer_Sample.h"

//此文件为手势识别模块应用文件


/**************************************公共变量************************************************/

uint GestureData = 0;				//缓存接收到的手势
uint Gesture_Exist_Flag = 0;		//手势接收标志，用于检测interrupt
 
/**************************************私有变量************************************************/
//详见Gesture_Module_Private.h文件

/**************************************私有方法************************************************/
void Delay_1us(unsigned int us)//包含调用时间,误差0us?
{
	unsigned int i=us;
	while( (us--) != 0)
   	{
		_nop_();
    }
}

/**************************************************************** 
 * 名称: GestureModuleWriteReg
 * 描述:  PAJ7620 写寄存器命令
 * 参数: addr:寄存器地址; cmd:写入的数据
 * 返回值: 无
****************************************************************/ 
void GestureModuleWriteReg(uint addr, uint cmd)
{
	char i = 1;
	IIC_Start(); 
	IIC_Send_Byte((PAJ7620_ID<<1)|0);	//发送器件地址+写命令	
	IIC_Send_Byte(addr);	//写寄存器地址
	IIC_Send_Byte(cmd);		//写寄存器地址 
 	IIC_Stop();	
}

/**************************************************************** 
 * 名称: GestureModuleReadReg
 * 描述:  PAJ7620 读寄存器数据
 * 参数: addr:寄存器地址;
 * 返回值: 读到的数据
 * 耗时： 988指令周期，1072us（11.0592MHz晶振）
****************************************************************/ 
uint GestureModuleReadReg(uint addr)
{
	unsigned char rdata;
	IIC_Start(); 
	IIC_Send_Byte((PAJ7620_ID<<1)|0);//发送器件地址+写命令	
	IIC_Send_Byte(addr);	//写寄存器地址
	IIC_Start();
	IIC_Send_Byte((PAJ7620_ID<<1)|1);//发送器件地址+读命令	
	rdata=IIC_Read_Byte();//读取数据,发送nACK 
	iic_SendACK(1); //最后一个数据需要会NAK
	IIC_Stop();	//产生一个停止条件 
	EA=1;
	return rdata;
	
    
}

/**************************************************************** 
 * 名称: GestureModuleReadRegForInterrupt
 * 描述:  PAJ7620 读寄存器数据（提供给中断服务程序的函数）
 * 参数: addr:寄存器地址;
 * 返回值: 读到的数据
****************************************************************/ 
uint GestureModuleReadRegForInterrupt(uint addr)
{
	unsigned char rdata;
	IIC_Start(); 
	IIC_Send_Byte((PAJ7620_ID<<1)|0);//发送器件地址+写命令	
	IIC_Send_Byte(addr);	//写寄存器地址
	IIC_Start();
	IIC_Send_Byte((PAJ7620_ID<<1)|1);//发送器件地址+读命令	
	rdata=IIC_Read_Byte();//读取数据,发送nACK 
	iic_SendACK(1); //最后一个数据需要会NAK
	IIC_Stop();	//产生一个停止条件 
	EA=1;
	return rdata;
	
    
}


/**************************************************************** 
 * 名称: GestureModuleSelectBank
 * 描述:  PAJ7620 选择存储bank
 * 参数: BANK0, BANK1
 * 返回值: none
****************************************************************/ 
void GestureModuleSelectBank(bank_e bank)
{
    switch(bank){
		case BANK0:
			GestureModuleWriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK0);
			break;
		case BANK1:
			GestureModuleWriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK1);
			break;
		default:
			break;
	}
}


/**************************************公共方法************************************************/


/**************************************************************** 
 * 名称: GestureModuleInit
 * 描述:  PAJ7620 初始化寄存器
 * 参数: none
 * 返回值: none
****************************************************************/ 
void GestureModuleInit(void) 
{
	//Near_normal_mode_V5_6.15mm_121017 for 940nm
	int i = 0;
	uint data0 = 0, data1 = 0;
	//唤醒传感器
	Delay_1us(100);	//Wait 700us for PAJ7620U2 to stabilize	

	GestureModuleSelectBank(BANK0);
	//GestureModuleSelectBank(BANK1);
	data0 = GestureModuleReadReg(0);
	data1 = GestureModuleReadReg(1);	
	for (i = 0; i < INIT_REG_ARRAY_SIZE; i++) 
	{
		GestureModuleWriteReg(initRegisterArray[i][0], initRegisterArray[i][1]);
	}
	
	GestureModuleSelectBank(BANK0);  //设置默认存储bank为bank0
	
	EA = 1;				//打开总中断
	EX0 = 1;			//打开外部中断
}

/**************************************************************** 
 * 名称: GestureModuleReadBrightness
 * 描述:  读取PAJ7620中亮度信息
 * 参数: 无
 * 返回值: 亮度信息
****************************************************************/ 
uint GestureModuleReadBrightness(void)
{
	return GestureModuleReadReg(PAJ7620_ADDR_OBJECT_BRIGHTNESS);
}


/**************************************事件************************************************/

/**************************************************************** 
 * 名称: GestureModuleRecognition
 * 描述:  采用中断方式提供手势数据
 * 参数: none
 * 返回: 无（手势数据通过全局变量GestureData返回）
****************************************************************/ 
void GestureModuleRecognition() interrupt 0
{
	EX0 = 0;
	GestureData = GestureModuleReadRegForInterrupt(PAJ7620_ADDR_GES_PS_DET_FLAG_0);
	Gesture_Exist_Flag = 1;

//	SBUF = GestureData;
//	while(!TI);
//	TI = 0;
//	SBUF = sample_buffer[index_of_sample_buffer%SAMPLE_BUFFER_LENGTH];
//	while(!TI);
//	TI = 0;
	SBUF = 255;
	while(!TI);
	TI = 0;
	
	
	EX0 = 1;
}