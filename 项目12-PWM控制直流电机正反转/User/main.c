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

int8_t num=0;
int8_t Code=0;
uint8_t key=0;

//PWM2输出到直流电机，旋转编码器控制速度和方向，按键1为总开关
int main(void){
	Encoder_Init();
	Key_Init();
	OLED_Init();
	motor_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		//显示速度
		OLED_ShowSignedNum(2,1,num,3);
		//接收旋转编码器
		if(num!=-100 || num!=100)
		num=num+GET_Encoder_Count()*5;
		//把速度值更新到定时器
		motor_SetSpeed(num);
		
		//总开关，如果按下就把速度强制置0，断电
		key=Key_GetNum();
		if(key==1){
			Code=~Code;
			
		}
		if(Code){
			motor_SetSpeed(0);
			OLED_ShowString(3,1,"OFF");
		}else{
			OLED_ShowString(3,1,"ON ");
		}
	}
}
