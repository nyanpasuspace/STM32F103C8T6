#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include <stdio.h>

void Delay(u32 dly);

int main(void) {
	LED_Init();
	USART_Config();
	while(1) {
		LED_ON();
		Delay(1000);
		LED_OFF();
		Delay(1000);
		USART_SendByte(USART1, 0x34);
	}
}

void Delay(u32 dly) {
	volatile uint32_t i;
  for (i = 0; i < dly * 8000; i++);
}
