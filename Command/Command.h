#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <DataManager.h>
#include <GiotData.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>
#include <CommandContainer.h>

class Command {
 public:
  static Command *getInstance();
  bool readCommand();

 private:
  Command();
  bool parseCommand(String command);
  void executeCommand();
  String command;
  String parameters[10]; // max number of parameters set to 10
  String ca;
  static const inline String TAG = "Command";
  int max_command_size;
  static inline Log *log = Log::getInstance();
  static inline CommandContainer *command_container = CommandContainer::getInstance();
  static Command *instance;
  static inline DataManager *dm = DataManager::getInstance();
};

#endif