#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Arduino.h"
#include "Log.h"

class Wifi {
 public:
  Wifi(WiFiClient *espClient, Log *LOG);
  Wifi(String ssid, String password, int max_try, WiFiClient *espClient,
       Log *LOG);
  bool connect();
  void disconnect();
  void setNetworkParameters(String ssid, String password);
  void setSsid(String ssid);
  void setPassword(String password);
  bool isConnected();

 private:
  String ssid;
  String password;
  static const inline String TAG = "Wifi";
  Log *LOG;
  WiFiClient *espClient;
  int max_try;
};

#endif