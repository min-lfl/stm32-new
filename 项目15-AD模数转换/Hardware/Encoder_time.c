#include "stm32f10x.h"                  // Device header


void Encoder_time_Init(){
	//第一步，打开TIM3和GPIOA的电源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步，把GPIOA配置成输入模式
	
	
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	        //设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;				//设置端口号，控制A6这里填6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//第三步，初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;      //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;    //psc
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//第四步初始化输入捕获单元，在每个上升沿把CNT转存到CCR，信号来自边沿检测极性选择
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);                            
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                   //指定TIM通道1
	TIM_ICInitStruct.TIM_ICFilter = 0xF;                            //滤波设置最大0xF
//	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;        //被测信号上升沿把计数器写入CCR1
	TIM_ICInit(TIM3,&TIM_ICInitStruct);                           
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;                   //指定TIM通道2
	TIM_ICInitStruct.TIM_ICFilter = 0xF;                            //滤波设置最大0xF
//	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;        //被测信号上升沿把计数器写入CCR1
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	//第五步初始化编码器
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Rising);
	TIM_InternalClockConfig(TIM3);
	//第六步，开始计时
	TIM_Cmd(TIM3,ENABLE);
}

//返回转过的格数，正为正转，负为反转
int16_t Encoder_Get(void){
	return TIM_GetCounter(TIM3)/4;    //因为编码器用TIM_EncoderMode_TI12模式转1格CNT会计数4次，所以需要/4得到真实格数
}




