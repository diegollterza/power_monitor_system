#include "log.h"

#include <Arduino.h>
#define DEBUG  // Can't define DEBUG on other libraries, need to define it here

Log::Log() {}

String Log::getCurrentTime(){
  time_t now = time(nullptr);
  String time_now = String(ctime(&now));
  return time_now.substring(0, time_now.length() - 1);
}

void Log::E(String TAG, String logMessage) {
  Serial.println(getCurrentTime() + " E " + TAG + ": " + logMessage);
}

void Log::I(String TAG, String logMessage) {
  time_t now = time(nullptr);
  Serial.println(getCurrentTime() + " I " + TAG + ": " + logMessage);
}

void Log::D(String TAG, String logMessage) {
#ifdef DEBUG
  time_t now = time(nullptr);
  Serial.println(getCurrentTime() + " D " + TAG + ": " + logMessage);
#endif
}

Log* Log::instance = 0;

Log* Log::getInstance() {
  if (instance == 0) {
    instance = new Log();
  }
  return instance;
}