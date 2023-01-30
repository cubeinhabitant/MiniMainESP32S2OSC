/*
   MiniMain ESP32S2 implementation of OSC control of board and MiniSSO.
 */


#include "secrets.h"
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

void setup() {
  Serial.begin(115200);

  delay(5000);

  Serial.print(F("\nStarting MiniMain ESP32-S2 OSC on "));
  Serial.println(ARDUINO_BOARD);
  Serial.print(F("\ARDUINO_DEPARTMENT_OF_ALCHEMY_MINIMAIN_ESP32S2 value: "));
  Serial.println(ARDUINO_DEPARTMENT_OF_ALCHEMY_MINIMAIN_ESP32S2);

}

void loop() {
  // put your main code here, to run repeatedly:

}
