#include "stm32f10x.h"                  // Device header

//DMA初始化
void MyDMA_Init(void){
	//上电DMA1
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//初始化DMA
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.DMA_BufferSize = 4;                                     //缓冲区大小，表示要转运几个单元的数据，与之对应的是DMA_SetCurrDataCounter()函数
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                        //设定外设为源
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;                               //指定软件传输（用于内存到内存），还是硬件传输，这里软件
	DMA_InitStruct.DMA_MemoryBaseAddr = 0x20000004;                        //  目标（内存）地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           //  目标地址长度,8位
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                   //  目标（内存）是否递增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                             //转运是否循环，关闭循环不自动重装，如果内存到内存不能循环
	DMA_InitStruct.DMA_PeripheralBaseAddr = 0x20000000;                    //  源（外设）地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //  源地址数据长度,8位
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;           //  源（外设）是否递增
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;                       //优先级，中等就好
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

//DMA启动
void DMA_Start(void){
	//关闭DMA
	DMA_Cmd(DMA1_Channel1,DISABLE);
	//写入重装计数器，这里的4会递减，表示向后运4个
	DMA_SetCurrDataCounter(DMA1_Channel1,4);
	//打开DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	//判断转运是否完成,判断完成标志位并清零
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

