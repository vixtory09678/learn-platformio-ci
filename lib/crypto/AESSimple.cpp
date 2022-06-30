#include "AESSimple.h"

size_t AESSimple::calAESBlockSize(size_t size) {
  int blockSizeRemain = (size % 16 == 0) ? 0 : 16 - (size % 16);
  int totalMsgBuffSize = size + blockSizeRemain;
  return totalMsgBuffSize;
}

int AESSimple::encrypt(uint8_t *input, uint8_t size, uint8_t key[16],
                       uint8_t *encrypt) {
  mbedtls_aes_context encryptContext;
  uint8_t iv[16] = {0};
  int ret = 0;

  uint8_t msgBuff[size];
  memset(msgBuff, 0, size);
  memcpy(msgBuff, input, size);

  // initial context
  mbedtls_aes_init(&encryptContext);
  ret = mbedtls_aes_setkey_enc(&encryptContext, key, 256);
  if (ret)
    return PROCESS_FAIL;

  // encryption
  ret = mbedtls_aes_crypt_cbc(&encryptContext, ESP_AES_ENCRYPT, size, iv,
                              msgBuff, encrypt);
  if (ret)
    return PROCESS_FAIL;

  return size;
}

int AESSimple::decrypt(uint8_t *input, size_t size, uint8_t key[16],
                       uint8_t *decrypt) {
  mbedtls_aes_context decryptContext;
  uint8_t iv[16] = {0};
  int ret = 0;

  if (size % 16)
    return PROCESS_FAIL;

  uint8_t msgBuff[size];
  memset(msgBuff, 0, size);
  memcpy(msgBuff, input, size);

  // initial context
  mbedtls_aes_init(&decryptContext);
  ret = mbedtls_aes_setkey_dec(&decryptContext, key, 256);
  if (ret)
    return PROCESS_FAIL;

  // decryption
  ret = mbedtls_aes_crypt_cbc(&decryptContext, ESP_AES_DECRYPT, size, iv,
                              msgBuff, decrypt);
  if (ret)
    return PROCESS_FAIL;

  return size;
}