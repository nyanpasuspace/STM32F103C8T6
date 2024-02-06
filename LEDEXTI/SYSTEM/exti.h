#include "stm32f10x.h"

// PC14
// 定义按钮端口
#define BTN_PORT GPIOB
// 定义按钮引脚
#define BTN_PIN GPIO_Pin_14
void NVIC_Config(void);
void EXTI_Config(void);
void BTN_GTIO_Config(void);
void BTN_EXTI_Config(void);
