```c
void IC_Init(void)
{
	/*
	初始化输入捕获步骤：
		1.RCC开启时钟，把GPIO和TIM的时钟打开
		2.GPIO初始化，把GPIO配置成输入模式，一般选择上拉输入模式或者浮空输入模式
		3.配置时基单元，让CNT计数器在内部时钟的驱动下自增运行
		4.配置输入捕获单元，包括滤波器、极性、直连通道还是交叉通道、分频器
		5.选择从模式的触发源，触发源选择TI1FP1，调用库函数给一个参数即可
		6.选择触发之后执行的操作，执行Reset操作，调用一个库函数即可
		6.调用TIM_Cmd函数开启定时器
	当需要读取最新一个周期的频率时，直接读取CCR寄存器，然后按照fc / N，计算即可。
	*/
	/*此处要用到TIM3的通道1，查看引脚定义，TIM3的通道1，2，3，4分别是PA6,PA7,PB0,PB1*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_InternalClockConfig(TIM3);
	
	/*性能分析：fc=1M,计数器最大计到65535，所以可测量的最低频率是1M/65535=15Hz
	频率再低计数器就要溢出。如果要再降低最低频率的限制，可以将PSC再加大一点，这样标准频率
	更低，所支持测量的最低频率也就更低。
	测量频率的上限是标准频率fc，但随着待测频率的增大，误差也会逐渐增大，比待测频率超过标准频率
	1MHz，则无法测量。实际上1MHz的上限已无异议，因为信号频率接近1MHz时误差已经非常大。所以最大
	频率取决于对误差的要求。正负1误差可以认为是1/计数值。如果要求误差等于千分之一时频率为上限，
	此时上限是1M/1000=1KHz。如果误差要求百分之一，则频率上限是1M/100=10kHz。
	可通过修改PSC提高上限。
	对于更高频率的测量，可考虑测频法。
	*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1; //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; //PSC，决定标准频率fc,fc = 72M / (PSC + 1)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1; //因为ICInit函数只有1个，所以此参数指定通道
	TIM_ICInitStruct.TIM_ICFilter = 0xF; //配置输入捕获的滤波器，如果信号有毛刺噪声，可以增大滤波器参数，有效避免干扰
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising; //边沿检测极性选择，选择是上升沿触发还是下降沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI; //配置数据选择器，选择直连通道还是交叉通道
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	
#if 1
	TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);
#else
	/*下面配置通道2为交叉输入的方式是可行的*/
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2; //因为ICInit函数只有1个，所以此参数指定通道
	TIM_ICInitStruct.TIM_ICFilter = 0xF; //配置输入捕获的滤波器，如果信号有毛刺噪声，可以增大滤波器参数，有效避免干扰
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling; //边沿检测极性选择，选择是上升沿触发还是下降沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI; //配置数据选择器，选择直连通道还是交叉通道
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
#endif
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void)
{
	//加1的目的是纠正正负1误差，实际不加1也可
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);  //1000000是标准频率fc
}

uint32_t IC_GetDuty(void)
{
	//加1的目的是纠正正负1误差，实际不加1也可
	return (float)(TIM_GetCapture2(TIM3) + 1) / (TIM_GetCapture1(TIM3) + 1) * 100 ;
}
```

```c
/*
配置输入捕获单元。
参数TIMx：选择定时器
参数TIM_ICInitStruct：包含各个配置的结构体
注意：输入捕获和输出比较都有4个通道，OCInit有4个通道，每一个通道独占一个函数，而ICInit是4个通道共用一个函数，参数结构体里会额外有一个参数，用来选择具体配置哪个通道。因为可能有交叉通道的配置，所以函数合在一起比较方便。
*/
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);

/*
和TIM_ICInit函数一样都是用于初始化输入捕获单元的。但TIM_ICInit只是单一地配置一个通道，而TIM_PWMIConfig可以快速配置两个通道。
*/
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);

/*
给输入捕获结构体赋一个初始值
*/
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);

/*
选择输入触发源TRGI，即从模式的触发源选择
*/
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);

/*
选择输出触发源TRGO，对应选择主模式输出的触发源
*/
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);

/*
选择从模式
*/
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);

/*分别单独配置通道1，2，3，4的分频器，此参数结构体也可以配置*/
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);

/*分别读取4个通道的CCR，和TIM_SetCompare1~4是对应的，读写的都是CCR寄存器。输出比较模式下，CCR是只写的，要用SetCompare写入；输入捕获模式下，CCR是只读的，要用GetCapture读出。*/
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);
```

