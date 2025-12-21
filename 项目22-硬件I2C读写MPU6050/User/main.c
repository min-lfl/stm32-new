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
#include <I2C_Software.H>
#include <MPU6050_Sensor.H>
#include <MPU6050_Hardware.h>

int16_t MPU6050xyz[6]={0};


//主函数
int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"1");
	MPU6050_Hardware_Init();
	OLED_ShowString(1,1,"MPU6050:");
	
	OLED_ShowString(2,1,"X:");
	OLED_ShowString(3,1,"Y:");
	OLED_ShowString(4,1,"Z:");
	OLED_ShowString(2,9,"Xa:");
	OLED_ShowString(3,9,"Ya:");
	OLED_ShowString(4,9,"Za:");
	//主循环
	while(1){
		MPU6050_Hardware_ReadXYZ(MPU6050xyz);
		OLED_ShowSignedNum(2,3,MPU6050xyz[0],4);
		OLED_ShowSignedNum(3,3,MPU6050xyz[1],4);
		OLED_ShowSignedNum(4,3,MPU6050xyz[2],4);

		OLED_ShowSignedNum(2,12,MPU6050xyz[3],4);
		OLED_ShowSignedNum(3,12,MPU6050xyz[4],4);
		OLED_ShowSignedNum(4,12,MPU6050xyz[5],4);
		Delay_ms(10);
	
	}
}


