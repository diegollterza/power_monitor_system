#include "Arduino.h"
#include "Wifi.h"
#include "Log.h"
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

Wifi::Wifi(WiFiClient *espClient, Log *LOG)
{
  this->ssid = "";
  this->password = "";
  this->espClient = espClient;
  this->LOG = LOG;
  this->TAG = "Wifi";
  this->max_try = 50; //5 seconds max try
}

Wifi::Wifi(String ssid, String password, int max_try, WiFiClient *espClient, Log *LOG)
{
  this->ssid = ssid;
  this->password = password;
  this->espClient = espClient;
  this->LOG = LOG;
  this->TAG = "Wifi";
  this->max_try = max_try;
}


bool Wifi::connect(){
  if (WiFi.status() == WL_CONNECTED) {
    LOG->I(TAG, "Wifi already connected, no action to be done");
  }

  WiFi.begin(ssid, password);
  int i = 0;
  LOG->I(TAG, "Trying to connect to SSID:" + ssid);
  while (WiFi.status() != WL_CONNECTED){
      delay(100);
      i++;
      if(i == max_try){
        LOG->E(TAG, "Couldn't connect to SSID: " + ssid); 
        return false;
      }
  }
  LOG->I(TAG, "Connected succesfully to SSID: " + ssid);
  LOG->I(TAG, "Connection info: IP=" + WiFi.localIP().toString());
  return true;
}

void Wifi::disconnect(){
  WiFi.disconnect();
  LOG->I(TAG, "Disconnected from SSID:" + ssid);
}

void Wifi::setNetworkParameters(String ssid, String password){
  String old_ssid = this->ssid;
  this->ssid = ssid;
  this->password = password;
  LOG->I(TAG, "Set new parameters: old_SSID: " + old_ssid + " new_SSID: " + ssid);
}

bool Wifi::isConnected(){
  bool isConn = WiFi.isConnected();
  LOG->I(TAG, "Is connected: " + String(isConn));
  return isConn;
}