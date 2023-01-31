/*
   MiniMain ESP32S2 implementation of OSC control of board and MiniSSO.
 */


#include "config.h"
#include "secrets.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <Preferences.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiUDP udp;
const uint16_t localPort = OSC_INCOMING_PORT;

uint8_t ledState = HIGH;              // HIGH means led is *on*

#ifndef BUILTIN_LED
#ifdef LED_BUILTIN
#define BUILTIN_LED LED_BUILTIN
#else
#define BUILTIN_LED 13
#endif
#endif

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, ledState); // turn *on* led
  Serial.begin(115200);

  delay(5000);

  Serial.print(F("\nStarting MiniMain ESP32-S2 OSC on "));
  Serial.println(ARDUINO_BOARD);
  Serial.print(F("\ARDUINO_DEPARTMENT_OF_ALCHEMY_MINIMAIN_ESP32S2 value: "));
  Serial.println(ARDUINO_DEPARTMENT_OF_ALCHEMY_MINIMAIN_ESP32S2);

  connect();
}

void loop() {
  receiveOSC();

  delay(10);
}

void connect() {
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println((String) ssid);

//  WiFi.setAutoConnect(true);
//  WiFi.setAutoReconnect(true);
//  WiFi.setSleep(false);
//  WiFi.setTxPower(WIFI_POWER_19dBm));

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));

  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  Serial.println(F("Starting UDP"));
  udp.begin(localPort);
  udp.flush();
  Serial.print(F("Local port: "));
  Serial.println(localPort);
}

void receiveOSC() {
  OSCMessage msg;
  uint16_t size;
  if ((size = udp.parsePacket()) > 0) {
    while (size--) {
      msg.fill(udp.read());
    }
    if (!msg.hasError()) {
      processMessage(msg);
    }
  }
}

void led(OSCMessage &msg) {
  if (msg.isInt(0)) {
    ledState = msg.getInt(0);
    digitalWrite(BUILTIN_LED, ledState);
    Serial.print(F("/led: "));
    Serial.println(ledState);
  }
}

void processMessage(OSCMessage &msg) {
  if (msg.dispatch("/led", led)) return;
}