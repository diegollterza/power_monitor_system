#include "Log.h"

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define DEBUG  // Can't define DEBUG on other libraries, need to define it here

Log::Log(NTPClient *timeClient) {
  Serial.begin(115200);
  this->timeClient = timeClient;
  Serial.println(timeClient->getFormattedTime() + " I " + this->TAG + ": " +
                 "Log system initialized");
}

Log::Log(int baud_rate, NTPClient *timeClient) {
  Serial.begin(baud_rate);
  this->timeClient = timeClient;
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