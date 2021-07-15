#ifndef WIFIDATA_H
#define WIFIDATA_H

#include "Arduino.h"
#include "Log.h"
#include <EEPROM.h>

class WifiData
{
  public:
   WifiData(Log *LOG);
    String getSavedSsid();
    String getSavedPassword();
    void saveSsid(String ssid);
    void savePassword(String password);
  private:
    String ssid;
    String password;
    String TAG;
    Log *LOG;
    int buffer_size;
};

#endif