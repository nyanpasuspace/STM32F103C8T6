#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"
void TEMP_GPIO_Config(void);
void TEMP_ADC_Config(void);
uint16_t ADC_GetResult(void);
float ConvertToVolt(void);
char* ConvertData(float result);
