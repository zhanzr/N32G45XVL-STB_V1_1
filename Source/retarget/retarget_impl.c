#include "retarget_impl.h"

/* retarget the C library printf function to the USART */
int stdout_putchar(int ch) {
  USART_SendData(USART1, (uint8_t)ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
    ;

  return (ch);
}

/**
 * @brief  show some words(32bit) in hex format
 */
void DumpWords(const uint32_t *words, uint32_t len) {
  for (uint32_t i = 0; i < len; ++i) {
    printf("0x%08x, ", words[i]);
  }
  printf("\r\n");
}

/**
 * @brief  show some bytes(8bit) in hex format
 */
void DumpBytes(const uint8_t *bytes, uint32_t len) {
  for (uint32_t i = 0; i < len; ++i) {
    printf("%02x", bytes[i]);
  }
  printf("\r\n");
}
