#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

volatile uint32_t g_ticks;

#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT

/**
 * @brief  Main program.
 */
int main(void) {
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000)) {
    /* Capture error */
    while (1)
      ;
  }

  LedInit();

  User_Usart_Init();

  /* Output a message on Hyperterminal using printf function */
  printf("\n\rUSART Printf Example: retarget the C library printf function to "
         "the USART\n\r");

  while (1) {
    Led3Toogle();
    printf("Freq %u ticks:%u\n\r", SystemCoreClock, g_ticks);

    simple_delay_ms(300);
  }
}
