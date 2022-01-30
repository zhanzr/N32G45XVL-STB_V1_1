#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

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
  LedInit();

  User_Usart_Init();

  /* Output a message on Hyperterminal using printf function */
  printf("\n\rUSART Printf Example: retarget the C library printf function to "
         "the USART\n\r");

  while (1) {
    Led3Toogle();
    printf("Freq %u\n\r", SystemCoreClock);

    simple_delay_ms(300);
  }
}
