#include "stm32f10x.h"                  // Device header

// 分散式写法
#define Buzzer_GPIO_PIN   	GPIO_Pin_12					//蜂鸣器的I/O口
#define Buzzer_GPIO_PORT   	GPIOB						//第几组口
#define Buzzer_GPIO_CLK    	RCC_APB2Periph_GPIOB		//第几组外设

void Buzzer_Init(void){
	//开启对应外设时钟
	RCC_APB2PeriphClockCmd(Buzzer_GPIO_CLK,ENABLE);
	
	//初始化LED接口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Buzzer_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Buzzer_GPIO_PORT,&GPIO_InitStructure);
	
	//初始化后关闭蜂鸣器（置高）
	GPIO_SetBits(Buzzer_GPIO_PORT,Buzzer_GPIO_PIN);

}

/**
	* @brief		打开蜂鸣器（置低）
	* @param		无
	* @retval		无
	*/
void Buzzer_ON(void){
	GPIO_ResetBits(Buzzer_GPIO_PORT,Buzzer_GPIO_PIN);
}

/**
	* @brief		关闭蜂鸣器（置高）
	* @param		无
	* @retval		无
	*/
void Buzzer_OFF(void){
	GPIO_SetBits(Buzzer_GPIO_PORT,Buzzer_GPIO_PIN);
}

/**
	* @brief		获取蜂鸣器口输出寄存器状态
	* @param		无
	* @retval		输出状态，1或0
	*/
uint8_t Buzzer_OUTGET(void){
	if(GPIO_ReadOutputDataBit(Buzzer_GPIO_PORT,Buzzer_GPIO_PIN)==1){
		return 1;
	}else{
		return 0;
	}
}
