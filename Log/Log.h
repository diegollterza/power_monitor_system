#ifndef LOG_H
#define LOG_H

#include <NTPClient.h>
#include <WiFiUdp.h>

#include "Arduino.h"
#include "debug.h"

class Log {
 public:
  static Log *getInstance();
  void E(String TAG, String logMessage);
  void I(String TAG, String logMessage);
  void D(String TAG, String logMessage);

 private:
  Log();
  static Log *instance;
  NTPClient *timeClient;
  WiFiUDP *udp;
  static const inline String TAG = "Log";
};

#endif