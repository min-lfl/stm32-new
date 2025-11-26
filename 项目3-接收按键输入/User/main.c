#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>


int main(void){
	uint8_t key=0;
	LED_Init();
	Key_Init();

	while(1){
		key = Key_GetNum();
		if(key!=0){
			if(key==1){
				if(LED1_OUTGET()){
					LED1_OFF();
				}else{
					LED1_ON();
				}
			}
			if(key==2){
				if(LED2_OUTGET()){
					LED2_OFF();
				}else{
					LED2_ON();
				}
			}
		}
		
	}
}
