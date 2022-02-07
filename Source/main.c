#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "hard_algo.h"
#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "soft_algo.h"
#include "usart.h"

#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT

volatile uint32_t g_ticks;

#define HASH_TEST_MSG "Hello!"

/**
 * @brief  SysTick Init.
 * @param  NUM   Interrupt Time(us)
 */
void SysTick_Init(uint32_t NUM) {
  /* SystemCoreClock / NUM */
  if (SysTick_Config(SystemCoreClock / NUM)) {
    while (1)
      ;
  }
}

/**
 * @brief  SysTick_Stop_time.
 */
void SysTick_Stop_time(void) {
  SysTick->CTRL &= SYSTICK_COUNTER_DIASBLE;
  /* Clear the SysTick Counter */
  SysTick->VAL = SYSTICK_COUNTER_CLEAR;
}

/**
 * @brief  Main program.
 */
int main(void) {
  /* Enable iCache */
  //    FLASH_iCacheCmd(FLASH_iCache_EN);

  SysTick_Init(SYSTICK_1MS);

  LedInit();

  User_Usart_Init();

  // Hardware Engine
  TestRand_Hard();

  TestMD5_Hard((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));
  TestSHA1_Hard((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));
  TestSHA224_Hard((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));
  TestSHA256_Hard((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));

  TestDES_Hard();
  TestAES_Hard();

  // Software Engine
  TestRand_Soft();

  TestMD5_Soft();
  TestSHA1_Soft((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));
  TestSHA224_Soft((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));
  TestSHA256_Soft((uint8_t *)HASH_TEST_MSG, strlen(HASH_TEST_MSG));

  TestDES_Soft();
  TestAES_Soft();

  while (1) {
    Led3Toogle();
    printf("Freq %u, ticks:%u\n\r", SystemCoreClock, g_ticks);

    simple_delay_ms(20000);
  }
}
