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

uint16_t i=0;


//PWM输出到A0口控制呼吸灯，在oled显示分辨率自加
int main(void){
	OLED_Init();
	PWM_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		
		for(i=0;i<100;i++){
			OLED_ShowSignedNum(2,1,TIM_GetCounter(TIM2),5);
			TIM_SetCompare1(TIM2,i);
			Delay_ms(10);
		}
		for(i=100;i>0;i--){
			OLED_ShowSignedNum(2,1,TIM_GetCounter(TIM2),5);
			TIM_SetCompare1(TIM2,i);
			Delay_ms(10);
		}

	}
}


