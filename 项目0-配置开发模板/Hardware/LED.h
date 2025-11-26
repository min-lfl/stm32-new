#ifndef __LED_H__
#define __LED_H__

//###默认灯接A0和A1(可改)。引脚为推挽输出，LED正极接引脚，负极接地

void LED_Init(void);  		//初始化LDE灯
void LED1_ON(void);			//开启灯1
void LED1_OFF(void);		//关闭灯1
void LED2_ON(void);			//开启灯2
void LED2_OFF(void);		//关闭灯2
uint8_t LED1_OUTGET(void);	//获取LED1口输出寄存器状态
uint8_t LED2_OUTGET(void);	//获取LED2口输出寄存器状态


#endif
