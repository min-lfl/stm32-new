#include "stm32f10x.h"                  // Device header
#include <I2C_Hardware.h>
// #include <OLED.h>

//硬件I2C初始化，包含引脚配置
void I2C_Hardware_Init(void){
    //给I2C模块2和引脚PB10和PB11上电
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //初始化硬件I2C端口
    GPIO_InitTypeDef GPIO_InitStructure;                   //定义类型

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;        //复用开漏模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; //设置端口号，控制A0这里填0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //设置频率（不省电无脑50hz）
    GPIO_Init(GPIOB,&GPIO_InitStructure);


    //初始化I2C
    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;                                //发送完后要不要给应答位
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  //地址位是7位还是10位
    I2C_InitStruct.I2C_ClockSpeed = 80000;                                  //时钟频率，影响发送速度，0-100000是低速模式，100000-400000是高速模式
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_16_9;                      //高速模式下的占空比，只有在高速模式下才生效
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;                                 //主从模式，这里不配置多主机模式或作为从机默认填I2C
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;                                  //指定多主机模式或者作为从机时的自身地址
    I2C_Init(I2C2,&I2C_InitStruct);

    I2C_Cmd(I2C2,ENABLE);
}


//发送开始信号
void I2C_Hardware_Start(void){

    I2C_GenerateSTART(I2C2,ENABLE); //发送开始信号
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)  != SUCCESS){
        
    }
}

//发送终止信号
void I2C_Hardware_Stop(void){
    
    I2C_GenerateSTOP(I2C2,ENABLE);  //发送终止信号
}

//发送应答信号
void I2C_Hardware_Ack(void){
    I2C_AcknowledgeConfig(I2C2,ENABLE);  //启用应答功能
}

//发送无应答信号
void I2C_Hardware_NAck(void){
    I2C_AcknowledgeConfig(I2C2,DISABLE);   
}


//发送7位地址加读写位，并且返回应答,有应答为0，无应答为1
uint8_t I2C_Hardware_Address_rw(uint8_t Address,uint8_t Read_and_write){
    I2C_Send7bitAddress(I2C2,Address,Read_and_write);
    if(Read_and_write){
        while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)  != SUCCESS){
        // 未收到应答
        if (I2C_GetFlagStatus(I2C2, I2C_FLAG_AF) == SET)
        {
            // 必须手动清除 AF
            I2C_ClearFlag(I2C2, I2C_FLAG_AF);
            I2C_GenerateSTOP(I2C2, ENABLE); //停止喊麦
            return 1;   // NACK
        }
    }
    }else{
        while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)  != SUCCESS){
        // 未收到应答
        if (I2C_GetFlagStatus(I2C2, I2C_FLAG_AF) == SET)
        {
            // 必须手动清除 AF
            I2C_ClearFlag(I2C2, I2C_FLAG_AF);
            I2C_GenerateSTOP(I2C2, ENABLE); //停止喊麦
            return 1;   // NACK
        }
    }
    }
    //如果跳出循环了，就是收到了应答并且进入了事件，返回0
	return 0;
}



//发送一个字节，返回应答结果,有应答为0，无应答为1
uint8_t I2C_Hardware_SendByte(uint8_t byte){
    I2C_SendData(I2C2,byte);  
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)  != SUCCESS){
        // 未收到应答
        if (I2C_GetFlagStatus(I2C2, I2C_FLAG_AF) == SET)
        {
            // 必须手动清除 AF
            I2C_ClearFlag(I2C2, I2C_FLAG_AF);
            I2C_GenerateSTOP(I2C2, ENABLE); //停止喊麦
            return 1;   // NACK
        }
    }
    //如果跳出循环了，就是收到了应答并且进入了事件，返回0
	return 0;
}


//接收一个字节
uint8_t I2C_Hardware_ReceiveByte(uint8_t ack){
    uint8_t Date=0;
    if(ack){
        I2C_Hardware_Ack(); //发送应答信号
    }else{
        I2C_Hardware_NAck(); //发送无应答信号
        I2C_GenerateSTOP(I2C2, ENABLE); //停止喊麦
    }
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED)  != SUCCESS);
    Date=I2C_ReceiveData(I2C2);

    return Date;
}
