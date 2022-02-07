#include "hard_algo.h"

extern void print_bytes(void *p, size_t length);
extern void print_hash(uint8_t *p);

/**
 * @brief  Example for how to get a randon number by ALGO lib
 */
void TestRand_Hard(void) {
  uint32_t buf[8];
  uint32_t seed[2] = {1, 2};

  log_info("\n");

  if (RNG_OK != GetPseudoRand_U32(buf, 8, seed)) {
    log_error("GetPseudoRand_U32 failed.\n");
  } else {
    log_info("Pseudo random with seed 1,2: ");
    DumpWords(buf, 8);
    log_info("\n");
  }
  seed[0] = 3;
  seed[1] = 4;
  if (RNG_OK != GetPseudoRand_U32(buf, 8, seed)) {
    log_error("GetPseudoRand_U32 failed.\n");
  } else {
    log_info("Pseudo random with seed 3,4: ");
    DumpWords(buf, 8);
    log_info("\n");
  }

  if (RNG_OK != GetTrueRand_U32(buf, 8)) {
    log_error("GetTrueRand_U32 failed.\n");
  } else {
    log_info("True random: ");
    DumpWords(buf, 8);
    log_info("\n");
  }
}

/**
 * @brief  Show how to calculate hash value by ALGO lib for a message
 */
void CalcHASH_Hard(const HASH_ALG *hashAlg, uint8_t *buf, uint32_t len,
                   uint8_t *result) {
  HASH_CTX ctx;

  ctx.hashAlg = hashAlg;
  ctx.sequence = HASH_SEQUENCE_FALSE;
  if (HASH_Init_OK != HASH_Init(&ctx)) {
    log_error("HASH_Init failed.\n");
    return;
  }
  if (HASH_Start_OK != HASH_Start(&ctx)) {
    log_error("HASH_Start failed.\n");
    return;
  }
  if (HASH_Update_OK != HASH_Update(&ctx, buf, len)) {
    log_error("HASH_Update failed.\n");
    return;
  }
  if (HASH_Complete_OK != HASH_Complete(&ctx, result)) {
    log_error("HASH_Complete failed.\n");
    return;
  }
}

/**
 * @brief  Show how to calculate SHA1 value by ALGO lib for a message
 */
void TestSHA1_Hard(uint8_t *buf, uint32_t len) {
  uint8_t result[20];

  log_info("\n");
  CalcHASH_Hard(HASH_ALG_SHA1, buf, len, result);
  log_info("SHA1 of message `%s` is: ", buf);
  DumpBytes(result, 20);
  log_info("\n");
}

void md5Binary_hard(uint8_t *buf, uint32_t len, uint8_t* result) {
  CalcHASH_Hard(HASH_ALG_MD5, buf, len, result);
}

void md5String_hard(uint8_t *buf, uint8_t* result) {
	md5Binary_hard(buf, strlen((char*)buf), result);
}

int test_hard_md5(char* input){
	uint8_t result[16];

	md5String_hard((uint8_t*)input, result);
	print_hash(result);
}

/**
 * @brief  Show how to calculate MD5 value by ALGO lib for a message
 */
void TestMD5_Hard(uint8_t *buf, uint32_t len) {
	printf("%s start\r\n\r\n", __func__);
	test_hard_md5("");
	test_hard_md5("a");
	test_hard_md5("abc");
	test_hard_md5("message digest");
	test_hard_md5("abcdefghijklmnopqrstuvwxyz");
	test_hard_md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	test_hard_md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
	printf("%s endof \r\n\r\n", __func__);
}

/**
 * @brief  Show how to calculate SHA224 value by ALGO lib for a message
 */
void TestSHA224_Hard(uint8_t *buf, uint32_t len) {
  uint8_t result[28];

  log_info("\n");
  CalcHASH_Hard(HASH_ALG_SHA224, buf, len, result);
  log_info("SHA224 of message `%s` is: ", buf);
  DumpBytes(result, 28);
  log_info("\n");
}

/**
 * @brief  Show how to calculate SHA256 value by ALGO lib for a message
 */
void TestSHA256_Hard(uint8_t *buf, uint32_t len) {
  uint8_t result[32];

  log_info("\n");
  CalcHASH_Hard(HASH_ALG_SHA256, buf, len, result);
  log_info("SHA256 of message `%s` is: ", buf);
  DumpBytes(result, 32);
  log_info("\n");
}

/**
 * @brief  Show how to encrypt a message by DES, then decrypt it and compare the
 * result.
 */
