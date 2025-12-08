//这是个读取ADC通道1（A0口）的例子
#ifndef __AD_H__
#define __AD_H__

void AD_Init(void);        //初始化ADC
uint16_t GET_ADC(void);    //读取ADC1的值

#endif
