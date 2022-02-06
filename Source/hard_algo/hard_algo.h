#ifndef __HARD_ALGO_H__
#define __HARD_ALGO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "n32g45x_aes.h"
#include "n32g45x_des.h"
#include "n32g45x_hash.h"
#include "n32g45x_rng.h"

#include "retarget_impl.h"

void TestRand_Hard(void);
void CalcHASH_Hard(const HASH_ALG *hashAlg, uint8_t *buf, uint32_t len,
                   uint8_t *result);
void TestSHA1_Hard(uint8_t *buf, uint32_t len);
void TestMD5_Hard(uint8_t *buf, uint32_t len);
void TestSHA224_Hard(uint8_t *buf, uint32_t len);
void TestSHA256_Hard(uint8_t *buf, uint32_t len);
void TestDES_Hard(void);
void TestAES_Hard(void);

#ifdef __cplusplus
}
#endif

#endif /* __HARD_ALGO_H__ */
