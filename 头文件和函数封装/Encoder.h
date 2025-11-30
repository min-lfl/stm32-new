//旋转编码器模块，他会占用B0和B1号口的中断
#ifndef __Encoder_H__
#define __Encoder_H__

void Encoder_Init(void);

int16_t GET_Encoder_Count(void);//返回变化的值，如果正转返回正数，反转返回负数
//使用示例，这样会把变化的值更新到主被赋值的变量
//num = num+GET_Encoder_Count();
#endif
