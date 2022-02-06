#ifndef __RETARGET_IMPL_H__
#define __RETARGET_IMPL_H__

#include <stdio.h>

#include "usart.h"

#ifndef __CLK_TCK
#define __CLK_TCK 1000
#endif

#define SYSTICK_1MS ((uint32_t)__CLK_TCK)
#define SYSTICK_COUNTER_DIASBLE ((uint32_t)0xFFFFFFFE)
#define SYSTICK_COUNTER_ENABLE ((uint32_t)0x00000001)
#define SYSTICK_COUNTER_CLEAR ((uint32_t)0x00000000)

#define log_error printf
#define log_info printf

void DumpBytes(const uint8_t *bytes, uint32_t len);
void DumpWords(const uint32_t *words, uint32_t len);

#endif /* __RETARGET_IMPL_H__ */
