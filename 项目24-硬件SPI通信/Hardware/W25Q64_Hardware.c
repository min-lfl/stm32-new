#include "stm32f10x.h"                  // Device header
#include <DELAY.H>
#include "SPI_Hardware.h"           //硬件SPI头文件

//初始化W25Q64
void W25Q64_Hardware_Init(void){
    //初始化W25Q64所需的SPI引脚
    SPI_Hardware_Init();
}

//读取状态寄存器1,等待W25Q64空闲,5ms超时
void W25Q64_Hardware_WaitBusy(void){
    uint8_t status = 0;
    uint32_t timeout = 5000; //5ms超时
    do{
        SPI_Hardware_Start();
        SPI_Hardware_SendByte(0x05); //读取状态寄存器1命令
        status = SPI_Hardware_SendByte(0xFF); //读取状态寄存器1的值
        SPI_Hardware_Stop();
        if(!(status & 0x01)){ //检查忙标志位
            break; //空闲，退出循环
        }
        Delay_ms(1);
        timeout--;
    }while(timeout > 0);
}

//指定位置页擦除
void W25Q64_Hardware_PageErase(uint32_t address){
    //写使能
    W25Q64_Hardware_WaitBusy(); //等待空闲
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x06); //写使能命令
    SPI_Hardware_Stop();
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x20); //页擦除命令
    SPI_Hardware_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Hardware_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Hardware_SendByte(address & 0xFF);         //地址低8位
    SPI_Hardware_Stop();
}

//指定位置写入一个字节
void W25Q64_Hardware_WriteByte(uint32_t address, uint8_t data){
    W25Q64_Hardware_WaitBusy(); //等待空闲
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x06); //写使能命令
    SPI_Hardware_Stop();
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x02); //写命令
    SPI_Hardware_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Hardware_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Hardware_SendByte(address & 0xFF);         //地址低8位
    SPI_Hardware_SendByte(data);                    //写入数据
    SPI_Hardware_Stop();
}


//指定位置读取一个字节
uint8_t W25Q64_Hardware_ReadByte(uint32_t address){
    W25Q64_Hardware_WaitBusy(); //等待空闲
    uint8_t receivedData;
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x03); //读命令
    SPI_Hardware_SendByte((address >> 16) & 0xFF); //地址高8位
    SPI_Hardware_SendByte((address >> 8) & 0xFF);  //地址中8位
    SPI_Hardware_SendByte(address & 0xFF);         //地址低8位
    receivedData = SPI_Hardware_SendByte(0xFF);    //读取数据
    SPI_Hardware_Stop();
    return receivedData;
}

//读取厂商ID和设备ID
void W25Q64_Hardware_ReadID(uint8_t* manufacturerID, uint16_t* deviceID){
    W25Q64_Hardware_WaitBusy(); //等待空闲
    SPI_Hardware_Start();
    SPI_Hardware_SendByte(0x9f); //读取ID命令
    *manufacturerID = SPI_Hardware_SendByte(0xFF); //读取厂商ID
    uint8_t deviceIDHigh = SPI_Hardware_SendByte(0xFF); //读取设备ID高8位
    uint8_t deviceIDLow = SPI_Hardware_SendByte(0xFF);  //读取设备ID低8位
    *deviceID = (deviceIDHigh << 8) | deviceIDLow; //合并设备ID
    SPI_Hardware_Stop();
}

