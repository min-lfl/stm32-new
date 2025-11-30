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

int32_t num=0;

int main(void){
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		num = num+GET_Encoder_Count();
//		OLED_ShowNum(2,1,num,3);
		OLED_ShowSignedNum(2,1,num,3);
	}
}

