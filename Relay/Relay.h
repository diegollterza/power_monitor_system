#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
#include "Log.h"

class Relay {
 public:
  Relay(Log *LOG);
  Relay(int pin, Log *LOG);
  void turnOn();
  void turnOff();
  bool isOn();

 private:
  int pin;
  static const inline String TAG = "Relay";
  Log *LOG;
  bool is_on;
};

#endif