#include "stm32f10x.h"                  // Device header


void AD_Init(uint16_t *DateA){
	//第一步，打开ADC1和GPIO和DMA1的电源
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//第二步，给所有ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//第三步，配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;					                       //定义类型
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	                               //设置模式，看情况，八种模式  ***设置输入模式函数***
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;     //设置端口号，控制A0这里填0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     	                       //设置频率（不省电无脑50hz）
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第四步，把通道写入序列，用来给通道的扫描顺序排序
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	//第五步，用结构体初始化ADC外设
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                        //打开连续模式，使能一次，转化多次
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                    //转化数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;       //关于外部触发，这里使用软件启动
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                        //ADC设置为独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 4;                                   //扫描模式下，总共扫描几个通道
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;                              //打开扫描模式
	ADC_Init(ADC1,&ADC_InitStruct);
	
	
	//初始化DMAADCx->DR
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.DMA_BufferSize = 4;                                     //缓冲区大小，表示要转运几个单元的数据，与之对应的是DMA_SetCurrDataCounter()函数
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                        //设定外设为源
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                              //指定软件传输（用于内存到内存），还是硬件传输，这里硬件
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)DateA;                   //  目标（内存）地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;       //  目标地址长度,16位
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                   //  目标（内存）是否递增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                           //转运是否循环，这里开启循环，关闭循环不自动重装，如果内存到内存不能循环
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);         //  源（外设）地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//  源地址数据长度,16位
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;          //  源（外设）是否递增
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;                       //优先级，中等就好
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//允许ADC的DMA请求
	ADC_DMACmd(ADC1,ENABLE);
	//第六步，使能ADC，开始转化,使能DMA
	ADC_Cmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	//校准ADC，含等待校准完成判断
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	//软件触发一次，开始扫描
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

