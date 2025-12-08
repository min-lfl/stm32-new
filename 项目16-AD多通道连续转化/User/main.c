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
#include <motor.H>
#include <IC.H>
#include <Encoder_time.H>
#include <AD.H>


int16_t num=0;
void LED2_Init(void);

//这个例子
int main(void){
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD1:");
	OLED_ShowString(2,1,"AD2:");
	OLED_ShowString(3,1,"AD3:");
	OLED_ShowString(4,1,"AD4:");
	
	while(1){
		OLED_ShowNum(1,6,GET_ADC_TD1() ,4);
		OLED_ShowNum(2,6,GET_ADC_TD2() ,4);
		OLED_ShowNum(3,6,GET_ADC_TD3() ,4);
		OLED_ShowNum(4,6,GET_ADC_TD4() ,4);
	}
}


