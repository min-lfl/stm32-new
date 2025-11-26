#include "stm32f10x.h"                  // Device header

// 分散式写法
#define LED1_GPIO_PIN   GPIO_Pin_0					//第一个灯连接的口
#define LED2_GPIO_PIN   GPIO_Pin_1					//第二个灯连接的口
#define LED_GPIO_PORT   GPIOA						//第几组口
#define LED_GPIO_CLK    RCC_APB2Periph_GPIOA		//第几组外设

void LED_Init(void){
	//开启对应外设时钟
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);
	
	//初始化LED接口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN | LED2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStructure);
	
	//初始化后关闭所有LED
	GPIO_ResetBits(LED_GPIO_PORT,LED1_GPIO_PIN);
	GPIO_ResetBits(LED_GPIO_PORT,LED2_GPIO_PIN);
}

void LED1_ON(void){
	GPIO_SetBits(LED_GPIO_PORT,LED1_GPIO_PIN);
}
void LED1_OFF(void){
	GPIO_ResetBits(LED_GPIO_PORT,LED1_GPIO_PIN);
}



void LED2_ON(void){
	GPIO_SetBits(LED_GPIO_PORT,LED2_GPIO_PIN);
}
void LED2_OFF(void){
	GPIO_ResetBits(LED_GPIO_PORT,LED2_GPIO_PIN);
}

uint8_t LED1_OUTGET(void){
	if(GPIO_ReadOutputDataBit(LED_GPIO_PORT,LED1_GPIO_PIN)==1){
		return 1;
	}else{
		return 0;
	}
}

uint8_t LED2_OUTGET(void){
	if(GPIO_ReadOutputDataBit(LED_GPIO_PORT,LED2_GPIO_PIN)==1){
		return 1;
	}else{
		return 0;
	}
}
