#include <Wifidata.h>

WifiData::WifiData() { log->I(TAG, "WifiData initialized"); }

String WifiData::getSavedSsid() {
  String ssid = dm->readData(0, buffer_size);
  log->I(TAG, "Retrieved saved SSID: " + ssid);
  return ssid;
}

String WifiData::getSavedPassword() {
  String password = dm->readData(buffer_size, buffer_size);
  log->I(TAG, "Retrieved saved password");
  log->D(TAG, "Saved password: " + password);
  return password;
}

void WifiData::saveSsid(String ssid) {
  dm->saveData(0, buffer_size, ssid);
  log->I(TAG, "Saved SSID: " + ssid);
}

void WifiData::savePassword(String password) {
  dm->saveData(buffer_size, buffer_size, password);
  log->I(TAG, "Saved password");
  log->I(TAG, "Password saved: " + password);
}

WifiData* WifiData::instance = 0;

WifiData* WifiData::getInstance() {
  if (!instance) instance = new WifiData();
  return instance;
}