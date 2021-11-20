#include "log.h"

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define DEBUG  // Can't define DEBUG on other libraries, need to define it here

Log::Log() {
  udp = new WiFiUDP();
  this->timeClient = new NTPClient(*udp, "pool.ntp.org", -10800);
}

void Log::E(String TAG, String logMessage) {
  timeClient->update();
  Serial.println(timeClient->getFormattedTime() + " E " + TAG + ": " +
                 logMessage);
}

void Log::I(String TAG, String logMessage) {
  timeClient->update();
  Serial.println(timeClient->getFormattedTime() + " I " + TAG + ": " +
                 logMessage);
}

void Log::D(String TAG, String logMessage) {
  timeClient->update();
#ifdef DEBUG
  Serial.println(timeClient->getFormattedTime() + " D " + TAG + ": " +
                 logMessage);
#endif
}

Log* Log::instance = 0;

Log* Log::getInstance() {
  if (instance == 0) {
    instance = new Log();
  }
  return instance;
}