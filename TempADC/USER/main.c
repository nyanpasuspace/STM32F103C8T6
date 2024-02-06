#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "temp.h"
#include "tim.h"
#include <stdio.h>

void Delay(u32 dly);

int main(void) {
	Clock_Init();
	LED_Init();
	LED_ON();
	USART_Config();
	TEMP_GPIO_Config();
	TEMP_ADC_Config();
	TIM_NVIC_Config();
	TIM_Config();
	// 通过定时器来定时 1s, 在更新中断里传输数据
	while(1);
}

void Delay(u32 dly) {
	volatile uint32_t i;
  for (i = 0; i < dly * 8000; i++);
}
