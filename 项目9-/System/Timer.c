#include "stm32f10x.h"                  // Device header


void Timer_init(void){
	//第一步，给定时器2和A口上电，并且初始化端口，配置浮空/上拉输入
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	    	//设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第二步，用模式2分配外部时钟给TIM2
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
	//第三步，初始化时基单元,这里72MHZ/7200*10000=1秒
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//第四步，配置中断输出控制
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);   //清除中断标志位，防止一上电就触发中断

	//第五步，配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	
	//第六步，开始计时
	TIM_Cmd(TIM2,ENABLE);
}


/*定时器中断模板，在^_^处添加要执行的函数
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		^_^
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
} 
*/

