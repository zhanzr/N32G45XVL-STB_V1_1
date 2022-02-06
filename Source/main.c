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
 * @brief  Main program.
 */
void main_init(void) {
    /* Switch iCache , it is default Enabled*/
//    FLASH_iCacheCmd(FLASH_iCache_EN);
//    FLASH_iCacheCmd(FLASH_iCache_DIS);
	
//	SysTick_Init(SYSTICK_1MS);

  LedInit();

  User_Usart_Init();

//  while (1) {
//    Led3Toogle();
//    printf("Freq %u, ticks:%u\n\r", SystemCoreClock, g_ticks);

//    simple_delay_ms(300);
//  }
}
