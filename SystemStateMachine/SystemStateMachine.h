#ifndef SYSTEMSTATEMACHINE_H
#define SYSTEMSTATEMACHINE_H

#include <Command.h>
#include <GiotData.h>
#include <Log.h>
#include <PowerMonitor.h>
#include <Relay.h>
#include <Wifi.h>
#include <Wifidata.h>

class SystemStateMachine {
 public:
  static SystemStateMachine *getInstance();
  void nextState();
  void restart();

 private:
  SystemStateMachine();
  int int_state;
  int int_old_state;
  /* inputs */
  bool b_isWifiOn;
  bool b_isRelayOn;
  bool b_isGcon;

  /* objects initialization */
  static inline Log *LOG = Log::getInstance();
  static inline GiotData *gdata = GiotData::getInstance();
  static inline Relay *relay = Relay::getInstance();
  static inline Wifi *wifi = Wifi::getInstance();
  static inline WifiData *wifidata = WifiData::getInstance();
  static inline PowerMonitor *power_monitor = PowerMonitor::getInstance();

  /* States */
  static const inline int INITIAL_STATE = 0;
  static const inline int NOWIFI = 1;
  static const inline int NOINTERNET = 2;
  static const inline int NOGCCONNECT = 3;
  static const inline int NOPOWER = 4;
  static const inline int WORKING = 5;

  static const inline char *STATE_NAMES[] = {"INITIAL_STATE", "NOWIFI",
                                             "NOINTERNET",    "NOGCCONNECT",
                                             "NOPOWER",       "WORKING"};
  /* Transition state */;
  void state();

  /* Misc */
  void setInputs();

  static const inline String TAG = "SystemStateMachine";
  static SystemStateMachine *instance;
};

#endif