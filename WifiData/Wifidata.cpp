#include <Wifidata.h>

WifiData::WifiData() {
  EEPROM.begin(2 * buffer_size);
  c_ssid = (char *)(malloc(buffer_size));
  c_password = (char *)(malloc(buffer_size));
  for (int i = 0; i < buffer_size; i++) {
    c_ssid[i] = EEPROM.read(i);
    c_password[i] = EEPROM.read(i + buffer_size);
  }
  EEPROM.end();
}

String WifiData::getSavedSsid() {
  EEPROM.begin(2 * buffer_size);
  int i = 0;
  while (i <= buffer_size) {
    c_ssid[i] = EEPROM.read(i);
    i++;
  }
  LOG->I(TAG, "Retrieving saved ssid: " + String(c_ssid));
  EEPROM.end();
  return String(c_ssid);
}

String WifiData::getSavedPassword() {
  EEPROM.begin(2 * buffer_size);
  int i = 0;
  while (i <= buffer_size) {
    c_password[i] = EEPROM.read(i + buffer_size);
    i++;
  }
  LOG->I(TAG, "Retrieving saved password.");
  EEPROM.end();
  return String(c_password);
}

void WifiData::saveSsid(String ssid) {
  EEPROM.begin(2 * buffer_size);
  for (int i = 0; i <= ssid.length(); i++) {
    EEPROM.write(i, ssid[i]);
    c_ssid[i] = ssid[i];
    EEPROM.commit();
    if (i == buffer_size) break;
  }
  LOG->I(TAG, "Saving new ssid: " + ssid);
  EEPROM.end();
}

void WifiData::savePassword(String password) {
  EEPROM.begin(2 * buffer_size);
  for (int i = 0; i <= password.length(); i++) {
    EEPROM.write(i + buffer_size, password[i]);
    c_password[i] = password[i];
    EEPROM.commit();
    if (i == buffer_size) break;
  }
  LOG->I(TAG, "Saving new password.");
  EEPROM.end();
}

WifiData* WifiData::instance = 0;

WifiData* WifiData::getInstance(){
  if(!instance) instance = new WifiData();
  return instance;
}