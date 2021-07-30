#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>
#include <GiotData.h>

class Command {
 public:
  Command(GiotData *gdata, Relay *relay, Wifi *wifi, WifiData *wifidata);
  bool readCommand();

 private:
  bool executeCommand();
  String str_command;
  String str_parameters;
  String str_ca;
  static const inline String TAG = "Command";
  int int_max_command_size;
  static inline Log *LOG = Log::getInstance();
  Wifi *wifi;
  WifiData *wifidata;
  Relay *relay;
  GiotData *gdata;
};

#endif