#ifndef __Usart_H__
#define __Usart_H__

void Usart_Init(void);   //初始化串口,波特率9600
void USART1_SendChar(uint8_t ch);   //发送一个字节
uint8_t USART1_ReceiveChar(void);   //接收一个字节
void USART1_SendArray(uint8_t *Array,int8_t len); //发送数组，len为长度，单位字节

#endif
