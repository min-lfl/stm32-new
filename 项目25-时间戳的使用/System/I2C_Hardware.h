#ifndef __I2C_Hardware_H__
#define __I2C_Hardware_H__

#define  Write    ((uint8_t)0x00)
#define  Read     ((uint8_t)0x01)

void I2C_Hardware_Init(void);                   //硬件I2C初始化，包含引脚配置
void I2C_Hardware_Start(void);                  //发送开始信号
void I2C_Hardware_Stop(void);                   //发送终止信号
void I2C_Hardware_Ack(void);                    //发送应答信号
void I2C_Hardware_NAck(void);                   //发送无应答信号
uint8_t I2C_Hardware_Address_rw(uint8_t Address,uint8_t Read_and_write);//发送7位地址加读写位，并且返回应答,有应答为0，无应答为1
uint8_t I2C_Hardware_SendByte(uint8_t byte);    //发送一个字节，返回应答结果,有应答为0，无应答为1
uint8_t I2C_Hardware_ReceiveByte(uint8_t ack);  //接收一个字节

#endif

