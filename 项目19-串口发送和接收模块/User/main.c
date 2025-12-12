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
uint8_t array[]={1,2,3,4,5};

//主函数
int main(void){
	OLED_Init();
	Usart_Init();
	OLED_ShowString(1,1,"AD7:");
	while(1){
		//接收串口数据
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
			num=USART1_ReceiveChar();
		}
		//显示数据到OLED
		OLED_ShowHexNum(1,6,num,4);
		// 并通过串口发送回电脑
		USART1_SendChar(num);
		USART1_SendArray(array,5);
		// Delay_ms(500);
	}
}


