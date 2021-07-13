#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
#include "Log.h"


class Relay
{
  public:
   Relay(int pin, Log *LOG);
    void turnOn();
    void turnOff();
    bool isOn();
  private:
    int pin;
    String TAG;
    Log *LOG;
    bool is_on;
};

#endif