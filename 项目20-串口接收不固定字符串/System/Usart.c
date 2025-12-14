#include "stm32f10x.h"                  // Device header
#include <DELAY.H>
#include <stdio.h>
#include "Usart.h"

//模块内部变量区
uint8_t usart1_rxbyteflag=0; //接收字节标志位
uint8_t usart1_byte=0; //接收的字节缓存区


char usart1_RXdata[100]={0}; //定义接收字符串缓存区
uint8_t usart1_RXindex=0; //接收字符串索引
uint8_t usart1_RXflag=0; //接收字符串标志位

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
//串口1中断函数接收字符串，字符串以@开头，以\n结尾，字符串长度不固定，最长100，
//状态机编程法，在中断函数内调用，
//状态变量Code为0时等待字符串头@，状态为1时接收字符串，并且在接收完成后设置接收完成标志位
//在接收完毕后再字符串末尾添加一个结束符'\0'
void USART1_IRQHandler(void){
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //接收到数据
		usart1_byte = USART_ReceiveData(USART1); //读取接收到的数据
		
		//状态机处理接收的字符串
		static uint8_t Code=0; //状态变量，初始状态为0，等待字符串头@
		if(Code==0){
			if(usart1_byte=='@'){ //检测到字符串头@
				Code=1; //切换到接收状态
				usart1_RXindex=0; //索引清零
			}
		}else if(Code==1){
			if(usart1_byte=='\r' | usart1_byte=='\n'){ //检测到字符串尾\n
				usart1_RXdata[usart1_RXindex++]='\0'; //添加结束符
				usart1_RXflag=1; //设置接收完成标志位
				Code=0; //切换回等待状态
			}else{
				usart1_RXdata[usart1_RXindex++]=usart1_byte; //存储接收到的字符
				if(usart1_RXindex>=100){ //防止溢出
					Code=0; //切换回等待状态
				}
			}
		}
		
		usart1_rxbyteflag=1; //设置接收字节标志位
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


//返回接收到的字符串标志位,并且置0
uint8_t USART1_ReceiveStringFlag(void){
	usart1_RXflag=0; //清除标志位
	return usart1_RXflag;
}

//返回接收到的字符串数组首地址
char* USART1_ReceiveString(void){
	return usart1_RXdata; //返回接收到的字符串首地址
}


