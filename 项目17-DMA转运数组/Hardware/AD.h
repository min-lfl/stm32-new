//这是个读取ADC通道1（A0口）的例子
#ifndef __AD_H__
#define __AD_H__

void AD_Init(void);        //初始化ADC
uint16_t GET_ADC_TD1(void);   //通道1数据
uint16_t GET_ADC_TD2(void);   //通道2数据
uint16_t GET_ADC_TD3(void);   //通道3数据
uint16_t GET_ADC_TD4(void);   //通道4数据
#endif
