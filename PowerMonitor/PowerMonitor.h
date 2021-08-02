#ifndef POWERMONITOR_H
#define POWERMONITOR_H

#include <Arduino.h>
#include <EmonLib.h>
#include <Log.h>

class PowerMonitor {
 public:
  static PowerMonitor *getInstance();
  double readPower();
  void setPin(int pin);
  void setVoltage(int voltage);
  void setResistor(float resistor);

 private:
  PowerMonitor();
  int i_pin;
  float f_resistor;
  int i_voltage;
  float f_current;
  static const inline String TAG = "PowerMonitor";
  EnergyMonitor *monitor;
  static inline Log *LOG = Log::getInstance();
  static PowerMonitor *instance;
};

#endif