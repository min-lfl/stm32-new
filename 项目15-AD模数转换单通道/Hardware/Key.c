#include "stm32f10x.h"                  // Device header
#include <DELAY.H>


// 分散式写法
#define KEY1_GPIO_PIN   GPIO_Pin_10					//第一个口
#define KEY2_GPIO_PIN   GPIO_Pin_11					//第二个口
#define KEY_GPIO_PORT   GPIOB						//第几组口
#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOB		//第几组外设


void Key_Init(void) {
    RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN|KEY2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);
}

/**
	* @brief		获取按键的值，返回按键1或2
	* @param		无
	* @retval		按键的键值，1或2
	*/
uint8_t Key_GetNum(void){
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_GPIO_PIN) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_GPIO_PIN) == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_GPIO_PIN) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_GPIO_PIN) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	return KeyNum;
}

