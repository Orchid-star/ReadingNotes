在stm32中，使用const修饰的变量（即常量）存储在Flash中，Flash只读。

对于变量和常量，它们的地址是由编译器确定的。不同的程序，地址可能不一样。但外设寄存器的地址是固定的，可在手册中查询，在程序中可以用结构体访问寄存器。比如要访问ADC1的DR寄存器，就可以使用ADC1->DR。

```c
//恢复缺省配置
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
//初始化
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
//结构体初始化
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
//使能
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
//中断输出使能
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
//设置当前数据寄存器，即计数器
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber); 
//获取当前计数值
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
//获取标志位状态、清除标志位、获取中断状态、清除中断挂起位 
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);
```

