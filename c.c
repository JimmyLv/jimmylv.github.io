#define BSP_GLOBALS
#include "includes.h"

/**************************ª˙∆˜≥ı ºªØµƒœ‡πÿ¥˙¬Î*********************************/

static volatile ErrorStatus HSEStartUpStatus = SUCCESS;


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
EXTI_InitTypeDef EXTI_InitStructure;

s16 sADC1Value[11];


/*******************************************************************************
* Function Name  : RCC_Init
* Description    : æß’Ò≥ı ºªØ 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void RCC_Init(void)
{
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);

		RCC_PLLCmd(ENABLE);

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
		}

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}     
  }
}
/*******************************************************************************
* Function Name  : TIM5_IRQ_Config
* Description    : TIM5 µƒ÷–∂œ≈‰÷√
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQ_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel ;			     //—°‘Ò∂® ±∆˜6÷–∂œœﬂ
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		 //÷˜”≈œ»º∂Œ™0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			 //¥””≈œ»º∂Œ™0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // πƒ‹÷–∂œÕ®µ¿
  NVIC_Init(&NVIC_InitStructure);								 //”√“‘…œ≤Œ ˝≥ı ºªØ10-15∫≈œﬂ÷–∂œÕ®µ¿
}	
/*******************************************************************************
* Function Name  : Anticollision_Config
* Description    : ∫ÏÕ‚√‚≈ˆ◊≤≈‰÷√°£”√TIM8µƒPWMÕ®µ¿1 ∫Õ±»Ωœ ‰≥ˆ2-3.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Anticollision_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;  
	TIM_DeInit(TIM8);                              //∏¥Œª∂® ±∆˜…Ë÷√
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);    //TIM3 ∂Àø⁄≤ø∑÷÷ÿ”≥…‰

	TIM_TimeBaseStructure.TIM_Prescaler = 5000-1;                 //…Ë÷√∆µ¬   495hz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //œÚ…œº∆ ˝
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;//  0 - 100 ’ºø’±»
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);            

	TIM_ITConfig(TIM8,TIM_IT_CC2,ENABLE);              //ø™∆Ù ‰≥ˆ±»ΩœÕ®µ¿2 and 3
  TIM_ITConfig(TIM8,TIM_IT_CC3,ENABLE);
	// Channel 1, 2,3 and 4 Configuration in PWM mode
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;           
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);               	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);		// √‚≈ˆ∑¢…‰
	
	TIM_OC4Init(TIM8,&TIM_OCInitStructure);               	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);		// ±ﬂÀ¢µÁª˙PWMøÿ÷∆
	
	TIM_SetCompare1(TIM8,15);
	TIM_SetCompare2(TIM8,20);
  TIM_SetCompare3(TIM8,80);
  
  TIM_CtrlPWMOutputs(TIM8, ENABLE);//pwm ∏ﬂº∂∂® ±∆˜1∫Õ8”√
	TIM_ARRPreloadConfig(TIM8, ENABLE);  //ø™∆Ù◊‘∂Ø÷ÿ‘ÿ
	TIM_Cmd(TIM8,ENABLE);                //ø™∆Ù∂® ±∆˜
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//void Anticollision_Config(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;  
//	TIM_DeInit(TIM8);                              //∏¥Œª∂® ±∆˜…Ë÷√
//	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);    //TIM3 ∂Àø⁄≤ø∑÷÷ÿ”≥…‰

//	TIM_TimeBaseStructure.TIM_Prescaler =1454-1;                 //…Ë÷√∆µ¬   495hz
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //œÚ…œº∆ ˝
//	TIM_TimeBaseStructure.TIM_Period = 100 - 1;//  0 - 100 ’ºø’±»
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
//  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

//  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);            

//	TIM_ITConfig(TIM8,TIM_IT_CC2,ENABLE);              //ø™∆Ù ‰≥ˆ±»ΩœÕ®µ¿2 and 3
//  TIM_ITConfig(TIM8,TIM_IT_CC3,ENABLE);
//	// Channel 1, 2,3 and 4 Configuration in PWM mode
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;           
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
//  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//	
//	TIM_OC1Init(TIM8,&TIM_OCInitStructure);               	
//	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);		// √‚≈ˆ∑¢…‰
//	
//	TIM_OC4Init(TIM8,&TIM_OCInitStructure);               	
//	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);		// ±ﬂÀ¢µÁª˙PWMøÿ÷∆
//	
//	TIM_SetCompare1(TIM8,13);
////	TIM_SetCompare2(TIM8,14);
//	TIM_SetCompare2(TIM8,26);
//  TIM_SetCompare3(TIM8,90);
//  
//  TIM_CtrlPWMOutputs(TIM8, ENABLE);//pwm ∏ﬂº∂∂® ±∆˜1∫Õ8”√
//	TIM_ARRPreloadConfig(TIM8, ENABLE);  //ø™∆Ù◊‘∂Ø÷ÿ‘ÿ
//	TIM_Cmd(TIM8,ENABLE);                //ø™∆Ù∂® ±∆˜
//	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQChannel;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
/*******************************************************************************
* Function Name  : BSP_Init
* Description    : ª˙∆˜ø™ª˙∫Ûµƒ”≤º˛≥ı ºªØ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_Init(void)
{
	RCC_Init();   //≥ı ºªØæß’Ò
  //∏˘æ› π”√µƒ“˝Ω≈–ﬁ∏ƒ	“˝Ω≈ ±÷”…Ë÷√
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD | 
						   RCC_APB2Periph_AFIO|	RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM8 | RCC_APB2Periph_ADC1 , ENABLE);
  	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5|
						   RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7,ENABLE);
    
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);

	/* Enable PWR and BKP clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	
	GPIO_Configuration();      //GPIOø⁄≥ı ºªØ
	Motor_Roll(0,DISABLE);     //œ»πÿ±’Œ¸≥æπˆÀ¢∫Õ±ﬂÀ¢
	Motor_Side(0,DISABLE);

  SysTick_Config();        // ±÷”≈‰÷√
	Interrupt_Config();      // ÷–∂œ≈‰÷√≥ı ºªØ 
	//custom timer initiation
	Timer_Deinit();  //∏¥Œª»´≤ø∂® ±∆˜≈‰÷√
	IRSendTimerSet();//TIM8 for IR-nocode send
	TIM5_IRQ_Config();     //TIM5 µƒ÷–∂œ≈‰÷√
	SelfTim6InterruptInit();//remote signal recognization  
	SelfTim7InterruptInit();//speed calculation
	IRSendTimerSet();      //∫ÏÕ‚38K∂® ±∆˜≥ı ºªØ

	//IR signal interrupt initiation
	Interrupt_IR_Config();   //Õ‚≤ø÷–∂œµƒ≈‰÷√

	/* Motor control initialization */
	Motor_Move_Init();       //––◊ﬂµÁª˙µƒPWM≈‰÷√
 // Motor_Init();            //∆‰À¸¬Ì¥Ô«˝∂Ø≥ı ºªØ  ”√TIM1 µƒPWMÕ®µ¿  1.2.3.4               
	EncoderInit();           //––◊ﬂµÁª˙µƒÀŸ∂»º∆À„≈‰÷√
	/* ADC and DMA initiation */
	ADCDMAInit();
	/* usart3 configuration for receive and transmit with display panel */
	USART3ForDispConfig(); 
	Anticollision_Config();   
}
/*******************************************************************************
* Function Name  : SysTick_Config
* Description    :  ±÷”≈‰÷√
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void SysTick_Config(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    u32  cnts;

    RCC_GetClocksFreq(&rcc_clocks);
    
    cnts = (u32)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

    SysTick_SetReload(cnts);
	/* Configure HCLK clock as SysTick clock source */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	/*º∆ ˝∆˜*/
    SysTick_CounterCmd(SysTick_Counter_Enable);
	 /* Enable the SysTick Interrupt */
    SysTick_ITConfig(ENABLE);
}
/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : GPIOø⁄≥ı ºªØ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	 // Õ∑≈JTAGΩ≈◊˜Œ™∆’Õ®IOø⁄  JTAG Ω˚”√£¨SWDø™∆Ù
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//GPIOA
	/* Configure GPIOA as output push-pull */
			                           //µÁ≥ÿ≥‰µÁøÿ÷∆ 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* GPIOA Configuration: PWM  */   //––◊ﬂ¥Û¬÷PWMøÿ÷∆
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* GPIOA Configuration: in_floating  */
													   	//◊Û±‡¬Î∆˜∑¥¿°             
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	//GPIOB
	/* Configure GPIOB as output push-pull */
	                               //∑‰√˘∆˜IO  //3.3V øÿ÷∆  //WIFI¥Æø⁄Œ¥”√…Ë÷√Œ™ ‰≥ˆ   //∏∫¿Î◊”øÿ÷∆
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_2  | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

                                //SDOCK     ◊Û≈ˆ◊≤ºÏ≤‚    ”“≈ˆ◊≤ºÏ≤‚


	/* GPIOB Configuration: PWM */   //—ÿ±ﬂPWM  //œ¬ ”PWM
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
																//“£øÿΩ” ’«∞ //≥‰µÁ◊¥Ã¨ºÏ≤‚ //∫ÏÕ‚Ω” ’∫Û  //∫ÏÕ‚Ω” ’”“  //◊Û≈ˆ◊≤ºÏ≤‚ //”“≈ˆ◊≤ºÏ≤‚  //“£øÿΩ” ’◊Û  //ÕÚœÚ¬÷ºÏ≤‚    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	//GPIOC
	/* Configure GPIOC as output push-pull */
                                   //Œ¸≥æPWM     //ª“≥æ∑¢…‰    //UVµ∆     
	GPIO_InitStructure.GPIO_Pin =    GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_12  ;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	                             //«∞œ¬ ”      //”“œ¬ ”     //Œ¸≥æ◊™ÀŸ     //¥≈ÃıªÙ∂˚    //◊Ûœ¬ ”  //≥‰¬˙µÁ◊¥Ã¨ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

					//∫ÏÕ‚“£øÿ∑¢…‰PWM    //√‚≈ˆ38K      //±ﬂÀ¢PWM	                           
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6   | GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);  
                             	
	//GPIOD
	/* Configure GPIOD */
  //◊Û±‡¬Î∆˜∑¥¿°
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			/*…œ¿≠ ‰»Î*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : Interrupt_Config
* Description    : ÷–∂œ≈‰÷√≥ı ºªØ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Interrupt_Config(void)
{
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC_PriorityGroup_2 ◊Ó∏ﬂ2Œª”√”⁄÷∏∂®«¿’º Ω”≈œ»º∂£¨◊ÓµÕ2Œª”√”⁄÷∏∂®œÏ”¶”≈œ»º∂
    NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,0,0);
}
/*******************************************************************************
* Function Name  : ADCInitiation
* Description    : ADC µƒDMA≥ı ºªØ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADCDMAInit(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
   
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE + 0x4C;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)sADC1Value;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 11;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);

//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//							   							◊Û√‚≈ˆ		µÁ≥ÿµÁ—π	  ”“√‚≈ˆ   ”“¥Û¬÷		  ◊Û¥Û¬÷	    ”“±ﬂÀ¢	   ª“≥æ∏–”¶		«∞√‚≈ˆ							
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//							        	         ◊Û±ﬂÀ¢	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
																	//Œ¸≥æµÁª˙  //µÁ≥ÿŒ¬∂»
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 11;     //…Ë÷√◊™ªª–Ú¡–≥§∂»Œ™11
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//≥£πÊ◊™ªª–Ú¡–1£∫adc1 Õ®µ¿1£®µÁ≥ÿµÁ—πºÏ≤‚£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
	//≥£πÊ◊™ªª–Ú¡–2£∫adc1 Õ®µ¿3£®”“––◊ﬂµÁª˙_ŒÔ¿Ì◊Û£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_1Cycles5);	
	//≥£πÊ◊™ªª–Ú¡–3£∫adc1 Õ®µ¿4£®◊Û––◊ﬂµÁª˙_ŒÔ¿Ì”“£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_1Cycles5);
	//≥£πÊ◊™ªª–Ú¡–4£∫adc1 Õ®µ¿6£®ª“≥æºÏ≤‚£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 4, ADC_SampleTime_1Cycles5);	
	//≥£πÊ◊™ªª–Ú¡–5£∫adc1 Õ®µ¿5£®”“±ﬂÀ¢µÁª˙£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_1Cycles5);	
	//≥£πÊ◊™ªª–Ú¡–6£∫adc1 Õ®µ¿9£®◊Û±ﬂÀ¢µÁª˙£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 6, ADC_SampleTime_1Cycles5);
	//≥£πÊ◊™ªª–Ú¡–7£∫adc1 Õ®µ¿15£®µÁ≥ÿŒ¬∂»£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 7, ADC_SampleTime_1Cycles5);
	//≥£πÊ◊™ªª–Ú8£∫adc1 Õ®µ¿12£®Œ¸≥æµÁª˙£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 8, ADC_SampleTime_1Cycles5);
	//≥£πÊ◊™ªª–Ú¡–9£∫adc1 Õ®µ¿0£®◊Û√‚≈ˆ£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 9, ADC_SampleTime_1Cycles5);	
	//≥£πÊ◊™ªª–Ú¡–10£∫adc1 Õ®µ¿2£®”“√‚≈ˆ£©  ≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 10, ADC_SampleTime_1Cycles5);	
	//≥£πÊ◊™ªª–Ú¡–11£∫adc1 Õ®µ¿7£®«∞√‚≈ˆ£©£¨≤…—˘ ±º‰>2.2us,(239cycles)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 11, ADC_SampleTime_1Cycles5);

	 
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
}

/*******************************************************************************
* Function Name  : USART3ForDispConfig
* Description    : ¥Æø⁄œ‘ æ√Ê∞Âµƒ≥ı ºªØ≥Ã–Ú
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3ForDispConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable USART3 and GPIOC clock */
//	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);    //UART3 ∂Àø⁄≤ø∑÷÷ÿ”≥…‰
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 


	/* Configure USART4 Tx (PC.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = DISP_TXD_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DISP_USART4_PIN_AREA, &GPIO_InitStructure);

	/* Configure USART4 Rx (PC.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = DISP_RXD_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DISP_USART4_PIN_AREA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQChannel;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
	NVIC_Init(&NVIC_InitStructure);  

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	/* Enable USART3 */
	USART_Cmd(UART4, ENABLE);
}
/*******************************************************************************
* Function Name  : Interrupt_IR_Config
* Description    : ÷–∂œœ‡πÿ≈‰÷√
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Interrupt_IR_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  	/* Enable the EXTI0-9 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//«¿’º”≈œ»º∂
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//œÏ”¶”≈œ»º∂
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

 	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
 	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);
  	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//«¿’º”≈œ»º∂
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//œÏ”¶”≈œ»º∂
	NVIC_Init(&NVIC_InitStructure);								 
 	/* Connect Interrupt EXTI Line to GPIO Pin */


	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);	  //dock
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);  //usart rx display pannel
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);   //top
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);   //◊Û“£øÿΩ” ’Õ∑
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);   //∫Û“£øÿΩ” ’Õ∑
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);  //”““£øÿΩ” ’Õ∑
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);   //WIFI ¥Æø⁄Ω” ’÷–∂œ


 	EXTI_InitStructure.EXTI_Line =  EXTI_Line0 | EXTI_Line5 | EXTI_Line10 | EXTI_Line11 | EXTI_Line13 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
 	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;             //DOCK ÷–∂œ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	




	/* Configure EXTI Line17(RTC Alarm) to generate an interrupt on rising edge */
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);  

	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
