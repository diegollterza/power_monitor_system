#include <Wifidata.h>

WifiData::WifiData() {}

String WifiData::getSavedSsid() {
  char c_ssid[buffer_size];
  dm->readData(0, buffer_size, c_ssid);
  return String(c_ssid);
}

String WifiData::getSavedPassword() {
  char c_pass[buffer_size];
  dm->readData(buffer_size, buffer_size, c_pass);
  return String(c_pass);
}

void WifiData::saveSsid(String ssid) {
  char c_ssid[buffer_size];
  ssid.toCharArray(c_ssid, buffer_size);
  dm->saveData(0, buffer_size, c_ssid);
}

void WifiData::savePassword(String password) {
  char c_pass[buffer_size];
  password.toCharArray(c_pass, buffer_size);
  dm->saveData(buffer_size, buffer_size, c_pass);
}

WifiData* WifiData::instance = 0;

WifiData* WifiData::getInstance() {
  if (!instance) instance = new WifiData();
  return instance;
}