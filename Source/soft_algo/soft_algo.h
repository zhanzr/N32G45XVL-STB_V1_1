#ifndef __SOFT_ALGO_H__
#define __SOFT_ALGO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retarget_impl.h"

void TestRand_Soft(void);
void TestSHA1_Soft(uint8_t *buf, uint32_t len);
void TestMD5_Soft(void);
void TestSHA224_Soft(uint8_t *buf, uint32_t len);
void TestSHA256_Soft(uint8_t *buf, uint32_t len);
void TestDES_Soft(void);
void TestAES_Soft(void);

#ifdef __cplusplus
}
#endif

#endif /* __SOFT_ALGO_H__ */
