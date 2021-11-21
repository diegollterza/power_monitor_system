#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
#include "Log.h"

class Relay {
 public:
  static Relay *getInstance();
  void setPin(int pin);
  void turnOn();
  void turnOff();
  bool isOn();

 private:
  Relay();
  int pin;
  static Relay *instance;
  static const inline String TAG = "Relay";
  static inline Log *log = Log::getInstance();
  bool is_on;
};

#endif