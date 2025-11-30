#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>
#include <OLED.H>
#include <CountSensor.H>

//这里注意把红外对射传感器绿光挡上，否则会多次计数
uint32_t num=0;
int main(void){
	OLED_Init();
	CountSensor_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		OLED_ShowNum(2,1,num,2);
	}
}


void EXTI15_10_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line14) == SET){
		num++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
