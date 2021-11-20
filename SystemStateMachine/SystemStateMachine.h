#ifndef SYSTEMSTATEMACHINE_H
#define SYSTEMSTATEMACHINE_H

#include <Command.h>
#include <Giot.h>
#include <Log.h>
#include <PowerMonitor.h>
#include <Relay.h>
#include <Wifi.h>

class SystemStateMachine {
 public:
  static SystemStateMachine *getInstance();
  void nextState();
  void restart();

 private:
  SystemStateMachine();
  int state;
  int old_state;
  /* inputs */
  bool isWifiOn;
  bool isRelayOn;
  bool isGcon;

  /* objects initialization */
  static inline Log *log = Log::getInstance();
  static inline Relay *relay = Relay::getInstance();
  static inline Wifi *wifi = Wifi::getInstance();
  static inline PowerMonitor *power_monitor = PowerMonitor::getInstance();
  static inline Giot *giot = Giot::getInstance();

  /* States */
  static const inline int INITIAL_STATE = 0;
  static const inline int NOWIFI = 1;
  static const inline int NOINTERNET = 2;
  static const inline int NOGCCONNECT = 3;
  static const inline int NOPOWER = 4;
  static const inline int WORKING = 5;
  static const inline int NOGIOT = 6;

  static const inline char *STATE_NAMES[] = {
      "INITIAL_STATE", "NOWIFI",  "NOINTERNET", "NOGCCONNECT",
      "NOPOWER",       "WORKING", "NOGIOT"};

  /* Transition state */;
  void setState();

  /* Misc */
  void setInputs();

  static const inline String TAG = "SystemStateMachine";
  static SystemStateMachine *instance;
};

#endif