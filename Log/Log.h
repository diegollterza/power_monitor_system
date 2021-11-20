#ifndef log_H
#define log_H

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
  String getCurrentTime();
  static Log *instance;
  static const inline String TAG = "Log";
};

#endif