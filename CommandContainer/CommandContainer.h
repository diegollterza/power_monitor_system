#ifndef COMMANDCONTAINER_H
#define COMMANDCONTAINER_H
#include <Arduino.h>
#include <DataManager.h>
#include <GiotData.h>
#include <Log.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>

class CommandContainer {
 public:
  static CommandContainer *getInstance();
  bool executeCommand(String command, String parameters[]);

 private:
  CommandContainer();
  bool setMethodPointer(String);
  void registerCommand(String command,
                       bool((CommandContainer::*mptr)(String[])));


  bool wifiCommand(String parameters[]);
  bool relayCommand(String parameters[]);
  
  String command_list[64];
  bool((CommandContainer::*ptr_list[64])(String[]));
  int pointer_index;
  static const inline String TAG = "CommandContainer";
  static inline Log *log = Log::getInstance();
  static inline Wifi *wifi = Wifi::getInstance();
  static inline WifiData *wifidata = WifiData::getInstance();
  static inline Relay *relay = Relay::getInstance();
  static inline GiotData *gdata = GiotData::getInstance();
  static CommandContainer *instance;
};

#endif