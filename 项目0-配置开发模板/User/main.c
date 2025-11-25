#include "stm32f10x.h"                  // Device header
#include <stdio.h>


int main(void){
//	################寄存器操作示例##################
//	RCC->APB2ENR = 0x00000010;
//	GPIOC->CRH = 0x00300000;
//	GPIOC->ODR = 0x00002000;   //把板子上的灯熄灭
//	GPIOC->ODR = 0x00000000;   //把板子上的灯点亮
	
//	################库函数操作示例##################
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;				//定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//设置结构体模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			//设置结构体引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置结构体频率
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//初始化端口，通过结构体里的设置
	
	int aaa,bbb,ccc;
	volatile uint32_t debugClock = SystemCoreClock;
	while(1){
		GPIO_SetBits(GPIOC,GPIO_Pin_13);					//给g13口高电平
		for(aaa=0;aaa<1000;aaa++){
			for(bbb=0;bbb<1000;bbb++);
		}
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);					//给g13口低电平
		for(aaa=0;aaa<1000;aaa++){
			for(bbb=0;bbb<1000;bbb++);
		}
	}
}
