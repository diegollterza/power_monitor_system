#ifndef LOG_H
#define LOG_H

#include "Arduino.h"
#include <NTPClient.h>

class Log
{
  public:
    Log(NTPClient *timeClient);
    void E(String TAG, String logMessage);
    void I(String TAG, String logMessage);
  private:
    NTPClient *timeClient;
};

#endif