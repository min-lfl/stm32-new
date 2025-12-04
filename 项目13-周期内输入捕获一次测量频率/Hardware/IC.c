#include "stm32f10x.h"                  // Device header


void IC_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	        //设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				//设置端口号，控制A6这里填6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//第三步，初始化时基单元
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;      //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;    //psc
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//第四步
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);                            
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                   //指定TIM通道V
	TIM_ICInitStruct.TIM_ICFilter = 0xF;                            //滤波设置最大0xFV
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;        //信号下降沿
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;              //预分频选择不分频V
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;    //引脚连接模式
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	//第五步
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);    //从模式从接口一接收被测信号上升沿
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);  //从模式接收上升沿后触发Reset操作
	
	//第六步,启动定时器
	TIM_Cmd(TIM3,ENABLE);
}



//获取频率
uint32_t IC_GetFreg(void){
	return 1000000/TIM_GetCapture1(TIM3);
}

