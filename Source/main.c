#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

extern volatile uint32_t g_ticks;

#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE* f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
        ;

    return (ch);
}


/**
 * @brief  Main program.
 */
int main(void) {
  SysTick_Config(SystemCoreClock / 1000);
	
  LedInit();

  User_Usart_Init();

  /* Output a message on Hyperterminal using printf function */
  printf("N32G457 Test \r");

  while (1) {
    Led1Toogle();
    printf("Freq %u %u\r", SystemCoreClock, g_ticks);

    simple_delay_ms(1000);
    Led2Toogle();
    simple_delay_ms(1000);
    Led3Toogle();
    simple_delay_ms(1000);
  }
}
