#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <GiotData.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>
#include <DataManager.h>

class Command {
 public:
  static Command *getInstance();
  bool readCommand();

 private:
  Command();
  bool executeCommand();
  String command;
  String parameters;
  String ca;
  static const inline String TAG = "Command";
  int max_command_size;
  static inline Log *log = Log::getInstance();
  static inline Wifi *wifi = Wifi::getInstance();
  static inline WifiData *wifidata = WifiData::getInstance();
  static inline Relay *relay = Relay::getInstance();
  static inline GiotData *gdata = GiotData::getInstance();
  static Command *instance;
  static inline DataManager *dm = DataManager::getInstance();
};

#endif