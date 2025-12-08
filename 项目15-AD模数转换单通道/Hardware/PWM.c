#include "stm32f10x.h"                  // Device header

//PWM呼吸灯的初始化函数，PA1输出
void PWM_Init(void){
	//第一步，打开TIM2和GPIOA的电源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步，初始化PA0，PWM1固定从PA0输出，引脚配置成复用推挽输出，控制权交给片上外设PWM
	GPIO_InitTypeDef GPIO_InitStructure;				//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    	//设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			//设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第三步，分配内部时钟给TIM2
	TIM_InternalClockConfig(TIM2);
	
	//第四步，初始化时基单元,这里72MHZ/7200*10000=1秒
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;      //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;    //psc
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	//第五步，配置OC
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 50;				//CCR的值
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	//第六步，开始计时
	TIM_Cmd(TIM2,ENABLE);
}


/*
舵机的初始化函数，PA1输出，TIM_SetCompare2(TIM2,num);中
num=5对应0°
num=10对应45°
num=15对应90°
num=20对应135°
num=25对应180°
*/
void PWMservo_Init(void){
	//第一步，打开TIM2和GPIOA的电源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步，初始化PA0，PWM1固定从PA0输出，引脚配置成复用推挽输出，控制权交给片上外设PWM
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    	//设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第三步，分配内部时钟给TIM2
	TIM_InternalClockConfig(TIM2);
	
	//第四步，初始化时基单元,这里72MHZ/7200*10000=1秒
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;      //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;    //psc
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	//第五步，配置OC
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 50;				//CCR的值
	
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	//第六步，开始计时
	TIM_Cmd(TIM2,ENABLE);
}


//定时器2的PWM驱动直流电机，A2口
void PWMmotor_Init(void){
	//第一步，打开TIM2和GPIOA的电源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步，初始化PA0，PWM1固定从PA0输出，引脚配置成复用推挽输出，控制权交给片上外设PWM
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    	//设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				//设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第三步，分配内部时钟给TIM2
	TIM_InternalClockConfig(TIM2);
	
	//第四步，初始化时基单元,这里72MHZ/7200*10000=1秒
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;      //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;    //psc
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	//第五步，配置OC
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 50;				//CCR的值
	
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	//第六步，开始计时
	TIM_Cmd(TIM2,ENABLE);
}


