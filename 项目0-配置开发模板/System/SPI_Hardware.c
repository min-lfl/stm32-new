#include "stm32f10x.h"                  // Device header

//初始化硬件SPI1，模式0
void SPI_Hardware_Init(void){
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE); //使能GPIOA和SPI1时钟

    //配置SPI引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ; //SCK, MISO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置MOSI引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //MOSI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置片选引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //NSS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_4); //片选高

    //配置SPI参数
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主机模式
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8位数据帧
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //时钟空闲低电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //第一个时钟边沿采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //软件管理片选
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //波特率预分频16
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位先传输
    SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC多项式

    SPI_Init(SPI1, &SPI_InitStructure); //初始化SPI1
    SPI_Cmd(SPI1, ENABLE); //使能SPI1

}

//开始信号，寄存器操作方式
void SPI_Hardware_Start(void){
    //片选拉低，寄存器操作
    GPIOA->BRR = GPIO_Pin_4;
}

//停止信号，寄存器操作方式
void SPI_Hardware_Stop(void){
    //片选拉高，寄存器操作
    GPIOA->BSRR = GPIO_Pin_4;
}

//通过硬件SPI发送并且接收一个字节数据,模式0
uint8_t SPI_Hardware_SendByte(uint8_t data){
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); //等待发送缓冲区空
    SPI_I2S_SendData(SPI1, data); //发送数据

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //等待接收缓冲区非空
    return SPI_I2S_ReceiveData(SPI1); //接收数据
}
