#ifndef AES_SIMPLE_H
#define AES_SIMPLE_H
#include <mbedtls/aes.h>
#include <string.h>

#define PROCESS_FAIL -1

class AESSimple {
public:
  AESSimple(/* args */);
  int encrypt(uint8_t *input, uint8_t size, uint8_t key[16], uint8_t *encrypt);
  int decrypt(uint8_t *input, size_t size, uint8_t key[16], uint8_t *decrypt);
  size_t calAESBlockSize(size_t size);

private:
  /* data */
};

#endif