* Function Name  : Motor_Move_Init
* Description    : ––◊ﬂµÁª˙«˝∂Ø≥ı ºªØ  ”√TIM2 µƒPWMÕ®µ¿  1.2.4
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Motor_Move_Init(void)
{ 
	// Time Base configuration 10KHz
	TIM_DeInit(MoveTime);
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;//0xFFF ;     
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

	TIM_TimeBaseInit(MoveTime,&TIM_TimeBaseStructure);

	// Channel 1, 2,3 and 4 Configuration in PWM mode
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	
	TIM_OC1Init(MoveTime,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(MoveTime, TIM_OCPreload_Enable);      // A4954 PWM4 ¬∑

	TIM_OC2Init(MoveTime,&TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(MoveTime, TIM_OCPreload_Enable);
	
	TIM_OC3Init(MoveTime,&TIM_OCInitStructure);	
	TIM_OC3PreloadConfig(MoveTime, TIM_OCPreload_Enable);

	TIM_OC4Init(MoveTime,&TIM_OCInitStructure);	                
	TIM_OC4PreloadConfig(MoveTime, TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(MoveTime, ENABLE);//pwm ∏ﬂº∂∂® ±∆˜1∫Õ8”√
}
/*******************************************************************************
* Function Name  : Encoder Initiation
* Description    : initiate tim2 for feedback of left wheel 
				   and tim3 for feedback of right wheel
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void EncoderInit(void)                                        //”√TIM2∫ÕTIM3µƒETR≤∂ªÒÕ®µ¿  ∑÷± «PA15 ∫Õ PD2
{
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);    //TIM2 ÕÍ»´÷ÿ”≥…‰ ∞—ETRΩ≈∏ƒ≥…PA15
	TIM_DeInit(ENCODER_TIMER_LEFT);
	TIM_DeInit(ENCODER_TIMER_RIGHT);
	TIM_TimeBaseInit(ENCODER_TIMER_LEFT, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period = 0xffff;                   //  µÁª˙◊™“ª»¶π‚µÁ±‡¬Î∆˜∑¢ÀÕ48∏ˆ¬ˆ≥Â
  TIM_TimeBaseStructure.TIM_Prescaler =0;	                     //…Ë÷√‘§∑÷∆µ£∫
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	     //…Ë÷√ ±÷”∑÷∆µœµ ˝£∫≤ª∑÷∆µ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //œÚ…œº∆ ˝ƒ£ Ω
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*≥ı ºªØTIM2∂® ±∆˜ */
	TIM_ETRClockMode2Config(ENCODER_TIMER_LEFT,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
  TIM_TimeBaseInit(ENCODER_TIMER_LEFT, &TIM_TimeBaseStructure);
	TIM_SetCounter(ENCODER_TIMER_LEFT,0);     
	TIM_ITConfig(ENCODER_TIMER_LEFT,TIM_IT_Update,ENABLE );              
	TIM_Cmd(ENCODER_TIMER_LEFT,ENABLE);
	
	TIM_TimeBaseInit(ENCODER_TIMER_RIGHT, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;                 //  µÁª˙◊™“ª»¶π‚µÁ±‡¬Î∆˜∑¢ÀÕ32∏ˆ¬ˆ≥Â
  TIM_TimeBaseStructure.TIM_Prescaler =0;	                //…Ë÷√‘§∑÷∆µ£∫
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//…Ë÷√ ±÷”∑÷∆µœµ ˝£∫≤ª∑÷∆µ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //œÚ…œº∆ ˝ƒ£ Ω
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*≥ı ºªØTIM3∂® ±∆˜ */
	TIM_ETRClockMode2Config(ENCODER_TIMER_RIGHT,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
  TIM_TimeBaseInit(ENCODER_TIMER_RIGHT, &TIM_TimeBaseStructure);
	TIM_SetCounter(ENCODER_TIMER_RIGHT,0); 
	
	ClearSpeedBuffer();
	TIM_ITConfig(ENCODER_TIMER_RIGHT, TIM_IT_Update, ENABLE);	
	TIM_Cmd(ENCODER_TIMER_RIGHT,ENABLE);
}
/*******************************************************************************
* Function Name  : Timer_Deinit
* Description    : ∏¥Œª∂® ±∆˜≈‰÷√
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer_Deinit(void)
{
	TIM_DeInit(TIM1);
	TIM_DeInit(TIM2);
	TIM_DeInit(TIM3);
	TIM_DeInit(TIM4);
	TIM_DeInit(TIM5);
	TIM_DeInit(TIM6);
	TIM_DeInit(TIM8);
}
/*******************************************************************************
* Function Name  : SelfTim7InterruptInit
* Description    : tim7 configuration for speed calculation, time cycle is 10ms, 
				   frequency 100Hz   ÀŸ∂»º∆À„∂® ±∆˜ 10ms º∆À„“ª¥Œ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SelfTim7InterruptInit(void)   //∂® ±∆˜7≈‰÷√£¨”√”⁄µÁª˙ÀŸ∂»º∆À„
{
	/*interrupt initiation 	   */
	NVIC_InitTypeDef NVIC_InitStructure;
	//chose interrupt group
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//enable SelfTimer interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQChannel;
	//«¿’º Ω÷–∂œ”≈œ»º∂
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//œÏ”¶ Ω÷–∂œ”≈œ»º∂
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	// πƒ‹÷–∂œ
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	TIM_DeInit(TIM7);

	//≤…”√ƒ⁄≤ø ±÷”∏¯SelfTimerÃ·π© ±÷”‘¥
	TIM_InternalClockConfig(TIM7);

	/* Time base configuration 	   */
  	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;//
  	TIM_TimeBaseStructure.TIM_Prescaler = 72 -1;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	//«Â≥˝“Á≥ˆ÷–∂œ±Í÷æ
	TIM_ClearFlag(TIM7, 0xFFFF);

	//Ω˚÷πARR‘§◊∞‘ÿª∫≥Â∆˜
	TIM_ARRPreloadConfig(TIM7, ENABLE);

	/* TIM IT enable */
  	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM7, ENABLE);	

//	SelfTimer->DIER |= 0x40;				 	
}
/*******************************************************************************
* Function Name  : SelfTim6InterruptInit
* Description    : tim6 configuration for remote signal recognization, time cycle is 1us, 
				   frequency 1 MHz
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SelfTim6InterruptInit(void)       //∂® ±∆˜6≈‰÷√£¨”√”⁄“£øÿΩ‚¬Î
{ 
	/*interrupt initiation 	   */
	NVIC_InitTypeDef NVIC_InitStructure;
	//chose interrupt group
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//enable SelfTimer interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQChannel;
	//«¿’º Ω÷–∂œ”≈œ»º∂
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//œÏ”¶ Ω÷–∂œ”≈œ»º∂
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	// πƒ‹÷–∂œ
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	TIM_DeInit(TIM6);

	//≤…”√ƒ⁄≤ø ±÷”∏¯SelfTimerÃ·π© ±÷”‘¥
	TIM_InternalClockConfig(TIM6);

	/* Time base configuration 	   */
  	TIM_TimeBaseStructure.TIM_Period = 0xffff;
  	TIM_TimeBaseStructure.TIM_Prescaler = 720 -1;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	//«Â≥˝“Á≥ˆ÷–∂œ±Í÷æ
	TIM_ClearFlag(TIM6, 0xFFFF);

	//Ω˚÷πARR‘§◊∞‘ÿª∫≥Â∆˜
	TIM_ARRPreloadConfig(TIM6, ENABLE);

	/* TIM IT enable */
  	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM6, ENABLE);	

//	SelfTimer->DIER |= 0x40;				 	
}
/*******************************************************************************
* Function Name  : IRSendTimerSet
* Description    : 38K∫ÏÕ‚≥ı ºªØ   TIM8µƒÕ®µ¿ 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IRSendTimerSet(void)
{
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1899;//0xFFF  37.9k;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

	TIM_TimeBaseInit(IrTime,&TIM_TimeBaseStructure);

	// Channel 1, 2,3 and 4 Configuration in PWM mode
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC3Init(IrTime,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(IrTime, TIM_OCPreload_Enable);		// —ÿ±ﬂ∑¢…‰
	TIM_OC4Init(IrTime,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(IrTime, TIM_OCPreload_Enable);		// œ¬ ”∑¢…‰
	IrTime->CCR3 = (IrTime->ARR + 1) * 33 / 100;
	IrTime->CCR4 = (IrTime->ARR + 1) * 33 / 100;
}
/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures RTC clock source and prescaler.  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration(void)
{
    INT32U iTempDelay;
    u32 PrescalerValue;
    FlagStatus fStatus;
	/* RTC clock source configuration ------------------------------------------*/
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	BKP_DeInit();
	/* Enable the LSE OSC */
	RCC_LSEConfig(RCC_LSE_ON);
    iTempDelay = OSTimeGet();
	/* Wait till LSE is ready */
	do{   
        fStatus = RCC_GetFlagStatus(RCC_FLAG_LSERDY);
        OSTimeDly(1);
	}while(fStatus == RESET && (OSTimeGet() - iTempDelay) < 1000);
//	fStatus = RESET;
    if(fStatus == RESET){
//    	RCC_LSEConfig(RCC_LSE_OFF);
        RCC_LSICmd(ENABLE);
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        PrescalerValue = 40000;
         bIsLSE = FALSE;
    }else{
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        PrescalerValue = 32767;
         bIsLSE = TRUE;
    }
	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* RTC configuration -------------------------------------------------------*/
	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();

	/* Set the RTC time base to 1s */
	RTC_SetPrescaler(PrescalerValue);  
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Alarm interrupt */
	RTC_ITConfig(RTC_IT_ALR, ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}
