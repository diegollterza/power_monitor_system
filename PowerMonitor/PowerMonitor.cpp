#include <Arduino.h>
#include <EmonLib.h>
#include <Log.h>
#include <PowerMonitor.h>

PowerMonitor::PowerMonitor(EnergyMonitor *monitor) {
  pin = A0;
  a_voltage = 110;
  out_current = 0.050;
  this->resistor = 680;
  this->monitor = monitor;
  monitor->current(pin, 2000 / resistor);
}

PowerMonitor::PowerMonitor(int pin, int resistor, int a_voltage,
                           int out_current, EnergyMonitor *monitor) {
  this->pin = pin;
  this->resistor = resistor;
  this->a_voltage = a_voltage;
  this->out_current = out_current;
  this->monitor = monitor;
  monitor->current(pin, 2000 / resistor);
}

double PowerMonitor::readPower() {
  double Irms = monitor->calcIrms(1480);
  double power = Irms*a_voltage;
  LOG->I(TAG, "Reading Irms value: " + String(Irms) + "A" + " Power = " + String(power) + "W");
  return power;
}