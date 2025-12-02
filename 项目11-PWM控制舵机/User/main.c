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

uint16_t num=0;
uint8_t key=0;

//PWM2输出到舵机
int main(void){
	Encoder_Init();
	Key_Init();
	OLED_Init();
	PWMservo_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		OLED_ShowNum(2,1,num,5);
		num=num-GET_Encoder_Count()*5;
		if(num<=5){
			num=5;
		}
		if(num>=25){
			num=25;
		}
		TIM_SetCompare2(TIM2,num);
		Delay_ms(1);
	}
}


//		key=Key_GetNum();
//		if(key!=0){
//			if(key==1){
//				num=(num+5)%30;
//				if(num==0){
//					num=5;
//				}
//			}
//		}