void TestDES_Hard(void) {
  DES_PARM DES_Parm;
#ifdef __IAR_ARM
  uint8_t key[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  uint8_t cipher[8];
  uint8_t plainOut[8];
#elif defined(__CC_ARM)
  __align(4) uint8_t key[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  __align(4)
      uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  __align(4) uint8_t cipher[8];
  __align(4) uint8_t plainOut[8];
#else
  _Alignas(4) uint8_t key[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  _Alignas(4)
      uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  _Alignas(4) uint8_t cipher[8];
  _Alignas(4) uint8_t plainOut[8];
#endif

  log_info("\n");

  DES_Parm.in = (uint32_t *)plain;
  DES_Parm.out = (uint32_t *)cipher;
  DES_Parm.key = (uint32_t *)key;
  DES_Parm.iv = NULL; // IV is not needed in ECB mode
  DES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
  DES_Parm.Mode = DES_ECB;
  DES_Parm.En_De = DES_ENC;
  DES_Parm.keyMode = DES_KEY;

  // encrypt data
  if (DES_Init_OK != DES_Init(&DES_Parm)) {
    log_error("DES_Init failed.\n");
    return;
  }
  if (DES_Crypto_OK != DES_Crypto(&DES_Parm)) {
    log_error("DES_Crypto failed\n");
    return;
  }

  log_info("DES ECB encrypt:\n");
  log_info("key = ");
  DumpBytes(key, sizeof(key));
  log_info("\n");
  log_info("plain = ");
  DumpBytes(plain, sizeof(plain));
  log_info("\n");
  log_info("cipher = ");
  DumpBytes(cipher, sizeof(cipher));
  log_info("\n");

  DES_Parm.in = (uint32_t *)cipher;
  DES_Parm.out = (uint32_t *)plainOut;
  DES_Parm.En_De = DES_DEC;

  // decrypt data
  if (DES_Init_OK != DES_Init(&DES_Parm)) {
    log_error("DES_Init failed.\n");
    return;
  }
  if (DES_Crypto_OK != DES_Crypto(&DES_Parm)) {
    log_error("DES_Crypto failed\n");
    return;
  }

  log_info("decrypt out = ");
  DumpBytes(plainOut, 8);
  log_info("\n");
  if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
    log_error("DES decrypt result do not equal plain data.\n");
    while (1)
      ;
  } else {
    log_info("DES test OK!\n");
  }
}

/**
 * @brief  Show how to encrypt a message by AES, then decrypt it and compare the
 * result.
 */
void TestAES_Hard(void) {
  AES_PARM AES_Parm;
#ifdef __IAR_ARM
  uint8_t key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  uint8_t plain[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                       0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
  uint8_t cipher[16];
  uint8_t plainOut[16];
#elif defined(__CC_ARM)
  __align(4)
      uint8_t key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  __align(4)
      uint8_t plain[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                           0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
  __align(4) uint8_t cipher[16];
  __align(4) uint8_t plainOut[16];
#else
  _Alignas(4)
      uint8_t key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  _Alignas(4)
      uint8_t plain[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                           0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
  _Alignas(4) uint8_t cipher[16];
  _Alignas(4) uint8_t plainOut[16];
#endif

  log_info("\n");

  AES_Parm.in = (uint32_t *)plain;
  AES_Parm.out = (uint32_t *)cipher;
  AES_Parm.key = (uint32_t *)key;
  AES_Parm.iv = NULL; // IV is not needed in ECB mode
  AES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
  AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
  AES_Parm.Mode = AES_ECB;
  AES_Parm.En_De = AES_ENC;

  // encrypt data
  if (AES_Init_OK != AES_Init(&AES_Parm)) {
    log_error("AES_Init failed.\n");
    return;
  }
  if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
    log_error("AES_Crypto failed\n");
    return;
  }

  log_info("AES ECB encrypt:\n");
  log_info("key = ");
  DumpBytes(key, sizeof(key));
  log_info("\n");
  log_info("plain = ");
  DumpBytes(plain, sizeof(plain));
  log_info("\n");
  log_info("cipher = ");
  DumpBytes(cipher, sizeof(cipher));
  log_info("\n");

  AES_Parm.in = (uint32_t *)cipher;
  AES_Parm.out = (uint32_t *)plainOut;
  AES_Parm.En_De = AES_DEC;

  // decrypt data
  if (AES_Init_OK != AES_Init(&AES_Parm)) {
    log_error("AES_Init failed.\n");
    return;
  }
  if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
    log_error("AES_Crypto failed\n");
    return;
  }

  log_info("decrypt out = ");
  DumpBytes(plainOut, sizeof(plainOut));
  log_info("\n");
  if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
    log_error("AES decrypt result do not equal plain data.\n");
    while (1)
      ;
  } else {
    log_info("AES test OK!\n");
  }
}
