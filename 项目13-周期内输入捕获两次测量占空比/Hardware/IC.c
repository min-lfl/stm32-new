#include "stm32f10x.h"                  // Device header
#include <math.h>

void IC_Init(void){
	//第一步，打开TIM3和GPIOA的电源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步，把GPIOA配置成输入模式
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
	
	//第四步初始化输入捕获单元，在每个下降沿把CNT转存到CCR
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);                            
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                   //指定TIM通道1，值会存入CCR1
	TIM_ICInitStruct.TIM_ICFilter = 0xF;                            //滤波设置最大0xF
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;        //被测信号上升沿把计数器写入CCR1
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;              //预分频选择不分频
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;    //引脚连接模式，直连输入，用通道1读取引脚1
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
//	TIM_ICStructInit(&TIM_ICInitStruct);                            
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;                    //和上面相反，指定TIM通道2，值会存入CCR2
//	TIM_ICInitStruct.TIM_ICFilter = 0xF;                             //滤波设置最大0xF
//	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;        //和上面相反，被测信号下降沿把计数器写入CCR2
//	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;               //预分频选择不分频
//	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;   //和上面相反，引脚连接模式，交叉输入，这样用着通道2读取引脚1
//	TIM_ICInit(TIM3,&TIM_ICInitStruct);
//	等效于
	TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);
	
	//第五步，用于在每个上升沿清零内部时钟计数器
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);    //从模式从接口一接收被测信号上升沿
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);  //从模式接收上升沿后触发Reset操作
	
	//第六步,启动定时器
	TIM_Cmd(TIM3,ENABLE);
}



//获取频率
uint32_t IC_GetFreg(void){
	return 1000000/(TIM_GetCapture1(TIM3)+1);
}

//获取占空比
uint32_t IC_GetDuty(void){
	return floor(TIM_GetCapture2(TIM3)+1)/floor(TIM_GetCapture1(TIM3)+1)*100;
}

