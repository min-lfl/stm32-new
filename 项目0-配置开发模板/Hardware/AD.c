#include "stm32f10x.h"                  // Device header


void AD_Init(void){
	//第一步，打开ADC1和GPIO的电源
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//第二步，给所有ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//第三步，配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	        //设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	//设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第四步，把通道写入序列，用来给通道的扫描顺序排序
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	//第五步，用结构体初始化ADC
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;     //不打开连续模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //转化数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;             //关于外部触发，这里使用软件触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                 //ADC设置为独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;                 //扫描模式下，总共扫描几个通道
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;           //关闭扫描模式
	
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//第六步，使能ADC，开始转化
	ADC_Cmd(ADC1,ENABLE);
	
	//校准ADC，含等待校准完成判断
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
}
	
uint16_t GET_ADC(void){
	//开始转化
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//返回输出
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

