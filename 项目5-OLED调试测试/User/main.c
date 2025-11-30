#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>
#include <OLED.H>

int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"Dare to know.");
	OLED_ShowString(2,1,"Act,don't speak");
	OLED_ShowString(3,1,"Know thyself");
	OLED_ShowString(4,1,"Never give up.");
	while(1){
		
	}
}
