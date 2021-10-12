#ifndef _GESTURE_MODULE_H_
#define _GESTURE_MODULE_H_

extern uint GestureData;				//缓存接收到的手势
extern uint Gesture_Exist_Flag;		//手势接收标志，用于检测interrupt

void GestureModuleInit(void);
uint GestureModuleReadBrightness(void);



#endif //_GESTURE_MODULE_H_