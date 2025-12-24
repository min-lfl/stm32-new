#ifndef __MPU6050_H__
#define __MPU6050_H__

void MPU6050_Init(void);                             // 初始化MPU6050
void MPU6050_WriteByte(uint8_t reg, uint8_t data);   // 指定位置写入一个字节，参数1寄存器地址，参数2数据
uint8_t MPU6050_ReadByte(uint8_t reg);               // 指定位置读取一个字节，参数1寄存器地址，返回值数据


void MPU6050_ReadXYZ(int16_t* MPUxyz);              //返回一个六位int16的数组，数组内值分别是加速度计xyz轴，陀螺仪xyz轴


#endif

