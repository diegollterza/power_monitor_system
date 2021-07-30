#ifndef WIFIDATA_H
#define WIFIDATA_H

#include <EEPROM.h>

#include "Arduino.h"
#include "Log.h"

class WifiData {
 public:
  WifiData();
  String getSavedSsid();
  String getSavedPassword();
  void saveSsid(String ssid);
  void savePassword(String password);

 private:
  String ssid;
  String password;
  static const inline String TAG = "WifiData";
  static inline Log *LOG = Log::getInstance();
  static const inline int buffer_size = 128;  // fixed buffer size of 128 bytes
};

#endif