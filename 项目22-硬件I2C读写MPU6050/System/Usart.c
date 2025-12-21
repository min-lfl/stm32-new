#include "stm32f10x.h"                  // Device header
#include <DELAY.H>
#include <stdio.h>
#include "Usart.h"

//模块内部变量区
uint8_t usart1_rxbyteflag=0; //接收字节标志位
uint8_t usart1_byte=0; //接收的字节缓存区
uint8_t usart1_rxdateflag=0; //接收数据包标志位
uint8_t usart1_RXdata[4]={0,0,0,0};//定义接收数据包缓存区


uint8_t usart1_TXdata[4];//定义固定4位发送数据包



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

	//开启串口1接收中断
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//开启接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//使能串口1
	USART_Cmd(USART1,ENABLE);
}

//###########发送部分#################################################################
//轮询发送一个字节
//参数1：要发送的字节
void USART1_SendChar(uint8_t ch)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  // 等待发送缓冲区空
    USART_SendData(USART1, ch);
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

//发送字符串
//参数：字符串首地址
void USART1_SendString(char *str){
	while(*str){
		USART1_SendChar(*str++);
	}
}


//发送十进制数（文本模式）
//参数：要发送的数字
void USART1_SendNumber(uint32_t num){
	uint8_t buf[10]; //存放数字字符
	uint8_t i=0;
	if(num==0){
		USART1_SendChar('0');
		return;
	}
	while(num){
		buf[i++]=num%10+'0';
		num/=10;
	}
	while(i--){
		USART1_SendChar(buf[i]);
	}
}

//发送一个16进制数（文本模式）
void USART1_SendHexNum(uint32_t num,int8_t len){
	int8_t i;
	uint8_t temp;
	for(i=len-1;i>=0;i--){
		temp=(num>>(i*4))&0x0F;
		if(temp<10){
			USART1_SendChar(temp+'0');
		}else{
			USART1_SendChar(temp-10+'A');
		}
	}
}

//发送浮点数（文本模式）
//参数：要发送的浮点数
void USART1_SendFloat(float fnum){
	uint32_t intpart;
	uint32_t fracpart;
	
	intpart = (uint32_t)fnum; //整数部分
	fracpart = (uint32_t)((fnum - intpart)*10000); //小数部分，保留4位
	
	USART1_SendNumber(intpart); //发送整数部分
	USART1_SendChar('.');       //发送小数点
	USART1_SendNumber(fracpart); //发送小数部分
}

//重定向c库函数printf到串口1，内部函数
//使用方法1：printf("Hello World\r\n");
//使用方法2：printf("num=%d\r\n",num);
int fputc(int ch, FILE *f)
{
	USART1_SendChar((uint8_t)ch);
	return ch;
}

//发送一个数据包，固定4位，头为0xff,尾为0xfe
void USART1_SendPacket(void){
	USART1_SendChar(0xff); //发送包头
	USART1_SendArray(usart1_TXdata,4); //发送数据部分
	USART1_SendChar(0xfe); //发送包尾
}


//###########接收部分######################################################################
//中断接收一个数据包，固定4位，头为0xff,尾为0xfe，状态机设计，状态0为等待包头，状态1为接收数据，状态2为等待包尾
//如果不是按协议接收，则丢弃数据，重新等待包头并且返回接收到的最后一个字节
void USART1_IRQHandler(void){
	uint8_t res;
	static uint8_t usart1_rxstate=0; //接收状态机状态变量
	static uint8_t usart1_rxindex=0; //接收数据包索引
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //接收到数据
		res=USART_ReceiveData(USART1); //读取接收到的数据
		
		switch(usart1_rxstate){
			case 0: //等待包头
				if(res==0xff){ //收到包头，进入接收数据状态
					usart1_rxstate=1;
					usart1_rxindex=0;
				}
				break;
			case 1: //接收数据
				usart1_RXdata[usart1_rxindex++]=res; //存储接收到的数据
				if(usart1_rxindex>=4){ //数据接收完毕，进入等待包尾状态
					usart1_rxstate=2;
				}
				break;
			case 2: //等待包尾
				if(res==0xfe){ //收到包尾，数据包接收完成
					usart1_rxdateflag=1; //置数据包接收完成标志位
				}
				//无论是否收到正确的包尾，都回到等待包头状态
				usart1_rxstate=0;
				break;
			default:
				usart1_rxstate=0;
				break;
		}
		
		//同时设置字节接收标志位和缓存字节
		usart1_byte=res;
		usart1_rxbyteflag=1;
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //清除中断标志位
	}
}

//返回接收字节标志位
uint8_t USART1_ReceiveByteFlag(void){
	return usart1_rxbyteflag;
}

//返回接收到的字节，并且清除字节标志位
uint8_t USART1_ReceiveByte(void){
	usart1_rxbyteflag=0; //清除标志位
	return usart1_byte; //返回接收到的字节
}


//返回接收数据包标志位
uint8_t USART1_ReceiveDateFlag(void){
	return usart1_rxdateflag;
}

//返回接收到的数据包，置为接收数据包标志位
uint8_t* USART1_ReceivePacket(void){
	usart1_rxdateflag=0; //清除标志位
	return usart1_RXdata; //返回接收到的数据包
}

