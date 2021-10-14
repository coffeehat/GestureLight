#include "Global.h"
#include "Timer_Sample.h"
#include "Gesture_Module.h"
#include "Light.h"

#define TIME 3686

//此文件为brightness采样应用文件
//采用定时器0中断，周期为4ms

/**************************************公共变量************************************************/
//brightness数据缓存
unsigned int idata sample_buffer[SAMPLE_BUFFER_LENGTH];
//当前brightness数据索引
uint index_of_sample_buffer = 0;
uint Gesture_Sweep_Flag = 0;		//手势扫略标志，用于检测用户是需要开关还是需要调光
uint Timer_Itrations = 0;			//计数器中断计数，用以保存时间信息
uint Sample_Stable;					//存储稳定的亮度信息

uint Adjustment_Flag = 0;

/**************************************公共方法************************************************/

/**************************************************************** 
 * 名称: TimerInit
 * 描述: 初始化定时器（周期8ms）
         当晶振为11.0592MHz时，计数值为：7372
		 当晶振为12MHz时，计数值为：8000
 * 参数: 无
 * 返回值: 无
****************************************************************/ 
void TimerInit()
{
	TMOD |= 0x01;			//设置定时器0为工作方式1（16位定时器）
	TH0 = (65536-TIME)/256;			//装载初值
	TL0 = (65536-TIME)%256;
	EA = 1;					//开总中断
	ET0 = 1;				//开定时器0中断
	TR0 = 1;				//开定时器
}


/**************************************事件************************************************/

/**************************************************************** 
 * 名称: Sample_Time
 * 描述: 已达到8ms采样时间
 * 参数: 无
 * 返回值: 无
****************************************************************/ 
void Sample_Time() interrupt 1
{
//	static uint count = 0;
	//更新计数器中断计数值
	Timer_Itrations++;
	//重装初值
	TH0 = (65536-TIME)/256;
	TL0 = (65536-TIME)%256;
	//读取brightness信息
	//sample_buffer采用环形覆盖队列结构
	sample_buffer[(index_of_sample_buffer)%SAMPLE_BUFFER_LENGTH] = GestureModuleReadBrightness();
	//滤波
	
			SBUF = sample_buffer[(index_of_sample_buffer)%SAMPLE_BUFFER_LENGTH];
		while(!TI);
		TI = 0;

	
	/*************以上执行时间为1029个机器周期，约为1ms*****************/
	Gesture_Sweep_Flag = sample_buffer[index_of_sample_buffer%SAMPLE_BUFFER_LENGTH] < 10 && sample_buffer[(index_of_sample_buffer-32)%SAMPLE_BUFFER_LENGTH] < 10;
	if(Adjustment_Flag == 1)
	{
		Light_Adjust(sample_buffer[(index_of_sample_buffer)%SAMPLE_BUFFER_LENGTH]);

	}
	
	index_of_sample_buffer++;
}