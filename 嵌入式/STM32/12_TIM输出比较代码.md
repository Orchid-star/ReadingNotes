**工程1 PWM驱动LED呼吸灯**

 **1 电路接线**

在PA0引脚上插一个LED，目标是在PA0引脚输出一个PWM波，用于驱动LED并且呈现不同的亮度。具体接法是正极接在PA0引脚，负极接在GND的驱动方法，即高电平点亮，低电平熄灭，所以PWM波占空比越大，LED越亮。

**2 工程代码**

	第1步：RCC开启时钟，将要用的TIM外设和GPIO外设的时钟打开
	
	第2步：配置时基单元，包括时钟源选择
	
	第3步：配置输出比较单元，包括CCR的值、输出比较模式、极性选择、输出使能等参数,在库函数中使用结构体统一配置
	
	第4步：配置GPIO，将PWM对应的GPIO口初始化为复用推挽输出的配置
	
	第5步：启动计数器
在tim.h头文件查看以下函数：

```c
/*
下面4个函数就是配置OC的，OC是Output Compare。输出比较有4个，所以有4个函数。OC1~OC4一个函数配置一个单元。
这4个初始化函数对应4个OC单元，或者说OC通道。不同的通道对应的GPIO口是不一样的。如使用PA0口,对应的是第一个OC通道
参数：TIMx 选择定时器
参数：TIM_OCInitStruct 输出比较的参数
*/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);

/*
给输出比较结构体赋一个默认值
*/
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);

/*配置强制输出模式，在运行中需要暂停输出波形并且强制输出高或低电平，用此函数。了解即可*/
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);

/*配置CCR寄存器的预装功能，写入的值不会立即生效，而是在更新事件才会生效。了解即可*/
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);

/*配置快速使能。了解即可*/
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);

/*外部事件时清除REF信号，了解即可*/
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);

/*单独设置OC的极性，带N的是高级定时器里互补通道的配置，OC4没有互补通道。在结构体初始化函数也可以设置极性*/
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);

/*单独修改输出使能参数*/
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);

/*选择OC模式，此函数用来单独更改输出比较模式*/
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);

/*单独更改CCR寄存器值的函数，重要，运行时更改占空比需要使用此函数*/
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
```



