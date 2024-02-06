#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

// PC13
// 定义 LED 端口
#define LED_PORT GPIOC
// 设置引脚
#define LED_PIN GPIO_Pin_13

void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);

#endif
