#include "Wifidata.h"

#include <EEPROM.h>

#include "Arduino.h"
#include "Log.h"

WifiData::WifiData() {
  EEPROM.begin(2 * buffer_size);
  char ssid_ch[buffer_size];
  char pass_ch[buffer_size];
  for (int i = 0; i < buffer_size; i++) {
    ssid_ch[i] = EEPROM.read(i);
    pass_ch[i] = EEPROM.read(i + buffer_size);
  }
  this->ssid = String(ssid_ch);
  this->password = String(pass_ch);
  EEPROM.end();
}

String WifiData::getSavedSsid() {
  EEPROM.begin(2 * buffer_size);
  char ssid_ch[buffer_size];
  int i = 0;
  while (i <= buffer_size) {
    ssid_ch[i] = EEPROM.read(i);
    i++;
  }
  this->ssid = String(ssid_ch);
  LOG->I(TAG, "Retrieving saved ssid: " + this->ssid);
  EEPROM.end();
  return this->ssid;
}

String WifiData::getSavedPassword() {
  EEPROM.begin(2 * buffer_size);
  char pass_ch[buffer_size];
  int i = 0;
  while (i <= buffer_size) {
    pass_ch[i] = EEPROM.read(i + buffer_size);
    i++;
  }
  this->password = String(pass_ch);
  LOG->I(TAG, "Retrieving saved password.");
  EEPROM.end();
  return this->password;
}

void WifiData::saveSsid(String ssid) {
  EEPROM.begin(2 * buffer_size);
  this->ssid = ssid;
  for (int i = 0; i <= this->ssid.length(); i++) {
    EEPROM.write(i, this->ssid[i]);
    EEPROM.commit();
    if (i == buffer_size) break;
  }
  LOG->I(TAG, "Saving new ssid: " + ssid);
  EEPROM.end();
}

void WifiData::savePassword(String password) {
  EEPROM.begin(2 * buffer_size);
  this->password = password;
  for (int i = 0; i <= this->password.length(); i++) {
    EEPROM.write(i + buffer_size, this->password[i]);
    EEPROM.commit();
    if (i == buffer_size) break;
  }
  LOG->I(TAG, "Saving new password.");
  EEPROM.end();
}