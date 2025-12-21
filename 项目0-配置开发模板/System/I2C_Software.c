#include "stm32f10x.h"                  // Device header

//I2C引脚定义
#define I2C_SCL_PORT        GPIOA
#define I2C_SCL_PIN         GPIO_Pin_6
#define I2C_SDA_PORT        GPIOA
#define I2C_SDA_PIN         GPIO_Pin_7

//内部延迟函数,延迟约数微秒
void I2C_Delay(void){
    volatile uint8_t i=30;
    while(i--);
}

//根据GPIO端口返回对应的RCC_APB2Periph值,用于使能时钟
static uint32_t GPIO_To_APB2Periph(GPIO_TypeDef* GPIOx)
{
    if (GPIOx == GPIOA) return RCC_APB2Periph_GPIOA;
    if (GPIOx == GPIOB) return RCC_APB2Periph_GPIOB;
    if (GPIOx == GPIOC) return RCC_APB2Periph_GPIOC;
    if (GPIOx == GPIOD) return RCC_APB2Periph_GPIOD;
    if (GPIOx == GPIOE) return RCC_APB2Periph_GPIOE;
#ifdef GPIOF
    if (GPIOx == GPIOF) return RCC_APB2Periph_GPIOF;
#endif
#ifdef GPIOG
    if (GPIOx == GPIOG) return RCC_APB2Periph_GPIOG;
#endif
    return 0; // 传入了不支持的端口
}

//软件I2C引脚初始化
void I2C_Software_Init(void){
    GPIO_InitTypeDef GPIO_InitStruct;
    
    //使能GPIOB时钟
    uint32_t clk = GPIO_To_APB2Periph(I2C_SCL_PORT) | GPIO_To_APB2Periph(I2C_SDA_PORT);
    if (clk == 0) while(1);
    RCC_APB2PeriphClockCmd(clk, ENABLE);
    
    //配置SCL引脚为开漏输出
    GPIO_InitStruct.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStruct);
    
    //配置SDA引脚为开漏输出
    GPIO_InitStruct.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStruct);
	
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN; //初始化后SCL置高电平
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //初始化后SDA置高电平
}


//起始条件
void I2C_Start(void){
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN; //保证SCL高电平
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //保证SDA高电平
	I2C_Delay();
	I2C_SDA_PORT -> BRR = I2C_SDA_PIN;  //先拉低SDA
	I2C_Delay();
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //再拉低SCL
}

//终止条件
void I2C_Stop(void){
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_SDA_PORT -> BRR = I2C_SDA_PIN;  //保证Sda低电平
	I2C_Delay();
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN; //先拉高SCL
	I2C_Delay();
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //再拉高SDA
}

//发送有应答
void I2C_Ack(void){
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_Delay();
	I2C_SDA_PORT -> BRR = I2C_SDA_PIN; //SDA拉低
	I2C_Delay();
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN; //SCL拉高
	I2C_Delay();
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN; //SCL拉低
}

//发送无应答
void I2C_NAck(void){
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_Delay();
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //SDA拉高
	I2C_Delay();
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN; //SCL拉高
	I2C_Delay();
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN; //SCL拉低
}

//发送一个字节，返回应答结果
uint8_t I2C_SendByte(uint8_t byte){
	uint8_t i=0;
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_SDA_PORT -> BRR = I2C_SDA_PIN;  //夺回SDA
	I2C_Delay();
	for(i=0;i<8;i++){  //从高往低依次取出位
		if(byte&(0x80>>i)){
			I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //SDA拉高
		}else{
			I2C_SDA_PORT -> BRR = I2C_SDA_PIN; //SDA拉低
		}
		
		I2C_SCL_PORT -> BSRR = I2C_SCL_PIN;  //SCL拉高把位发送出去
		I2C_Delay();
		I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //SCL拉低准备下一个循环
	}
	//接收应答部分
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN; //同时释放SDA（拉高）
	I2C_Delay();
	I2C_SCL_PORT -> BSRR = I2C_SCL_PIN;
	I2C_Delay();
	if(I2C_SDA_PORT->IDR & I2C_SDA_PIN){
		I2C_SCL_PORT -> BRR = I2C_SCL_PIN;
		return 1;
	}else{
		I2C_SCL_PORT -> BRR = I2C_SCL_PIN;
		return 0;
	}
}

//接收一个字节,ack为是否发送应答
uint8_t I2C_ReceiveByte(uint8_t ack){
	uint8_t byte=0,i=0;
	I2C_SCL_PORT -> BRR = I2C_SCL_PIN;  //保证SCL低电平
	I2C_SDA_PORT -> BSRR = I2C_SDA_PIN;  //把SDA的控制权交给从机
	I2C_Delay();		//这个延迟之后从机应该已经操作了SDA了，所有循环一开始就要马上读取
	for(i=0;i<8;i++){
		I2C_SCL_PORT -> BSRR = I2C_SCL_PIN;  //先拉高，再读取
		I2C_Delay();
		if(I2C_SDA_PORT->IDR & I2C_SDA_PIN){
			byte|=0x80>>i;  //如果读取到就把该位置1
		}//否则不执行操作
		//给从机一个方波脉冲，并且等一段时间让它操作SDA
		I2C_SCL_PORT -> BRR = I2C_SCL_PIN;   //SCL低电平
		I2C_Delay();
	}
	//根据ack决定是否发送应答
	if(ack){
		I2C_Ack();
	}else{
		I2C_NAck();
	}
	return byte;
}


