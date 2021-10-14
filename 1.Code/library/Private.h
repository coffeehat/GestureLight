//主函数私有头文件
#ifndef _PRIVATE_H_
#define _PRIVATE_H_

#include "Serial_Communication.h"
#include "Gesture_Module.h"
#include "Timer_Sample.h"
#include "Light.h"
#include "PWM.h"

void light_switch_interface();		//灯具开关
void light_adjust_interface();		//灯具调光

void delay_ms(uint t);		//毫秒延时

#endif //_PRIVATE_H_