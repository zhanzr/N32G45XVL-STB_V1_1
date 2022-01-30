#include "simple_delay.h"

void simple_delay_us(uint32_t x) {
  for (uint32_t i = 0; i < x; ++i) {
    for (uint32_t j = 0; j < 30; ++j) {
      __NOP();
    }
  }
}

void simple_delay_ms(uint32_t x) {
  for (uint32_t i = 0; i < x; ++i) {
    simple_delay_us(1000);
  }
}
