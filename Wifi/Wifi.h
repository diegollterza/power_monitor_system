#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Log.h>
#include <WiFiUdp.h>
#include <Wifidata.h>

class Wifi {
 public:
  bool connect();
  void disconnect();
  void setSsid(String ssid);
  void setPassword(String password);
  bool isConnected();
  static Wifi *getInstance();

 private:
  Wifi();
  static Wifi *instance;
  int TIMEOUT = 15000;
  static const inline String TAG = "Wifi";
  static inline Log *log = Log::getInstance();
  static inline WifiData *wifidata = WifiData::getInstance();
  void configureWebTime();
  WiFiClient *espClient;
};

#endif