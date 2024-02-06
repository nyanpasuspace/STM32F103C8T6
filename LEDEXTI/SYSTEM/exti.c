#include "stm32f10x.h"
#include "misc.h"
#include "exti.h"

void BTN_GTIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	// 开启 GPIOA,GPIOB 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// 指定 IO 口，对应引脚速率，设置输入输出模式
	GPIO_InitStructure.GPIO_Pin = BTN_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BTN_PORT, &GPIO_InitStructure);
}

void NVIC_Config(void) {
	// 嵌套向量中断控制器控制中断
	NVIC_InitTypeDef NVIC_InitStruct;
	// 配置中断优先级分组（设置抢占优先级和相应优先级地分配
	// 此时主优先级 0-1，次优先级 0-7
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	// 配置中断源
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	// 配置优先级
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	// 使能中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	// 初始化
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_Config(void) {
  EXTI_InitTypeDef EXTI_InitStruct ;

	// 设置 EXTI 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// 配置引脚 PB14
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	// 配置中断 / 事件栈
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;
	// 使能 EXTI
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	// 配置模式
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	// 配置触发器
	// 下降触发
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	// 初始化
	EXTI_Init(&EXTI_InitStruct);
	// 中断处理函数 void EXTI0_IRQHandler(void) 在 stm32f10x_it.c 中编写
}

void BTN_EXTI_Config(void) {
	NVIC_Config();
	EXTI_Config();
}
