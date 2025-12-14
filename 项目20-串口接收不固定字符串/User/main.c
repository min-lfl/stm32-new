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
#include <Usart.H>

uint8_t num=0;
uint8_t i=0;
uint8_t array[]={1,2,3,4};

extern uint8_t usart1_TXdata[4];//引用模块内固定4位发送数据包

char buffer[20]="123456\0hhh";

//主函数
int main(void){
	OLED_Init();
	Usart_Init();
	OLED_ShowString(1,1,"AD7:");
	
	
	//主循环
	while(1){
		if(USART1_ReceiveStringFlag()){
			OLED_ShowString(2,1,"                                        ");
			OLED_ShowString(2,1,USART1_ReceiveString());//显示接收到的字符串
			USART1_SendArray((uint8_t*)USART1_ReceiveString(),20);
		}
	}
}


