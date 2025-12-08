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


int16_t num=0;
void LED2_Init(void);

//这个例子
int main(void){
	OLED_Init();
	AD_Init();
	LED2_Init();
	OLED_ShowString(1,1,"Voltage:");
	OLED_ShowString(2,2,".00V");
	OLED_ShowString(3,1,"num(0->4096):");
	while(1){
		//读取电压寄存器
		num=GET_ADC();
		//把寄存器值转化电压
		float abc = (float)num/4096*3.3;
		//打印出电压
		OLED_ShowNum(2,1,abc,1);
		OLED_ShowNum(2,3,(int)(abc*100)%100,2);
		//打印出原始寄存器值
		OLED_ShowNum(4,1,num,4);
		if(num>1600){
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}else if(num<1500){
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
	}
}


void LED2_Init(void){
	//开启对应外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//初始化LED接口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
