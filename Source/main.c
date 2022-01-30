#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "simple_delay.h"

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

  while (1) {
    Led3Toogle();
    simple_delay_ms(300);
  }
}
