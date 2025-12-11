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
#include <MyDMA.H>

uint16_t DateA[] = {0x01,0x02,0x03,0x04};
uint8_t DateB[] = {0,0,0,0};
uint8_t i=0;


//这个例子
int main(void){
	OLED_Init();
	AD_Init(DateA);
	
	OLED_ShowString(1,1,"AD1:");
	OLED_ShowString(2,1,"AD2:");
	OLED_ShowString(3,1,"AD3:");
	OLED_ShowString(4,1,"AD4:");
	while(1){
		OLED_ShowNum(1,6,DateA[0],4);
		OLED_ShowNum(2,6,DateA[1],4);
		OLED_ShowNum(3,6,DateA[2],4);
		OLED_ShowNum(4,6,DateA[3],4);
//		OLED_ShowHexNum(4,2,(uint32_t)DateA,8);
//		OLED_ShowHexNum(4,2,(uint32_t)&(ADC1->DR),8);
	}
}


