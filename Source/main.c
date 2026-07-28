#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

#include "custom_def.h"
#include "core_portme.h"

extern void portable_init(core_portable *p, int *argc, char *argv[]);
extern void portable_fini(core_portable *p);

/**
 * @brief  Main program.
 */
int main(void) {
  SysTick_Config(SystemCoreClock / configTICK_RATE_HZ);
	
  LedInit();

  User_Usart_Init(SERIAL_BAUDRATE);

  /* Output a message on Hyperterminal using printf function */
  printf("N32G457 Test \r");
	printf("CC: %s\n", COMPILER_NAME);		
	printf("%u Hz, %08X, CM:%d, FPU_USED:%d\n",
			SystemCoreClock, SCB->CPUID,
			__CORTEX_M, __FPU_USED);
	
  while (1) {
		printf("\n");
		printf("Flash cached enable\n");
		FLASH_iCacheCmd(FLASH_iCache_EN);		
		coremark_main();
		
    Led1Toogle();
    HAL_Delay(3000);
    Led2Toogle();
    HAL_Delay(3000);
    Led3Toogle();
    HAL_Delay(3000);
		
		printf("CC: %s\n", COMPILER_NAME);		
		printf("%u Hz, %08X, CM:%d, FPU_USED:%d\n",
				SystemCoreClock, SCB->CPUID,
				__CORTEX_M, __FPU_USED);
		printf("vector: %08X %08X\n", (uint32_t)(&portable_init), (uint32_t)(&portable_fini));
		printf("Flash cached test completed\n");

    HAL_Delay(3 * 1000);
		
		printf("\n");
		printf("Flash cached disable\n");
		FLASH_iCacheCmd(FLASH_iCache_DIS);
		coremark_main();
		
    Led1Toogle();
    HAL_Delay(3000);
    Led2Toogle();
    HAL_Delay(3000);
    Led3Toogle();
    HAL_Delay(3000);
		
		printf("CC: %s\n", COMPILER_NAME);		
		printf("%u Hz, %08X, CM:%d, FPU_USED:%d\n",
				SystemCoreClock, SCB->CPUID,
				__CORTEX_M, __FPU_USED);
		printf("vector: %08X %08X\n", (uint32_t)(&portable_init), (uint32_t)(&portable_fini));
		printf("Flash uncached test completed\n");
				
		
    HAL_Delay(3 * 1000);
  }
}
