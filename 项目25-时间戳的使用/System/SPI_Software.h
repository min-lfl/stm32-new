//软件模拟SPI头文件
//接线方式:
//SPI_Software_CS   --> PA4
//SPI_Software_SCK  --> PA6   接模块CLK
//SPI_Software_MOSI --> PA7   接模块DI
//SPI_Software_MISO --> PA5   接模块DO
#ifndef __SPI_Software_H__
#define __SPI_Software_H__

void SPI_Software_Init(void);                   //初始化软件SPI
void SPI_Software_Start(void);                  //开始信号
void SPI_Software_Stop(void);                   //停止信号  
uint8_t SPI_Software_SendByte(uint8_t data);    //通过软件SPI发送并且接收一个字节数据

#endif
