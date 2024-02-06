#include "stm32f10x_conf.h"

#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10
void USART_Config(void);
void USART_SendByte(USART_TypeDef* pUSARTx, uint8_t data);
void USART_SendString(USART_TypeDef* pUSARTx, char *str);
