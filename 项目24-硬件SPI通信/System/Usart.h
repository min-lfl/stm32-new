#ifndef __Usart_H__
#define __Usart_H__

void Usart_Init(void);   //初始化串口,波特率9600
void USART1_SendChar(uint8_t ch);   //发送一个字节
void USART1_SendArray(uint8_t *Array,int8_t len); //发送数组，len为长度，单位字节
void USART1_SendString(char *str); //发送字符串
void USART1_SendNumber(uint32_t num); //发送数字（文本模式）
void USART1_SendHexNum(uint32_t num,int8_t len); //发送一个16进制数（文本模式）
void USART1_SendFloat(float num); //发送浮点数（文本模式）
void USART1_SendPacket(void); //发送一个数据包，固定4位，头为0xff,尾为0xfe,记得引用extern uint8_t usart1_TXdata[4];//发送数组


uint8_t USART1_ReceiveByteFlag(void);//返回接收字节标志位
uint8_t USART1_ReceiveByte(void);//返回接收到的字节，并且清除字节标志位
uint8_t USART1_ReceiveDateFlag(void);//返回接收数据包标志位
uint8_t* USART1_ReceivePacket(void);//返回接收到的数据包，置为接收数据包标志位,数据包固定4位，头为0xff,尾为0xfe

#endif
