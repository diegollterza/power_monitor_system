#include <Arduino.h>
#include <Command.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <WifiData.h>
#include <GiotData.h>

Command::Command(GiotData* gdata, Relay* relay, Wifi* wifi, WifiData* wifidata, Log *LOG) {
  str_command = "";
  str_parameters = "";
  str_ca = "";
  this->relay = relay;
  this->wifi = wifi;
  this->wifidata = wifidata;
  this->gdata = gdata;
  this->LOG = LOG;
  LOG->I(TAG, "Command initialized");
}

bool Command::readCommand() {
  if (!Serial.available()) return false;
  String str_full_command = Serial.readString();
  char c_com[int_max_command_size];
  str_full_command.toCharArray(c_com, int_max_command_size);
  str_command = strtok(c_com, ":");
  str_parameters = strtok(NULL, ":");
  return executeCommand();
}

bool Command::executeCommand() {
  bool b_success = true;
  if (!str_command.length()) return false;
  if (str_command == "connect") {
    if (wifi->connect()) {
      LOG->I(TAG, "connected to wifi by command");
    } else {
      LOG->E(TAG, "couldn't connect on wifi by command");
    }
  } else if (str_command == "disconnect") {
    wifi->disconnect();
    LOG->I(TAG, "disconnected to wifi");
  } else if (str_command == "setssid") {
    wifi->setSsid(str_parameters);
    LOG->I(TAG, "ssid changed");
  } else if (str_command == "setpassword") {
    wifi->setPassword(str_parameters);
    LOG->I(TAG, "password changed");
  } else if (str_command == "relayon") {
    relay->turnOn();
    LOG->I(TAG, "relay turned on");
  } else if (str_command == "relayoff") {
    relay->turnOff();
    LOG->I(TAG, "relay turned off");
  } else if (str_command == "saveca") {
    str_ca = str_ca + str_parameters;
    LOG->I(TAG, "received line of ssl certificate: " + str_parameters);
  } else if (str_command == "commitca") {
    gdata->saveCa(str_ca);
    LOG->I(TAG, "saved google ssl certificate:\n" + str_ca);
  } else {
    b_success = false;
  }
  if (b_success) {
    LOG->I(TAG, "Command " + str_command +
                    " executed succesfully with parameters " + str_parameters);
  } else {
    LOG->I(TAG, "Command " + str_command + " failed with parameters " +
                    str_parameters);
  }
  // Reset the command strings (to avoid errors)
  str_command = "";
  str_parameters = "";
}