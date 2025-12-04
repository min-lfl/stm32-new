#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>
#include <OLED.H>
#include <CountSensor.H>
#include <Encoder.H>
#include <Timer.H>
#include <PWM.H>
#include <IC.H>

uint16_t i=0;
uint32_t Freg=0;


//void PWM_Init(void);
//void PWM_SetCompare1(uint16_t Compare);  //改变占空比
//void PWM_SetPrescaler(uint16_t Prescaler);  //改变频率


//void IC_Init(void);
//uint32_t IC_GetFreg(void);   //获取频率



//PWM输出到A0口控制呼吸灯，在oled显示分辨率自加
int main(void)
{
	OLED_Init();
	PWM_Init();
	IC_Init();
	OLED_ShowString(1,1,"num:");
	
	PWM_SetPrescaler(720-1);  //频率=72M/720-1/100=1000hz/s
	PWM_SetCompare1(50);
	while(1)
	{
		Freg=IC_GetFreg();
		OLED_ShowNum(2,1,Freg,5);
	}
}


