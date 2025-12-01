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


int32_t num=0;

//外部时钟给定时器提供频率
//这里用的是定时器2，需要把外部时钟源插到A0口
int main(void){
	OLED_Init();
	Timer_init();
	OLED_ShowString(1,1,"num:");
	while(1){
		OLED_ShowSignedNum(2,1,num,3);
		OLED_ShowSignedNum(3,1,TIM_GetCounter(TIM2),5);
	}
}



void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
} 
