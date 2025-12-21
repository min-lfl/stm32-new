//软件模拟I2C六个模块,包括起始信号,停止信号,应答信号,无应答信号,发送一个字节,接收一个字节
#ifndef __I2C_SOFTWARE_H__
#define __I2C_SOFTWARE_H__

void I2C_Software_Init(void);                 //软件I2C初始化，包含引脚配置

void I2C_Start(void);                //发送起始信号
void I2C_Stop(void);                 //发送停止信号 
void I2C_Ack(void);                  //发送应答信号
void I2C_NAck(void);                 //发送无应答信号
uint8_t I2C_SendByte(uint8_t byte);  //发送一个字节，返回应答结果
uint8_t I2C_ReceiveByte(uint8_t ack);//接收一个字节


#endif
