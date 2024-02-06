#include "temp.h"

void TEMP_GPIO_Config(void) {
	// 使用内部通道，因此不设定引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

void TEMP_ADC_Config(void) {
	// 查看固件库文档对 ADC_InitTypeDef 的说明
	// 配置 ADC1
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 配置通道16为第一个转换通道, 采样时间(1.5个周期)
	// 即 ADC12_IN_16
	// 采样时间根据数据手册最大 17.1μs
	// 根据时间公式调整采样时间参数 采样时间 + 12.5个周期 = 转换时间
	// 1.16μs
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_1Cycles5);
	
	// 参考手册：传感器从关电模式唤醒后到可以输出正确水平的V SENSE
	// 前，有一个建立时间。ADC
	// 在上电后也
	// 有一个建立时间，因此为了缩短延时，应该同时设置ADON
	// 和TSVREFE位
	// 使能内部温度传感器和参考电压
	ADC_TempSensorVrefintCmd(ENABLE);
	// 使能 ADC
	ADC_Cmd(ADC1, ENABLE);
	// 参考手册建议，每次上电后执行一次校准
	// 重置校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)) {}
	// 开始指定校准状态
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)) {}
}

uint16_t ADC_GetResult(void) {
	// 启动ADC转换
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {}
	uint16_t adcValue = ADC_GetConversionValue(ADC1);
  ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
  return adcValue;
}

// 转换数据为电压
// 注意：STM32 附带 ADC 分辨率为 12 位
float ConvertToVolt(void ) {
	// 获取 ADC 数据
	uint16_t adcValue = ADC_GetResult();
	// 获取 ADC 分辨率
	// float resolution = 12.0;
	// 参考电压（假设为 3.3V）
	// float referenceVoltage = 3.3;
	// 计算电压值
	// 2^12
	float voltage = adcValue * 3.3 / 4096.0;
	return voltage;
}

// 转换电压为温度
// 温度(℃) = (v25 - vsense) / Avg_Slope + 25 参考数据手册温度传感器特性
char* ConvertData(float result) {
	float temp = (1.43 - result) / 4.3 + 25.0;
	char* data = malloc(5 * sizeof(char));
	sprintf(data, "%f", temp);
	return data;
}
