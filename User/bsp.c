#include "bsp.h"
#include "debug.h"
#include "main.h"


/*********************************************************************
 * @fn      Delay_SoftUs
 *
 * @brief   软件实现的微秒延时(不依赖SysTick)
 *
 * @param   us - 微秒数
 *
 * @return  None
 */
void DelayUs(uint32_t us)
{
    // 48MHz下，每个循环约消耗6个时钟周期(实测调整)
    // 48/6 = 8，所以每微秒需要8个循环
    volatile uint32_t count = us *3;
    while (count--);
}



/* 毫秒延时 */
void DelayMs(uint32_t ms)
{
     while (ms--)
    {
        DelayUs(1000);
    }
}

/* LED初始化 */
void BSP_LEDInit(void) {
    // GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    // GPIO_InitStructure.GPIO_Pin = BSP_LED_PIN;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(BSP_LED_PORT, &GPIO_InitStructure);
    // BSP_LEDOff();
}

/* LED控制函数 */
void BSP_LEDOn(void) {
    // GPIO_ResetBits(BSP_LED_PORT, BSP_LED_PIN);
}

void BSP_LEDOff(void) {
    // GPIO_SetBits(BSP_LED_PORT, BSP_LED_PIN);
}

void BSP_LEDToggle(void) {
    // BSP_LED_PORT->ODR ^= BSP_LED_PIN;
}

/* 按键初始化 */
void BSP_KEYInit(void) {
    // GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    // GPIO_InitStructure.GPIO_Pin = BSP_KEY_PIN;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(BSP_KEY_PORT, &GPIO_InitStructure);
}

/* ADC初始化 */

/*********************************************************************
 * @fn      ADC_Function_Init
 *
 * @brief   Initializes ADC collection.
 *
 * @return  none
 */
void ADC_Function_Init(void)
{
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    //NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC|RCC_PB2Periph_GPIOD, ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);



    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_NbrOfChannel = 1;

    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Init(ADC1, &ADC_InitStructure);


    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_CyclesMode7);
    ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_2);
    ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_None);


    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_BufferCmd(ADC1, DISABLE);    //disable buffer
    
}

/*********************************************************************
 * @fn      Get_ADC_Val
 *
 * @brief   Returns ADCx conversion result data.
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *
 * @return  none
 */
u16 Get_ADC_Val(u8 ch)
{
    u16 val;
	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_CyclesMode7);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    val = ADC_GetConversionValue(ADC1);

    return val;
}
