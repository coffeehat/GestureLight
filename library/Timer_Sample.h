#ifndef _TIMER_SAMPLE_H_
#define _TIMER_SAMPLE_H_

#define SAMPLE_BUFFER_LENGTH 32

extern unsigned int idata sample_buffer[];
extern uint index_of_sample_buffer;
extern uint Gesture_Sweep_Flag;		//手势扫略标志，用于检测用户是需要开关还是需要调光
extern uint Sample_Stable;				//存储稳定的亮度信息
extern uint Adjustment_Flag;

void TimerInit();

#endif //_TIMER_SAMPLE_H_
