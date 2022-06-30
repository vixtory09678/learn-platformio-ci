/**
 * @file AESSimple.h
 * @author Wannachat Surasiang (wannachat.sur@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 * @ref cryptography
 * "https://iamteam.me/iot-security-esp32-%E0%B8%81%E0%B8%B1%E0%B8%9A%E0%B8%A7%E0%B8%B4%E0%B8%97%E0%B8%A2%E0%B8%B2%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%A3%E0%B8%AB%E0%B8%B1%E0%B8%AA%E0%B8%A5%E0%B8%B1%E0%B8%9A-part-2-8506c05b9172"
 */

#ifndef AES_SIMPLE_H
#define AES_SIMPLE_H

#include <mbedtls/aes.h>
#include <string.h>

#define PROCESS_FAIL -1

class AESSimple {
public:
  int encrypt(uint8_t *input, uint8_t size, uint8_t key[16], uint8_t *encrypt);
  int decrypt(uint8_t *input, size_t size, uint8_t key[16], uint8_t *decrypt);
  size_t calAESBlockSize(size_t size);
};

#endif