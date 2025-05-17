#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>
#include "bsp.h"
//#include "user_flash.h"

#include "debug.h"
#include <string.h>
// 系统时钟相关
extern volatile uint32_t uwTick;
extern volatile uint8_t T1ms_flag;
extern volatile uint8_t T100ms_count;
extern volatile uint8_t T100ms_flag;



// 定时器配置
#define TIM1_CH1CVR_ADDRESS 0x40012C34

#define TEST_FLASH_ADDR 0x0800F100  // 选择一个合适的Flash地址


//测试脚
#define LED_PIN     GPIO_Pin_0
#define LED_PROT    GPIOD
#define LED_ON      (LED_PROT->BSHR = LED_PIN)
#define LED_OFF     (LED_PROT->BCR =  LED_PIN)
// 最小/最大宏
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))



typedef struct {
    uint8_t outputState;     // 输出状态(0:关闭 1:开启)     ==  
    uint16_t brightness;      // 亮度(0-100%)
    uint8_t cctLevel;
} Edata_t;
extern Edata_t edata;


extern volatile uint8_t T10ms_flag;
extern volatile uint32_t uwTick;
extern u8 rxbuf[30];

// 中断处理函数声明
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#endif