//蜂鸣器模块
#ifndef __Buzzer_H__
#define __Buzzer_H__

void Buzzer_Init(void);  	//初始化蜂鸣器
void Buzzer_ON(void);		//打开蜂鸣器
void Buzzer_OFF(void);		//关闭蜂鸣器
uint8_t Buzzer_OUTGET(void);//读取蜂鸣器状态

#endif
