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
  int pin;
  float resistor;
  int voltage;
  float current;
  static const inline String TAG = "PowerMonitor";
  EnergyMonitor *monitor;
  static inline Log *log = Log::getInstance();
  static PowerMonitor *instance;
};

#endif