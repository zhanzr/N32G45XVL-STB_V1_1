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
int main_init(void) {
	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / __CLK_TCK)) {
		 /* Capture error */
		 while (1);
	}
	
  LedInit();

  User_Usart_Init();

//  while (1) {
//    Led3Toogle();
//    printf("Freq %u, ticks:%u\n\r", SystemCoreClock, g_ticks);

//    simple_delay_ms(300);
//  }
}
