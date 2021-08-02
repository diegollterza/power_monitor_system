#ifndef WIFIDATA_H
#define WIFIDATA_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Log.h>

class WifiData {
 public:
  static WifiData *getInstance();
  String getSavedSsid();
  String getSavedPassword();
  void saveSsid(String ssid);
  void savePassword(String password);

 private:
  WifiData();
  char *c_ssid;
  char *c_password;
  static const inline String TAG = "WifiData";
  static inline Log *LOG = Log::getInstance();
  static const inline int buffer_size = 128;  // fixed buffer size of 128 bytes
  static WifiData *instance;
};

#endif