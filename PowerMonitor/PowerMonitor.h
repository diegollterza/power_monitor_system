#ifndef POWERMONITOR_H
#define POWERMONITOR_H

#include <Arduino.h>
#include <EmonLib.h>
#include <Log.h>

class PowerMonitor {
 public:
  PowerMonitor(EnergyMonitor *monitor);
  PowerMonitor(int pin, int resistor, int a_voltage, int out_current, EnergyMonitor *monitor);
  double readPower();

 private:
  int pin;
  float resistor;
  int a_voltage;
  float out_current;
  static const inline String TAG = "PowerMonitor";
  EnergyMonitor *monitor;
  static inline Log *LOG = Log::getInstance();
};

#endif