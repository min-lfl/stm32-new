#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>

int main(void){
	LightSensor_Init();
	Buzzer_Init();
	while(1){
		if(LightSensorDo_GetNum()==1){
			Buzzer_ON();
		}else{
			Buzzer_OFF();
		}
		
	}
}
