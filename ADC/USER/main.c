#include "stm32f10x.h"
#include <stdio.h>

void Delay(u32 dly);

int main(void) {

}

void Delay(u32 dly) {
	volatile uint32_t i;
  for (i = 0; i < dly * 8000; i++);
}
