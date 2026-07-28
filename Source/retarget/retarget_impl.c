#include <stdio.h>

#include "usart.h"

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* __ICCARM__ */

/* retarget the C library printf function to the USART */
int stdout_putchar(int ch) {
  USART_SendData(USART1, (uint8_t)ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
    ;

  return (ch);
}


#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT


/* retarget the C library printf function to the USART */
PUTCHAR_PROTOTYPE {
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
        ;

    return (ch);
}
