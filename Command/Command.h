#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>

class Command {
 public:
  Command(Relay *relay, Wifi *wifi, WifiData *wifidata, Log *LOG);
  Command(int max_command_size, Relay *relay, Wifi *wifi, WifiData *wifidata,
          Log *LOG);
  bool readCommand();

 private:
  bool executeCommand();
  String str_command;
  String str_parameters;
  static const inline String TAG = "Command";
  int int_max_command_size;
  Log *LOG;
  Wifi *wifi;
  WifiData *wifidata;
  Relay *relay;
};

#endif