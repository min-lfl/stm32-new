#include "stm32f10x.h"                  // Device header
#include "SPI_Software.h"               //软件SPI头文件
#include <DELAY.H>

void W25Q64_Init(void){
    //初始化W25Q64所需的SPI引脚
    SPI_Software_Init();
}

//指定位置页擦除
void W25Q64_PageErase(uint32_t address){
    SPI_Software_Start();
    SPI_Software_SendByte(0x20); //页擦除命令
    SPI_Software_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Software_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Software_SendByte(address & 0xFF);         //地址低8位
    SPI_Software_Stop();
    //等待擦除完成，通常需要一些时间，这里可以添加延时或查询状态寄存器
    Delay_ms(3); //简单延时，实际应用中应查询状态寄存器
}

//指定位置写入一个字节
void W25Q64_WriteByte(uint32_t address, uint8_t data){
    SPI_Software_Start();
    SPI_Software_SendByte(0x06); //写使能命令
    SPI_Software_Stop();
    SPI_Software_Start();
    SPI_Software_SendByte(0x02); //写命令
    SPI_Software_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Software_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Software_SendByte(address & 0xFF);         //地址低8位
    SPI_Software_SendByte(data);                    //写入数据
    SPI_Software_Stop();
}


//指定位置读取一个字节
uint8_t W25Q64_ReadByte(uint32_t address){
    uint8_t receivedData;
    SPI_Software_Start();
    SPI_Software_SendByte(0x03); //读命令
    SPI_Software_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Software_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Software_SendByte(address & 0xFF);         //地址低8位
    receivedData = SPI_Software_SendByte(0xFF);    //读取数据
    SPI_Software_Stop();
    return receivedData;
}

//读取厂商ID和设备ID
void W25Q64_ReadID(uint8_t* manufacturerID, uint16_t* deviceID){
    SPI_Software_Start();
    SPI_Software_SendByte(0x9f); //读取ID命令
    *manufacturerID = SPI_Software_SendByte(0xFF); //读取厂商ID
    uint8_t deviceIDHigh = SPI_Software_SendByte(0xFF); //读取设备ID高8位
    uint8_t deviceIDLow = SPI_Software_SendByte(0xFF);  //读取设备ID低8位
    *deviceID = (deviceIDHigh << 8) | deviceIDLow; //合并设备ID
    SPI_Software_Stop();
}
