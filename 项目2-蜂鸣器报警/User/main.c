#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//  GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//	GPIO_Write(GPIOA,0xFFFE);
	while(1){
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
		Delay_ms(500);
	}
}
