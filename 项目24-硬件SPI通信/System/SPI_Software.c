#include "stm32f10x.h"                  // Device header

#define SPI_Software_PORT GPIOA         //定义SPI端口
#define SPI_Software_CS GPIO_Pin_4      //定义SPI片选引脚
#define SPI_Software_MISO GPIO_Pin_5    //定义SPI输入脚     接模块DO
#define SPI_Software_SCK GPIO_Pin_6     //定义SPI时钟引脚   接模块CLK
#define SPI_Software_MOSI GPIO_Pin_7    //定义SPI输出引脚   接模块DI


//初始化软件SPI，模式0
void SPI_Software_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟

    //配置SPI引脚
    GPIO_InitStructure.GPIO_Pin = SPI_Software_CS | SPI_Software_SCK | SPI_Software_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Software_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_Software_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
    GPIO_Init(SPI_Software_PORT, &GPIO_InitStructure);

    //初始化引脚状态
    GPIO_SetBits(SPI_Software_PORT, SPI_Software_CS);   //片选高
    GPIO_ResetBits(SPI_Software_PORT, SPI_Software_SCK); //时钟低
}

//开始信号，寄存器操作方式
void SPI_Software_Start(void){
    SPI_Software_PORT->BRR = SPI_Software_CS; //片选低
}

//停止信号，寄存器操作方式
void SPI_Software_Stop(void){
    SPI_Software_PORT->BSRR = SPI_Software_CS; //片选高
}

//通过软件SPI发送并且接收一个字节数据,模式0，拉高读取，先高时钟读取，再低时钟发送
uint8_t SPI_Software_SendByte(uint8_t data){
    uint8_t receivedData = 0;
    for(int i = 0; i < 8; i++){
        //发送数据位
        if(data & 0x80){ //检查最高位
            SPI_Software_PORT->BSRR = SPI_Software_MOSI; //发送1
        } else {
            SPI_Software_PORT->BRR = SPI_Software_MOSI; //发送0
        }
        data <<= 1; //左移数据以准备下一位

        //拉高时钟，读取数据位
        SPI_Software_PORT->BSRR = SPI_Software_SCK; //时钟高
        receivedData <<= 1; //为接收的数据腾出位置
        if(SPI_Software_PORT->IDR & SPI_Software_MISO){ //读取输入引脚
            receivedData |= 0x01; //接收到1
        }

        //拉低时钟
        SPI_Software_PORT->BRR = SPI_Software_SCK; //时钟低
    }
    return receivedData;
}
