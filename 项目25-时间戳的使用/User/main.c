#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>
#include <OLED.H>
#include <CountSensor.H>
#include <Encoder.H>
#include <Timer.H>
#include <PWM.H>
#include <motor.H>
#include <IC.H>
#include <Encoder_time.H>
#include <AD.H>
#include <MyDMA.H>
#include <Usart.H>
#include <I2C_Software.H>
#include <MPU6050_Sensor.H>
#include <MPU6050_Hardware.h>
#include <W25Q64_Sensor.h>
#include <W25Q64_Hardware.h>
#include <SPI_Hardware.h>

uint32_t address = 0x00000067; //W25Q64地址
uint8_t Write_Date = 0;  //写入的数据
uint8_t Read_Date = 0;   //读取的数据


//主函数
int main(void){
	OLED_Init();
	W25Q64_Hardware_Init(); //初始化W25Q64
	OLED_ShowString(1,1,"W25QXX:");


	// //显示厂商ID和设备ID
	// uint8_t manufacturerID = 0;
	// uint16_t deviceID = 0;
	// W25Q64_Hardware_ReadID(&manufacturerID, &deviceID);
	// OLED_ShowHexNum(2, 1, manufacturerID, 2);
	// OLED_ShowHexNum(2, 5, deviceID, 4);


	//写入一个字节
	Write_Date = 0x24; //要写入的数据
	W25Q64_Hardware_PageErase(address); //页擦除
	Delay_ms(10); //等待擦除完成
	W25Q64_Hardware_WriteByte(address, Write_Date); //写入数据
	Delay_ms(10); //等待写入完成

	//读取一个字节
	Read_Date = W25Q64_Hardware_ReadByte(address); //读取数据
	OLED_ShowString(2,1,"Read:");
	OLED_ShowHexNum(2,6,Read_Date,2); //显示读取的数据
	
	//主循环
	while(1){

	
	}
}


