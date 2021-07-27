#include "Wifi.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Arduino.h"
#include "Log.h"

Wifi::Wifi(WiFiClient *espClient, Log *LOG) {
  this->ssid = "";
  this->password = "";
  this->espClient = espClient;
  this->LOG = LOG;
  this->max_try = 50;  // 5 seconds max try
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

Wifi::Wifi(String ssid, String password, int max_try, WiFiClient *espClient,
           Log *LOG) {
  this->ssid = ssid;
  this->password = password;
  this->espClient = espClient;
  this->LOG = LOG;
  this->max_try = max_try;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

bool Wifi::connect() {
  if (WiFi.status() == WL_CONNECTED) {
    LOG->I(TAG, "Wifi already connected, no action to be done");
  }

  WiFi.begin(ssid, password);
  int i = 0;
  LOG->I(TAG, "Trying to connect to SSID:" + ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    i++;
    if (i == max_try) {
      LOG->E(TAG, "Couldn't connect to SSID: " + ssid);
      return false;
    }
  }
  LOG->I(TAG, "Connected succesfully to SSID: " + ssid);
  LOG->I(TAG, "Connection info: IP=" + WiFi.localIP().toString() + " rssi=" + WiFi.RSSI());
  digitalWrite(LED_BUILTIN, LOW);
  return true;
}

void Wifi::disconnect() {
  WiFi.disconnect();
  LOG->I(TAG, "Disconnected from ssid:" + ssid);
  digitalWrite(LED_BUILTIN, HIGH);
}

void Wifi::setNetworkParameters(String ssid, String password) {
  this->ssid = ssid;
  this->password = password;
  LOG->I(TAG, "Set network parameters with ssid: " + ssid);
}

bool Wifi::isConnected() {
  bool isConn = WiFi.isConnected();
  LOG->I(TAG, "Is connected: " + String(isConn));
  return isConn;
}

void Wifi::setSsid(String ssid) {
  String old_ssid = this->ssid;
  this->ssid = ssid;
  LOG->I(TAG, "Set ssid:" + ssid);
}

void Wifi::setPassword(String password) {
  this->password = password;
  LOG->I(TAG, "Set password");
}