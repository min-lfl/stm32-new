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

int16_t num=0;
int8_t Code=0;
uint8_t key=0;


int main(void){
	Encoder_time_Init();
//	Encoder_Init();
	OLED_Init();
	OLED_ShowString(1,1,"num:");
	OLED_ShowString(2,1,"S:000000r");
	OLED_ShowString(3,1,"V:0000r/s");
	while(1){
		num=Encoder_Get();
		Delay_ms(500);
		//显示位置，20格为一圈，所以格式为格数/20格
		OLED_ShowSignedNum(2,3,num/20,5);
		//显示速度，20格为一圈，公式为0.5秒内走过格数*2个0.5秒/20格
		OLED_ShowSignedNum(3,3,((Encoder_Get()-num)*2)/20,3);
	}
}
