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

uint8_t DateA[] = {0x01,0x02,0x03,0x04};
uint8_t DateB[] = {0,0,0,0};
uint8_t i=0;

//这个例子
int main(void){
	OLED_Init();
//	OLED_ShowString(1,1,"0x");
	
	
	
	MyDMA_Init();
	
	while(1){
		for(i=0;i<4;i++){
			OLED_ShowHexNum(2,i*3+1,DateA[i],2);
		}
		for(i=0;i<4;i++){
			OLED_ShowHexNum(3,i*3+1,DateB[i],2);
		}
		DateA[0]=0x06;
		DateA[1]=0x06;
		DateA[2]=0x06;
		DateA[3]=0x06;
		DMA_Start();
	}
}


