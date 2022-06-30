#include <AESSimple.h>
#include <Arduino.h>
#include <unity.h>

AESSimple aes;
const char key[16] = "i am team";
String plainText = "hello my mom";
size_t bufferSize = 0;
size_t size = 0;

uint8_t dataToBeEncrypted[50] = {0};
uint8_t bufferToBeDecrypted[50] = {0};

void test_encryption() {

  bufferSize = aes.calAESBlockSize(plainText.length());
  size = aes.encrypt((uint8_t *)plainText.c_str(), bufferSize, (uint8_t *)key,
                     dataToBeEncrypted);

  if (size == -1) {
    TEST_FAIL_MESSAGE("Encryption failed");
  }

  TEST_PASS();
}

void test_decryption() {

  size = aes.decrypt(dataToBeEncrypted, bufferSize, (uint8_t *)key,
                     bufferToBeDecrypted);
  if (size == PROCESS_FAIL) {
    return;
  }

  String decrypted = String((char *)bufferToBeDecrypted);
  TEST_ASSERT_EQUAL_STRING(plainText.c_str(), decrypted.c_str());
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(testEncryption);
  RUN_TEST(testDecryption);
  UNITY_END();
}

void loop() {}
