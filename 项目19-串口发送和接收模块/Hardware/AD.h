//读取A0-A3总共4个通道的AD值，并且用DMA转运到传入的数组里面
#ifndef __AD_H__
#define __AD_H__

void AD_Init(uint16_t *DateA);        //初始化ADC

/*使用方法：
uint16_t aaa[]={0,0,0,0};
AD_Init(aaa);
然后读取数组内的值即可
*/
#endif
