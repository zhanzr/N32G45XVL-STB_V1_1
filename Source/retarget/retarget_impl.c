#include "usart.h"

/* retarget the C library printf function to the USART */
int stdout_putchar(int ch) {
  USART_SendData(USART1, (uint8_t)ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
    ;

  return (ch);
}
