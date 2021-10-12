#include "Global.h"
#include "Light.h"
#include "PWM.h"
//该文件为PWM灯光控制文件
//PWM灯光控制通过P1口输出二进制强度数据

bit Light_On_Flag = 0;
uint last_amplitude = 0xFF;

void Light_Switch(bit state)
{
	if(state)
	{
//		P1 = last_amplitude;
		Light_On_Flag = 1;
		PWMChange0(last_amplitude);
	}
	else
	{
//		P1 = 0x00;
		Light_On_Flag = 0;
		PWMChange0(0x00);
	}
}

void Light_Adjust(uint amplitude)
{
//	P1 = amplitude;
	PWMChange0(amplitude);
	
}