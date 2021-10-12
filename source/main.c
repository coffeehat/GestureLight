#include "Global.h"
#include "Private.h"

sbit beep = P2^3;


void main()
{
	SerialInit();
	GestureModuleInit();
	TimerInit();
	PWMInit();
	delay_ms(1000);
	Gesture_Exist_Flag = 0;
	Gesture_Sweep_Flag = 0;
	
	while(1)
	{
		if( Gesture_Exist_Flag == 1)
		{
			if( Gesture_Sweep_Flag == 1 )
				light_switch_interface();
			else
				if( Light_On_Flag == 1)
					light_adjust_interface();
		}
	}
}