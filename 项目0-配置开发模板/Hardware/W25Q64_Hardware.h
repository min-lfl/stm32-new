#ifndef __W25Q64_Hardware_H__
#define __W25Q64_Hardware_H__

void W25Q64_Hardware_Init(void);                    //初始化W25Q64
void W25Q64_Hardware_PageErase(uint32_t address);   //指定位置页擦除
void W25Q64_Hardware_WriteByte(uint32_t address, uint8_t data);//指定位置写入一个字节
uint8_t W25Q64_Hardware_ReadByte(uint32_t address); //指定位置读取一个字节
void W25Q64_Hardware_ReadID(uint8_t* manufacturerID, uint16_t* deviceID);//读取厂商ID和设备ID

#endif

