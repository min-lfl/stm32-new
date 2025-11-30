#include "stm32f10x.h"                  // Device header

// 分散式写法
#define LightSensor_GPIO_PIN   	GPIO_Pin_12					//光敏电阻DO接口
#define LightSensor_GPIO_PORT   GPIOA						//第几组口
#define LightSensor_GPIO_CLK    RCC_APB2Periph_GPIOA		//第几组外设


void LightSensor_Init(void) {
    RCC_APB2PeriphClockCmd(LightSensor_GPIO_CLK, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = LightSensor_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(LightSensor_GPIO_PORT, &GPIO_InitStructure);
}

/**
	* @brief		获取光敏电阻DO口的值，返回按键0或1
	* @param		无
	* @retval		按键的键值，0或1
	*/
uint8_t LightSensorDo_GetNum(void){
	return GPIO_ReadInputDataBit(LightSensor_GPIO_PORT,LightSensor_GPIO_PIN);
}
