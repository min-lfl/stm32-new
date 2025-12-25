//硬件SPI驱动头文件
//接线方式:
//SPI1_SCK  --> PA5
//SPI1_MISO --> PA6   接模块DO，接收数据
//SPI1_MOSI --> PA7   接模块DI，发送数据
//SPI1_NSS  --> PA4
#ifndef __SPI_Hardware_H__
#define __SPI_Hardware_H__

void SPI_Hardware_Init(void);
void SPI_Hardware_Start(void);
void SPI_Hardware_Stop(void);
uint8_t SPI_Hardware_SendByte(uint8_t data);

#endif

