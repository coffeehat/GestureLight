#include "Global.h"
#include "PWM_Private.h"
#include "PWM.h"

void PWMInit(void)
{
	CCON = 0;	//Initial PCA control register
				//PCA timer stop running
				//Clear CF flag
				//Clear all module interrupt flag
	CL = 0;		//Reset PCA base timer
	CH = 0;
	CMOD = 0x02;	//Set PCA timer clock source as Fosc/2
					//Disable PCA timer overflow interrupt
	CCAP0H = CCAP0L = 0x00;	//PWM0 port output 0% duty cycle square wave
	CCAPM0 = 0x42;	//PCA module-0 work in 8-bit PWM mode
	
//	CCAP1H = CCAP1L = 0x01;	//PWM1 port output 0% duty cycle square wave
//	PCAPWM1 = 0x03;
//	CCAPM1 = 0x42;	//PCA module-1 work in 8-bit PWM mode
//					//and no PCA interrupt
	CR = 1;			//PCA timer start run
}

void PWMChange0(uchar thres)
{
	CCAP0H = thres;
}