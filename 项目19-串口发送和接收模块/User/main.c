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

//这个例子
int main(void){
	OLED_Init();
	Usart_Init();
	OLED_ShowString(1,1,"AD1:");
	while(1){
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
			num=USART1_ReceiveChar();
		}
		OLED_ShowHexNum(1,6,num,4);
		USART1_SendChar(num);
		
	}
}


