#include "n32g45x.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "led.h"
#include "retarget_impl.h"
#include "simple_delay.h"
#include "usart.h"

#include "n32g45x_rng.h"
#include "n32g45x_hash.h"
#include "n32g45x_des.h"
#include "n32g45x_aes.h"

#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif // USE_FULL_ASSERT

/**
 * @brief  show some words(32bit) in hex format
 */
void DumpWords(const uint32_t* words, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        printf("0x%08x, ", words[i]);
    }
		printf("\r\n");
}

/**
 * @brief  show some bytes(8bit) in hex format
 */
void DumpBytes(const uint8_t* bytes, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        printf("%02x", bytes[i]);
    }
		printf("\r\n");		
}

volatile uint32_t g_ticks;

/**
 * @brief  SysTick Init.
 * @param  NUM   Interrupt Time(us)
 */
void SysTick_Init(uint32_t NUM)
{
    /* SystemCoreClock / NUM */
    if (SysTick_Config(SystemCoreClock / NUM))
    {
        while (1)
            ;
    }
}

/**
 * @brief  SysTick_Stop_time.
 */
void SysTick_Stop_time(void)
{
    SysTick->CTRL &= SYSTICK_COUNTER_DIASBLE;
    /* Clear the SysTick Counter */
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
}


/**
 * @brief  Example for how to get a randon number by ALGO lib
 */
void TestRand(void)
{
    uint32_t buf[8];
    uint32_t seed[2] = {1, 2};
    
    log_info("\n");
    
    if (RNG_OK != GetPseudoRand_U32(buf, 8, seed))
    {
        log_error("GetPseudoRand_U32 failed.\n");
    }
    else
    {
        log_info("Pseudo random with seed 1,2: ");
        DumpWords(buf, 8);
        log_info("\n");
    }
    seed[0] = 3;
    seed[1] = 4;
    if (RNG_OK != GetPseudoRand_U32(buf, 8, seed))
    {
        log_error("GetPseudoRand_U32 failed.\n");
    }
    else
    {
        log_info("Pseudo random with seed 3,4: ");
        DumpWords(buf, 8);
        log_info("\n");
    }

    if (RNG_OK != GetTrueRand_U32(buf, 8))
    {
        log_error("GetTrueRand_U32 failed.\n");
    }
    else
    {
        log_info("True random: ");
        DumpWords(buf, 8);
        log_info("\n");
    }
}

#define HASH_TEST_MSG "Hello!"

/**
 * @brief  Show how to calculate hash value by ALGO lib for a message 
 */
void CalcHASH(const HASH_ALG* hashAlg, char* msg, uint8_t* result)
{
    HASH_CTX ctx;
    
    ctx.hashAlg  = hashAlg;
    ctx.sequence = HASH_SEQUENCE_FALSE;
    if (HASH_Init_OK != HASH_Init(&ctx))
    {
        log_error("HASH_Init failed.\n");
        return;
    }
    if (HASH_Start_OK != HASH_Start(&ctx))
    {
        log_error("HASH_Start failed.\n");
        return;
    }
    if (HASH_Update_OK != HASH_Update(&ctx, (uint8_t*)msg, strlen(msg)))
    {
        log_error("HASH_Update failed.\n");
        return;
    }
    if (HASH_Complete_OK != HASH_Complete(&ctx, result))
    {
        log_error("HASH_Complete failed.\n");
        return;
    }
}

/**
 * @brief  Show how to calculate SHA1 value by ALGO lib for a message 
 */
