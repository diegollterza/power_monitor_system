#include <PowerMonitor.h>

PowerMonitor::PowerMonitor() {
  this->pin = A0;
  this->voltage = 110;
  this->current = 0.050;
  this->resistor = 680;
  this->turns = 2000;
  monitor = new EnergyMonitor();
  monitor->current(pin, turns / resistor);
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

void PowerMonitor::calibrate(double real_current, double delta,
                             double accept_percentage) {
  double calibration = turns / resistor;
  double current_diff = real_current - monitor->calcIrms(1480);
  double previous_current_diff = 0;
  while (abs(current_diff) > (accept_percentage * real_current)) {
    current_diff = real_current - monitor->calcIrms(1480);
    if (current_diff > 0) {
      if (previous_current_diff < 0) delta /= 2;
      calibration -= delta;
      monitor->current(pin, calibration);
    } else {
      if (previous_current_diff > 0) delta /= 2;
      calibration += delta;
      monitor->current(pin, calibration);
    }
  }
}

PowerMonitor* PowerMonitor::instance = 0;

PowerMonitor* PowerMonitor::getInstance() {
  if (!instance) instance = new PowerMonitor();
  return instance;
}