//会占用定时器2和A0口用于输出PWM波
#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(void);       //通道1，呼吸灯
void PWMservo_Init(void);  //通道2，舵机
void PWMmotor_Init(void);  //通道3，直流电机

#endif
