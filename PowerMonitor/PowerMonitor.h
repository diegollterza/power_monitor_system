#ifndef POWERMONITOR_H
#define POWERMONITOR_H

#include <Arduino.h>
#include <EmonLib.h>
#include <Log.h>

class PowerMonitor {
 public:
  PowerMonitor(Log *LOG, EnergyMonitor *monitor);
  PowerMonitor(int pin, int resistor, int a_voltage, int out_current, Log *LOG, EnergyMonitor *monitor);
  double readPower();

 private:
  int pin;
  float resistor;
  int a_voltage;
  float out_current;
  static const inline String TAG = "PowerMonitor";
  Log *LOG;
  EnergyMonitor *monitor;
};

#endif