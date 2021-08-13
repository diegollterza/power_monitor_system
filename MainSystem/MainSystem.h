#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <EEPROM.h>
#include <SystemStateMachine.h>

class MainSystem {
 public:
  static MainSystem *getInstance();
  void start();
  void stop();
  void resume();
  void pause();

 private:
  void run();

  int internal_state;
  static const inline int IDLE = 0;
  static const inline int RUNNING = 1;
  static const inline int PAUSED = 2;
  static const inline int STOPPED = 3;

  MainSystem();
  static MainSystem *instance;
  static inline Log *LOG = Log::getInstance();
  static inline SystemStateMachine *smm = SystemStateMachine::getInstance();
  static inline Command *command = Command::getInstance();
  int wait_time;  // time to sleep after each loop of the run
  static const inline String TAG = "MainSystem";
};

#endif