

```c
void Encoder_Init(void)
{
	/*
	1.RCC开启时钟，开启GPIO和定时器时钟
	2.配置GPIO，将PA6和PA7配置成输入模式
	3.配置时基单元，PSC一般选择不分频，ARR一般给最大65535，只需要CNT执行计数即可
	4.配置输入捕获单元，编码器接口只需要使用输入捕获单元的滤波器和极性选择两个参数
	5.配置编码器接口模式，调用库函数即可
	6.调用TIM_Cmd启动定时器
	如果想要测量编码器的位置，直接读出CNT的值即可；
	如果想要测量编码器的速度和方向，需要每隔一段固定的闸门时间，取出一次CNT并清零
	*/
}

```

```c
/*
	定时器编码器接口配置。
	参数1：选择定时器
	参数2：选择编码器模式
	参数3，4：分别选择通道1和通道2的电平极性
*/
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
```

