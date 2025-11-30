#ifndef __LightSensor_H__
#define __LightSensor_H__

void LightSensor_Init(void);		//初始化更敏电阻
uint8_t LightSensorDo_GetNum(void);	//读取光敏电阻DO口，无光为1，有光为0

#endif
