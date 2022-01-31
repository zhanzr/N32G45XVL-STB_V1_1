#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

#include "core_portme.h"

#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT

volatile uint32_t g_ticks;

/**
 * @brief  SysTick Init.
 * @param  NUM   Interrupt Time(us)
 */
void SysTick_Init(uint32_t NUM)
{
    /* SystemCoreClock / NUM */
    if (SysTick_Config(SystemCoreClock / NUM))
    {
        while (1)
            ;
    }
}

/**
 * @brief  SysTick_Stop_time.
 */
void SysTick_Stop_time(void)
{
    SysTick->CTRL &= SYSTICK_COUNTER_DIASBLE;
    /* Clear the SysTick Counter */
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
}

/**
 * @brief  Main program.
 */
int main_init(void) {
    /* Enable iCache */
//    FLASH_iCacheCmd(FLASH_iCache_EN);
	
	SysTick_Init(SYSTICK_1MS);

  LedInit();

  User_Usart_Init();

//  while (1) {
//    Led3Toogle();
//    printf("Freq %u, ticks:%u\n\r", SystemCoreClock, g_ticks);

//    simple_delay_ms(300);
//  }
}
