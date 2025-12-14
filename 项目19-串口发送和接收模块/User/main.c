#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <DELAY.H>
#include <LED.H>
#include <KEY.H>
#include <LightSensor.H>
#include <Buzzer.H>
#include <OLED.H>
#include <CountSensor.H>
#include <Encoder.H>
#include <Timer.H>
#include <PWM.H>
#include <motor.H>
#include <IC.H>
#include <Encoder_time.H>
#include <AD.H>
#include <MyDMA.H>
#include <Usart.H>

uint8_t num=0;
uint8_t i=0;
uint8_t array[]={1,2,3,4};


extern uint8_t usart1_TXdata[4];//引用模块内固定4位发送数据包

//主函数
int main(void){
	OLED_Init();
	Usart_Init();
	OLED_ShowString(1,1,"AD7:");
	

	//主循环
	while(1){
		//接收串口数据包
		if(USART1_ReceiveDateFlag()){ //收到数据包
			uint8_t* rxdata=USART1_ReceivePacket(); //获取数据包指针

			//将接收到的数据包内容发送回去作为回应
			for(i=0;i<4;i++){
				usart1_TXdata[i]=rxdata[i]; //把接收到的数据包内容复制到发送数据包
			}
			USART1_SendPacket(); //发送数据包

			//在OLED上显示接收到的数据
			OLED_ShowString(2,1,"RX:");
			for(i=0;i<4;i++){
				OLED_ShowHexNum(3,1+i*3,rxdata[i],2); //显示每个字节的16进制值
			}
		}
	}
}


