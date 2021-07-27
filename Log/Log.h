#ifndef LOG_H
#define LOG_H

#include <NTPClient.h>

#include "Arduino.h"
#include "debug.h"

class Log {
 public:
  Log(NTPClient *timeClient);
  Log(int baud_rate, NTPClient *timeClient);
  void E(String TAG, String logMessage);
  void I(String TAG, String logMessage);
  void D(String TAG, String logMessage);

 private:
  NTPClient *timeClient;
  static const inline String TAG = "Log";
};

#endif