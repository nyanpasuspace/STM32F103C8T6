#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "tim.h"
#include <stdio.h>

void Delay(u32 dly);

int main(void) {
	Clock_Init();
	LED_Init();
	USART_Config();
	TIM_NVIC_Config();
	TIM_Config();
	LED_ON();
	while(1);
}

void Delay(u32 dly) {
	volatile uint32_t i;
  for (i = 0; i < dly * 8000; i++);
}
