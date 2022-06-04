#include <Arduino.h>

float Divide(int x, int y) {
  if (y == 0.0) {
    return 0.0;
  }

  float result = static_cast<float>(x) / static_cast<float>(y);
  return result;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(Divide(10, 2));
}

void loop() {
  // put your main code here, to run repeatedly:
}