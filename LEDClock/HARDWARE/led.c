#include "led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	// 更换时钟源
	RCC_DeInit();
	// 默认HSI切换为HSE
	RCC_HSEConfig(RCC_HSE_ON);
	// 等待晶振工作
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
	// 设置 AHB 时钟 HCLK
	// 此处分频系数设置为不分频
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	// 设置低速 APB 时钟
	RCC_PCLK1Config(RCC_HCLK_Div2);
	// 设置高速 APB 时钟
	RCC_PCLK2Config(RCC_HCLK_Div1);
	// 设置系统时钟
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	// 以上为必须设置的时钟，其他时钟根据需要设置
	// 判断是否是设置的时钟
	while(RCC_GetSYSCLKSource() != 0x04);
	
	// 开启 GPIOA,GPIOB 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// 指定 IO 口，对应引脚速率，设置输入输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  LED_OFF();
}

// 点亮 LED P13
void LED_ON(void) {
    GPIO_ResetBits(LED_PORT, LED_PIN);
}

// 关闭 LED P13
void LED_OFF(void) {
    GPIO_SetBits(LED_PORT, LED_PIN);
}
