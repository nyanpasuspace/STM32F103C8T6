#include "tim.h"

// 使用普通定时器 TIM2
// 定时器就是计数器
// 1s 更新
void Clock_Init(void) {	
	// 更换时钟源，使用 PLL 达到 72MHz
	RCC_DeInit();
	// 默认HSI切换为HSE
	// RCC_HSEConfig(RCC_HSE_ON);
	// 启用外部晶振
  RCC_HSEConfig(RCC_HSE_ON);
  // 等待晶振工作稳定
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
	// 配置 PLL 输入时钟源为 HSE，倍频系数为 9（输入时钟为 8MHz * 9 = 72MHz）
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
	// 启用 PLL
  RCC_PLLCmd(ENABLE);
  // 等待 PLL 工作稳定
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	// 设置 AHB 时钟 HCLK
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	// 设置低速 APB 时钟
	RCC_PCLK1Config(RCC_HCLK_Div1);
	// 设置高速 APB 时钟
	RCC_PCLK2Config(RCC_HCLK_Div1);
	// 设置系统时钟
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	// 以上为必须设置的时钟，其他时钟根据需要设置
	// 判断是否是设置的时钟
	while(RCC_GetSYSCLKSource() != 0x08) {}
}

void TIM_Config(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// 开启TIM2时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
	// 设置计数器的自动重装值
	// 由于从 0 开始计数，所以减 1
	// 自动重装载寄存器，计数器与此值相同时，可以发生更新中断
	// * 预分频器同自动重装载寄存器可以选择开启影子寄存器机制，以修改值
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
	// 预分频值，将时钟频率除以指定值，得到定时器的时钟频率
	// 此为计数器内部，处于前端的预分频器
	// eg. 预分频器：0 1 计数器：1
	// 因此使用 7200 且 - 1
	// 两个参数最大值 65535
	TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
	// 时钟分割，可继续分频计数器时钟
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 设置计数器模式，此处向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// 自动重装
	// 影子寄存器
  TIM_ARRPreloadConfig(TIM2,ENABLE);
  // 清空中断标志
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  // 启用中断
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  // 启用TIM2外设
  TIM_Cmd(TIM2,ENABLE);
}

void TIM_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
