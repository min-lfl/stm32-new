//会占用定时器2和A0口用于输出PWM波
#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(void);

void PWM_SetCompare1(uint16_t Compare);  //改变占空比

void PWM_SetPrescaler(uint16_t Prescaler);  //改变频率

#endif
