#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
#include "Log.h"

class Relay {
 public:
  Relay();
  Relay(int pin);
  void turnOn();
  void turnOff();
  bool isOn();

 private:
  int pin;
  static const inline String TAG = "Relay";
  static inline Log *LOG = Log::getInstance();
  bool is_on;
};

#endif