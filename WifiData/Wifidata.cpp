#include "Arduino.h"
#include "Wifidata.h"
#include "Log.h"
#include <EEPROM.h>

WifiData::WifiData(Log *LOG)
{
  this->buffer_size = 128; //fixed buffer size of 128 bytes
  char ssid_ch[buffer_size];
  char pass_ch[buffer_size];
  for(int i = 0; i < buffer_size; i++){
      ssid_ch[i] = EEPROM.read(i);
      pass_ch[i] = EEPROM.read(i + buffer_size);
  }
  this->ssid = String(ssid_ch);
  this->password = String(pass_ch);
  this->LOG = LOG;
  this->TAG = "WifiData";
  EEPROM.begin(2*buffer_size);
}

String WifiData::getSavedSsid(){
    char ssid_ch[buffer_size];
    int i = 0;
    char c = 'a';
    while(c != '\0' && i <= buffer_size){
        ssid_ch[i] = EEPROM.read(i);
        i++;
    }
    this->ssid = String(ssid_ch);
    LOG->I(TAG, "Retrieving saved ssid: " + this->ssid);
    return this->ssid;
}

String WifiData::getSavedPassword(){
    char pass_ch[buffer_size];
    int i = 0;
    char c = 'a';
    while(c != '\0' && i <= buffer_size){
        pass_ch[i] = EEPROM.read(i + buffer_size);
        i++;
    }
    this->password= String(pass_ch);
    LOG->I(TAG, "Retrieving saved password.");
    return this->password;
}

void WifiData::saveSsid(String ssid){
    this->ssid = ssid;
    for(int i = 0; i <= this->ssid.length(); i++){
        EEPROM.write(i, this->ssid[i]);
        EEPROM.commit();
        if(i==buffer_size) break;
    }
    LOG->I(TAG, "Saving new ssid: " + ssid);
}

void WifiData::savePassword(String password){
    this->password = password;
    for(int i = 0; i <= this->password.length(); i++){
        EEPROM.write(i + buffer_size, this->password[i]);
        EEPROM.commit();
        if(i==buffer_size) break;
    }
    LOG->I(TAG, "Saving new password.");
}