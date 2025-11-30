#ifndef __CountSensor_H__
#define __CountSensor_H__

void CountSensor_Init(void);

/*中断模板，在^_^处添加要执行的函数
void EXTI15_10_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line14) == SET){
		^_^
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
*/

#endif
