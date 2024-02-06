#include "stm32f10x.h"
#include "led.h"
#include "exti.h"

void Delay(u32 dly);
void EXTI_Config(void);
int main(void) {
	LED_Init();
	BTN_GTIO_Config();
	BTN_EXTI_Config();
	
	LED_ON();
	Delay(1000);
	LED_OFF();
	Delay(1000);
	
	while(1) {
		Delay(1000);
	}
}

void Delay(u32 dly) { 
	volatile uint32_t i;
  for (i = 0; i < dly * 8000; i++);
}
