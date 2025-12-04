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
uint32_t Freg=0,Duty=0;


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
	OLED_ShowString(1,1,"Display");
	OLED_ShowString(2,1,"Freg:00000Hz");
	OLED_ShowString(3,1,"Duty:00%");
	
	PWM_SetPrescaler(720-1);  //频率=72M/720-1/100=1000hz/s
	PWM_SetCompare1(50);
	while(1)
	{
//		i=(i+1)%100;
//		PWM_SetCompare1(i);
		Freg=IC_GetFreg();
		Duty=IC_GetDuty();
		OLED_ShowNum(2,6,Freg,5);
		OLED_ShowNum(3,6,Duty,2);
		Delay_ms(100);
	}
}


