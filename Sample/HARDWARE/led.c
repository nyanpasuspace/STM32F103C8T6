#include "led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	// 开启 GPIOA,GPIOB 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// 开启复用时钟，一定要开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// 失能 JTAG，使能 SW
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
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
