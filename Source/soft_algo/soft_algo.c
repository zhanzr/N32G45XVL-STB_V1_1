#include "soft_algo.h"

extern int test_soft_des_ebc(void);
extern int test_soft_md5(char* input);

#define TEST_N 8
#ifndef RAND_SEED
#define RAND_SEED 123
#endif

void TestRand_Soft(void) {
	printf("%s start\r\n\r\n", __func__);

  int32_t result[TEST_N];

  srand(RAND_SEED);
  for (uint32_t i = 0; i < TEST_N; ++i) {
    result[i] = rand();
  }

  for (uint32_t i = 0; i < TEST_N; ++i) {
    printf("%08X ", result[i]);
  }
	printf("%s endof \r\n\r\n", __func__);
}

void TestSHA1_Soft(uint8_t *buf, uint32_t len) {}

// RFC1321 produces incorrect outputs
//MD5 test suite:
//MD5 ("") = e4c23762ed2823a27e62a64b95c024e7
//MD5 ("a") = 793a9bc07e209b286fa416d6ee29a85d
//MD5 ("abc") = 7999dc75e8da648c6727e137c5b77803
//MD5 ("message digest") = 840793371ec58a6cc84896a5153095de
//MD5 ("abcdefghijklmnopqrstuvwxyz") = 98ef94f1f01ac7b91918c6747fdebd96
//MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = dabcd637cde443764c4f8aa099cf23be
//MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = e29c01a1e2a663c26b4a68bf7ec42df7

void TestMD5_Soft(void) {
	printf("%s start\r\n\r\n", __func__);
	test_soft_md5("");
	test_soft_md5("a");
	test_soft_md5("abc");
	test_soft_md5("message digest");
	test_soft_md5("abcdefghijklmnopqrstuvwxyz");
	test_soft_md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	test_soft_md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
	printf("%s endof \r\n\r\n", __func__);
}

void TestSHA224_Soft(uint8_t *buf, uint32_t len) {}

void TestSHA256_Soft(uint8_t *buf, uint32_t len) {}

void TestDES_Soft(void) {
	test_soft_des_ebc();
}

void TestAES_Soft(void) {	
}
