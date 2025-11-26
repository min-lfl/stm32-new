#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>

int main(void){
	LED_Init();
	while(1){
		LED1_OFF();
		LED2_OFF();
	}
}
