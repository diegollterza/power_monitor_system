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
  void calibrate(double real_current, double delta, double accept_percentage);

 private:
  PowerMonitor();
  int pin;
  float resistor;
  int voltage;
  float current;
  int turns;
  static const inline String TAG = "PowerMonitor";
  EnergyMonitor *monitor;
  static inline Log *log = Log::getInstance();
  static PowerMonitor *instance;
};

#endif