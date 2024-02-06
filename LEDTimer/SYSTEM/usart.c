#include <stdio.h>
#include "usart.h"
// 使用 USART1
// 位于 APB2：PA9 RX PA10 TX
void USART_Config(void) {
	// 使能 GPIO 时钟和串口时钟
	// USART 引脚类型 IO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	// 输入输出模式的设置参考手册 8.1.4
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	// 下为异步模式，对于同步模式，需要初始化更多初始成员
	// 区分同步异步：看需不需要对外提供时钟输出
	// 发送和接受设备波特率一致
	// 设备管理器设置 
	// 波特率
	USART_InitStructure.USART_BaudRate = 9600;
	// 字长为 8 位数据格式
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 设置 1 为停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 无奇偶校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// 无硬件数据流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 收发模式
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);
	// 如果单片机要接收，串口设置中断
	// USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// 使能串口
	USART_Cmd(USART1, ENABLE);
}

void USART_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data); //发送数据
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET); //等待发送完成
}

void USART_SendString(USART_TypeDef* pUSARTx, char *str)
{
  while(*str)
  {
    USART_SendByte(pUSARTx, *str++);
  }
}

