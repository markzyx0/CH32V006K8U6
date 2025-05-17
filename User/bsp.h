#ifndef __BSP_H
#define __BSP_H

#include "ch32v00x.h"

/* LED配置 */
#define BSP_LED_PIN     GPIO_Pin_0
#define BSP_LED_PORT    GPIOD

/* 按键配置 */ 
#define BSP_KEY_PIN     GPIO_Pin_1
#define BSP_KEY_PORT    GPIOC

/* ADC配置 */
#define BSP_ADC_CHANNEL ADC_Channel_0

/* 延时函数 */
void BSP_DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);

/* LED控制 */
void BSP_LEDInit(void);
void BSP_LEDOn(void);
void BSP_LEDOff(void);
void BSP_LEDToggle(void);

/* 按键处理 */
void BSP_KEYInit(void);
void SensorOutputControl(uint8_t state,uint8_t type);

/* ADC处理 */
extern   u16 Get_ADC_Val(u8 ch);
void ADC_Function_Init(void);


/* TIM处理 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp);
//void TIM2_INT_Init( u16 arr, u16 psc);
void TIM2_PWMOut_Init(u16 arr, u16 psc, u16 ccp);
#endif