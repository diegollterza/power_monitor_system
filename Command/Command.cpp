#include "Arduino.h"
#include "Log.h"
#include "Wifi.h"
#include "Command.h"
#include "WifiData.h"
#include "Relay.h"

Command::Command(Relay *relay, Wifi *wifi, WifiData *wifidata, Log *LOG){
  this->command = "";
  this->parameters = "";
  this->LOG = LOG;
  this->relay = relay;
  this->wifi = wifi;
  this->wifidata = wifidata;
  this->TAG = "Command";
  this->max_command_size = 128; //default command size
}

Command::Command(int max_command_size, Relay *relay, Wifi *wifi, WifiData *wifidata, Log *LOG){
  this->command = "";
  this->parameters = "";
  this->LOG = LOG;
  this->relay = relay;
  this->wifi = wifi;
  this->wifidata = wifidata;
  this->TAG = "Command";
  this->max_command_size = max_command_size;
}

bool Command::readCommand(){
  if(!Serial.available()) return false;
  String full_command = Serial.readString();
  char com_ch[max_command_size];
  full_command.toCharArray(com_ch, max_command_size);
  command = strtok(com_ch, ":");
  parameters = strtok(NULL, ":");
  LOG->I(TAG, "Executing command " + command +" with parameters " + parameters);
  return executeCommand();
}

bool Command::executeCommand(){
  if(!command.length()) return false;
  if(command == "connect"){
    if(wifi->connect()){
      LOG->I(TAG, "connected to wifi by command");
    }else{
      LOG->E(TAG, "couldn't connect on wifi by command");
    }
  }
  if(command == "disconnect"){
    wifi->disconnect();
    LOG->I(TAG, "disconnected to wifi by command");
  }
  if(command == "setssid"){
    wifi->setSsid(parameters);
    LOG->I(TAG, "ssid changed by command");
  }
  if(command == "setpassword"){
    wifi->setPassword(parameters);
    LOG->I(TAG, "password changed by command");
  }
  if(command == "relayon"){
    relay->turnOn();
    LOG->I(TAG, "relay turned on by command");
  }
  if(command == "relayoff"){
    relay->turnOff();
    LOG->I(TAG, "relay turned off by command");
  }
  // Reset the command strings
  command = "";
  parameters = "";
}