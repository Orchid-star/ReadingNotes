```c

```

```c
//rcc.h
/*配置ADCCLK分频器，可以对APB2的72MHz时钟选择2、4、6、8分频，输入到ADCCLK*/
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);

//adc.h
/*恢复缺省配置*/
void ADC_DeInit(ADC_TypeDef* ADCx);
/*初始化*/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
/*结构体初始化*/
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
/*ADC_Cmd，给ADC上电，即开关控制*/
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/*开启DMA输出信号。如果使用DMA转运数据，需用到此函数*/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/*中断输出控制，用于控制中断是否能够通过NVIC*/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
/*复位校准、获取复位校准状态、开始校准、获取开始校准状态，ADC初始化完成后，依次调用即可*/
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
/*软件触发转换*/
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/*获取软件开始转换状态，不能用于判断转换是否完成。此函数是给SWSTART位置1以开始转换，返回的是SWSTART的状态。由于SWSTART位在开始转换后立刻被清零，所以本函数的返回值跟是否转换结束毫无关系。所以本函数一般不用*/
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
/*判断转换是否结束，获取标志位状态。如果转换结束，EOC置1。本函数判断EOC标志位是否置1*/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
/*配置间断模式，第一个函数配置每隔几个通道间断一次，第二个函数配置是否启用间断模式*/
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/*ADC规则组通道配置。本函数重要，作用是给每隔序列的位置填写指定的通道。
参数2 ADC_Channel:指定通道
参数3：序列几的位置
参数4：ADC_SampleTime指定通道的采样时间
*/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
/*外部触发转换控制，配置是否允许外部触发转换*/
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/*获取AD转换的数据寄存器，读取结果使用本函数*/
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
/*获取双模式转换值，双ADC模式读取转换结果的函数*/
uint32_t ADC_GetDualModeConversionValue(void);
/*对模拟看门狗进行配置。第一个是否启动模拟看门狗，第二个配置高低阈值，第三个配置看门的通道*/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
/*温度传感器、内部参考电压控制，开启内部的两个通道*/
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
/*获取标志位状态、清除标志位、获取中断状态、清除中断挂起位*/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);
```



