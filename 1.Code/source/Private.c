#include "Global.h"
#include "Private.h"
#include "intrins.h"

void delay500ms(void);

void light_switch_interface()
{
	static bit state = 1;
	state = ~state;
	Light_Switch(state);
	Gesture_Exist_Flag = 0;
	Gesture_Sweep_Flag = 0;
}

void light_adjust_interface()
{
	uint sample_temp_now;
	//将Adjustment置1通知定时器0中断可以进行调光数据发送处理
	Adjustment_Flag = 1;
	do
	{
		sample_temp_now = sample_buffer[(index_of_sample_buffer)%SAMPLE_BUFFER_LENGTH];
	}
	while( Gesture_Exist_Flag != 1 || sample_temp_now != 0 );			//等待调光手势结束
	Adjustment_Flag = 0;
	
	last_amplitude = sample_buffer[(index_of_sample_buffer-25)%SAMPLE_BUFFER_LENGTH];		//采用之前第25个采样点的数据调光，并保存到上次调光结果
	Light_Adjust(last_amplitude);

	//delay_ms(500);
	delay500ms();
	Gesture_Exist_Flag = 0;
	Gesture_Sweep_Flag = 0;
}


void delay_ms(uint t)
{
	uchar i,j;
	for(i = t; i > 0; i--)
		for(j = 4000; j > 0; j--);
}

void delay500ms(void)
{
	uint i,j;
	for(i = 0; i < 11; i++)
		for(j = 0; j < 27857; j++);
}