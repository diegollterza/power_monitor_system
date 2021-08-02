#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Arduino.h"
#include "Log.h"

class Wifi {
 public:
  bool connect();
  void disconnect();
  void setNetworkParameters(String ssid, String password);
  void setSsid(String ssid);
  void setPassword(String password);
  bool isConnected();
  static Wifi *getInstance();

 private:
  Wifi();
  static Wifi *instance;
  String ssid;
  String password;
  static const inline String TAG = "Wifi";
  static inline Log *LOG = Log::getInstance();
  WiFiClient *espClient;
  int max_try;
};

#endif