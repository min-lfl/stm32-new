#ifndef __Usart_H__
#define __Usart_H__

void Usart_Init(void);   //初始化串口1
void USART1_SendChar(uint8_t ch);   //发送
uint8_t USART1_ReceiveChar(void);   //接收一个字节
#endif
