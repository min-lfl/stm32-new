#include "stm32f10x.h"                  // Device header
#include <DELAY.H>


//串口1初始化，波特率9600
void Usart_Init(void){
	//给串口1模块上电，GPIOA上电
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//初始化端口，复用开漏输出
	GPIO_InitTypeDef GPIO_InitStructure;					//定义类型
	 /* 2. 配置 PA9 = TX（复用推挽输出） */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 3. 配置 PA10 = RX（浮空输入） */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//初始化串口1
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;                                      //约定波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //流控制启动还是禁用
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //指定模式发送和接收
	USART_InitStruct.USART_Parity = USART_Parity_No;                             //校验位配置为无校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;                          //停止位设置1位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                     //数据长度选择8位                                    //

	USART_Init(USART1,&USART_InitStruct);
	
	//使能串口1
	USART_Cmd(USART1,ENABLE);
}

//轮询发送一个字节
//参数1：要发送的字节
void USART1_SendChar(uint8_t ch)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  // 等待发送缓冲区空
    USART_SendData(USART1, ch);
}

//接收一个字节
//返回值：接收到的数据
uint8_t USART1_ReceiveChar(void)
{
	return (uint8_t)USART_ReceiveData(USART1);
}


//发送数组，len为长度，单位字节
//参数1：数组首地址
//参数2：数组长度，单位字节
void USART1_SendArray(uint8_t *Array,int8_t len){
	uint8_t i=0;

	for(i=0;i<len;i++)
	{
		USART1_SendChar(Array[i]);
		Delay_us(100);
	}
}

