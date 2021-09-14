#include <PowerMonitor.h>

PowerMonitor::PowerMonitor() {
  this->pin = A0;
  this->voltage = 110;
  this->current = 0.050;
  this->resistor = 680;
  monitor = new EnergyMonitor();
  monitor->current(pin, 2000 / resistor);
   log->I(TAG, "PowerMonitor initialized");
}

double PowerMonitor::readPower() {
  double Irms = monitor->calcIrms(1480);
  double power = Irms * voltage;
  log->I(TAG, "Reading Irms value: " + String(Irms) + "A" +
                  " Power = " + String(power) + "W");
  return power;
}

void PowerMonitor::setPin(int pin) {
  this->pin = pin;
  log->I(TAG, "Pin set to " + String(pin));
}

void PowerMonitor::setVoltage(int voltage) {
  this->voltage = voltage;
  log->I(TAG, "Voltage set to " + String(voltage));
}

void PowerMonitor::setResistor(float resistor) {
  this->resistor = resistor;
  log->I(TAG, "Resistor set to " + String(resistor));
}

PowerMonitor* PowerMonitor::instance = 0;

PowerMonitor* PowerMonitor::getInstance() {
  if (!instance) instance = new PowerMonitor();
  return instance;
}