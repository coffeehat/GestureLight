#ifndef _LIGHT_H_
#define _LIGHT_H_

extern bit Light_On_Flag;
extern uint last_amplitude;

void Light_Switch(bit state);
void Light_Adjust(uint amplitude);

#endif //_LIGHT_H_