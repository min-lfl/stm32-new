#include "stm32f10x.h"                  // Device header
#include <PWM.H>

void motor_Init(void){
	//开启对应外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//初始化LED接口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//初始化后关闭所有LED
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
	//初始化定时器
	PWMmotor_Init();
	//关闭所有定时器
	TIM_SetCompare3(TIM2,0);
}

void motor_SetSpeed(int8_t Speed){
	if(Speed>=0){
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		TIM_SetCompare3(TIM2,Speed);
	}else if(Speed<=0){
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		TIM_SetCompare3(TIM2,-Speed);
	}
}