void TestSHA1()
{
    uint8_t result[20];
    
    log_info("\n");
    CalcHASH(HASH_ALG_SHA1, HASH_TEST_MSG, result);
    log_info("SHA1 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 20);
    log_info("\n");
}

/**
 * @brief  Show how to calculate MD5 value by ALGO lib for a message 
 */
void TestMD5()
{
    uint8_t result[16];
    
    log_info("\n");
    CalcHASH(HASH_ALG_MD5, HASH_TEST_MSG, result);
    log_info("MD5 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 16);
    log_info("\n");
}

/**
 * @brief  Show how to calculate SHA224 value by ALGO lib for a message 
 */
void TestSHA224()
{
    uint8_t result[28];
    
    log_info("\n");
    CalcHASH(HASH_ALG_SHA224, HASH_TEST_MSG, result);
    log_info("SHA224 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 28);
    log_info("\n");
}

/**
 * @brief  Show how to calculate SHA256 value by ALGO lib for a message 
 */
void TestSHA256()
{
    uint8_t result[32];
    
    log_info("\n");
    CalcHASH(HASH_ALG_SHA256, HASH_TEST_MSG, result);
    log_info("SHA256 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 32);
    log_info("\n");
}

/**
 * @brief  Show how to encrypt a message by DES, then decrypt it and compare the result.
 */
void TestDES(void)
{
    DES_PARM DES_Parm;
#ifdef  __IAR_ARM
    uint8_t key[8]   = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint8_t cipher[8];
    uint8_t plainOut[8];
#else
    _Alignas(4) uint8_t key[8]   = {1, 2, 3, 4, 5, 6, 7, 8};
    _Alignas(4) uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    _Alignas(4) uint8_t cipher[8];
    _Alignas(4) uint8_t plainOut[8];
#endif
    
    log_info("\n");
    
    DES_Parm.in        = (uint32_t*)plain;
    DES_Parm.out       = (uint32_t*)cipher;
    DES_Parm.key       = (uint32_t*)key;
    DES_Parm.iv        = NULL; // IV is not needed in ECB mode
    DES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
    DES_Parm.Mode      = DES_ECB;
    DES_Parm.En_De     = DES_ENC;
    DES_Parm.keyMode   = DES_KEY;

    // encrypt data
    if (DES_Init_OK != DES_Init(&DES_Parm))
    {
        log_error("DES_Init failed.\n");
        return;
    }
    if (DES_Crypto_OK != DES_Crypto(&DES_Parm))
    {
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

    DES_Parm.in    = (uint32_t*)cipher;
    DES_Parm.out   = (uint32_t*)plainOut;
    DES_Parm.En_De = DES_DEC;

    // decrypt data
    if (DES_Init_OK != DES_Init(&DES_Parm))
    {
        log_error("DES_Init failed.\n");
        return;
    }
    if (DES_Crypto_OK != DES_Crypto(&DES_Parm))
    {
        log_error("DES_Crypto failed\n");
        return;
    }

    log_info("decrypt out = ");
    DumpBytes(plainOut, 8);
    log_info("\n");
    if (memcmp(plain, plainOut, sizeof(plain)) != 0)
    {
        log_error("DES decrypt result do not equal plain data.\n");
        while(1);
    }
    else
    {
        log_info("DES test OK!\n");
    }
}

/**
 * @brief  Show how to encrypt a message by AES, then decrypt it and compare the result.
 */
void TestAES(void)
{
    AES_PARM AES_Parm;
#ifdef  __IAR_ARM
    uint8_t key[16]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8_t plain[16] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
    uint8_t cipher[16];
    uint8_t plainOut[16];
#else
    _Alignas(4) uint8_t key[16]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    _Alignas(4) uint8_t plain[16] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
    _Alignas(4) uint8_t cipher[16];
    _Alignas(4) uint8_t plainOut[16];
#endif
        
    log_info("\n");
        
    AES_Parm.in         = (uint32_t*)plain;
    AES_Parm.out        = (uint32_t*)cipher;
    AES_Parm.key        = (uint32_t*)key;
    AES_Parm.iv         = NULL; // IV is not needed in ECB mode
    AES_Parm.inWordLen  = sizeof(plain) / sizeof(uint32_t);
    AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
    AES_Parm.Mode       = AES_ECB;
    AES_Parm.En_De      = AES_ENC;

    // encrypt data
    if (AES_Init_OK != AES_Init(&AES_Parm))
    {
        log_error("AES_Init failed.\n");
        return;
    }
    if (AES_Crypto_OK != AES_Crypto(&AES_Parm))
    {
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

    AES_Parm.in    = (uint32_t*)cipher;
    AES_Parm.out   = (uint32_t*)plainOut;
    AES_Parm.En_De = AES_DEC;

    // decrypt data
    if (AES_Init_OK != AES_Init(&AES_Parm))
    {
        log_error("AES_Init failed.\n");
        return;
    }
    if (AES_Crypto_OK != AES_Crypto(&AES_Parm))
    {
        log_error("AES_Crypto failed\n");
        return;
    }

    log_info("decrypt out = ");
    DumpBytes(plainOut, sizeof(plainOut));
    log_info("\n");
    if (memcmp(plain, plainOut, sizeof(plain)) != 0)
    {
        log_error("AES decrypt result do not equal plain data.\n");
        while(1);
    }
    else
    {
        log_info("AES test OK!\n");
    }
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

	    // RNG test
    TestRand();

    // HASH test
    TestMD5();
    TestSHA1();
    TestSHA224();
    TestSHA256();

    // Cryptogram algorithm
    TestDES();
    TestAES();
		
  while (1) {
    Led3Toogle();
    printf("Freq %u, ticks:%u\n\r", SystemCoreClock, g_ticks);

    simple_delay_ms(300);
  }
}
