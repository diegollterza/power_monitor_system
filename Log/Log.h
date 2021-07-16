#ifndef LOG_H
#define LOG_H

#include "Arduino.h"
#include <NTPClient.h>
#include "debug.h"

class Log
{
  public:
    Log(NTPClient *timeClient);
    Log(int baud_rate, NTPClient *timeClient);
    void E(String TAG, String logMessage);
    void I(String TAG, String logMessage);
    void D(String TAG, String logMessage);
  private:
    NTPClient *timeClient;
};

#endif