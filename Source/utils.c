#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "custom_def.h"
#include "utils.h"

#include "n32g45x.h"

volatile uint32_t g_ticks;

uint32_t HAL_GetTick(void) { return g_ticks; }

//#pragma clang section text="RAM_CODE"
void HAL_Delay(uint32_t t) {
  uint32_t d = t + HAL_GetTick();
  while (d > HAL_GetTick()) {
    __NOP();
  }
}
