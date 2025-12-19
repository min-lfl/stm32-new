#include "stm32f10x.h"                  // Device header
#include "I2C_Software.h"               // 软件I2C驱动
#include "MPU6050_reg.h"                // MPU6050寄存器定义

uint8_t MPU6050_Address = 0xD0; // MPU6050器件地址（写地址）

void MPU6050_WriteByte(uint8_t reg, uint8_t data);


void MPU6050_Init(void){
    I2C_Software_Init();
    
    MPU6050_WriteByte(MPU6050_PWR_MGMT_1, 0x01);    // 唤醒MPU6050，写入寄存器0x6B，值0x01, 采用陀螺仪时钟
    MPU6050_WriteByte(MPU6050_PWR_MGMT_2,0x00);     // 不设置循环睡眠频率
    MPU6050_WriteByte(MPU6050_SMPLRT_DIV,0x09);     // 采样率分频，10分频，影响耗电和采样快慢
    MPU6050_WriteByte(MPU6050_CONFIG,0x06);         // 把低通滤波调大一点
    MPU6050_WriteByte(MPU6050_GYRO_CONFIG,0x18);    // 陀螺仪配置，设置不自测，设置量程
    MPU6050_WriteByte(MPU6050_ACCEL_CONFIG,0x018);  // 加速度计，高通滤波器相关配置
}

//指定位置写入一个字节，参数1寄存器地址，参数2数据
void MPU6050_WriteByte(uint8_t reg, uint8_t data){
    I2C_Start();
    I2C_SendByte(MPU6050_Address|0x00);     // 发送器件地址+写位
    I2C_SendByte(reg);                      // 发送寄存器地址
    I2C_SendByte(data);                     // 发送数据
    I2C_Stop();
}

//指定位置读取一个字节，参数1寄存器地址，返回值数据
uint8_t MPU6050_ReadByte(uint8_t reg){
    uint8_t data=0;
    I2C_Start();
    I2C_SendByte(MPU6050_Address|0x00);     // 发送器件地址+写位
    I2C_SendByte(reg);                      // 发送寄存器地址
    I2C_Start();
    I2C_SendByte(MPU6050_Address|0x01);     // 发送器件地址+读位
    data = I2C_ReceiveByte(0);              // 接收数据，发送无应答
    I2C_Stop();
    return data;
}

//返回一个六位uint16的数组，数组内值分别是加速度计xyz轴，陀螺仪xyz轴
void MPU6050_ReadXYZ(int16_t* MPUxyz){
    uint8_t Date_H=0,Date_L=0;
    I2C_Start();
    I2C_SendByte(MPU6050_Address|0x00);     // 发送器件地址+写位
    I2C_SendByte(MPU6050_ACCEL_XOUT_H);     // 发送寄存器地址
    I2C_Start();
    I2C_SendByte(MPU6050_Address|0x01);     // 发送器件地址+读位

    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(1);
    MPUxyz[0]=(Date_H<<8) | Date_L;
    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(1);
    MPUxyz[1]=(Date_H<<8) | Date_L;
    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(1);
    MPUxyz[2]=(Date_H<<8) | Date_L;

    I2C_ReceiveByte(1);I2C_ReceiveByte(1);  //越过中间的两个温度值寄存器

    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(1);
    MPUxyz[3]=(Date_H<<8) | Date_L;
    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(1);
    MPUxyz[4]=(Date_H<<8) | Date_L;
    Date_H=I2C_ReceiveByte(1);
    Date_L=I2C_ReceiveByte(0);
    MPUxyz[5]=(Date_H<<8) | Date_L;

    I2C_Stop();                             //发送停止位
}
