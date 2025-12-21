#ifndef __MPU6050_reg_H__
#define __MPU6050_reg_H__

// MPU6050寄存器定义
// 读取数据寄存器地址
#define MPU6050_ACCEL_XOUT_H     0x3B // 加速度计X轴高字节寄存器
#define MPU6050_ACCEL_XOUT_L     0x3C // 加速度计X轴低字节寄存器
#define MPU6050_ACCEL_YOUT_H     0x3D // 加速度计Y轴高字节寄存器
#define MPU6050_ACCEL_YOUT_L     0x3E // 加速度计Y轴低字节寄存器
#define MPU6050_ACCEL_ZOUT_H     0x3F // 加速度计Z轴高字节寄存器
#define MPU6050_ACCEL_ZOUT_L     0x40 // 加速度计Z轴低字节寄存器

#define MPU6050_TEMP_OUT_H       0x41 // 温度高字节寄存器
#define MPU6050_TEMP_OUT_L       0x42 // 温度低字节寄存器

#define MPU6050_GYRO_XOUT_H      0x43 // 陀螺仪X轴高字节寄存器
#define MPU6050_GYRO_XOUT_L      0x44 // 陀螺仪X轴低字节寄存器
#define MPU6050_GYRO_YOUT_H      0x45 // 陀螺仪Y轴高字节寄存器
#define MPU6050_GYRO_YOUT_L      0x46 // 陀螺仪Y轴低字节寄存器
#define MPU6050_GYRO_ZOUT_H      0x47 // 陀螺仪Z轴高字节寄存器
#define MPU6050_GYRO_ZOUT_L      0x48 // 陀螺仪Z轴低字节寄存器

#define MPU6050_WHO_AM_I         0x75 // 器件识别寄存器

// 配置寄存器地址
#define MPU6050_PWR_MGMT_1       0x6B // 电源管理寄存器1，可以参考 @ref MPU6050_ClockSource枚举类型
#define MPU6050_PWR_MGMT_2       0x6C // 电源管理寄存器2
#define MPU6050_SMPLRT_DIV       0x19 // 采样率分频器寄存器
#define MPU6050_CONFIG           0x1A // 配置寄存器，低通滤波设置
#define MPU6050_GYRO_CONFIG      0x1B // 陀螺仪配置寄存器
#define MPU6050_ACCEL_CONFIG     0x1C // 加速度计配置寄存器

//电源管理寄存器1配置列表
typedef enum {
    MPU6050_CLOCK_INTERNAL = 0x00,   // 内部8MHz振荡器，    默认配置
    MPU6050_CLOCK_PLL_XGYRO = 0x01,  // PLL与X轴陀螺仪参考，推荐配置陀螺仪时钟
    MPU6050_CLOCK_PLL_YGYRO = 0x02,  // PLL与Y轴陀螺仪参考
    MPU6050_CLOCK_PLL_ZGYRO = 0x03,  // PLL与Z轴陀螺仪参考
    MPU6050_CLOCK_PLL_EXT32K = 0x04, // PLL与外部32.768kHz参考
    MPU6050_CLOCK_PLL_EXT19M = 0x05, // PLL与外部19.2MHz参考
    MPU6050_CLOCK_KEEP_RESET = 0x07  // 保持时钟停止，保持复位状态
} MPU6050_ClockSource;

// //电源管理寄存器2配置列表
// typedef enum {
    
// }

#endif

