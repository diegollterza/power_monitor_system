#include <PowerMonitor.h>

PowerMonitor::PowerMonitor() {
  i_pin = A0;
  i_voltage = 110;
  f_current = 0.050;
  f_resistor = 680;
  monitor = new EnergyMonitor();
  monitor->current(i_pin, 2000 / f_resistor);
}

double PowerMonitor::readPower() {
  double Irms = monitor->calcIrms(1480);
  double power = Irms * i_voltage;
  LOG->I(TAG, "Reading Irms value: " + String(Irms) + "A" +
                  " Power = " + String(power) + "W");
  return power;
}

void PowerMonitor::setPin(int pin) {
  i_pin = pin;
  LOG->I(TAG, "Pin set to " + String(pin));
}

void PowerMonitor::setVoltage(int voltage) {
  i_voltage = voltage;
  LOG->I(TAG, "Voltage set to " + String(voltage));
}

void PowerMonitor::setResistor(float resistor) {
  f_resistor = resistor;
  LOG->I(TAG, "Resistor set to " + String(resistor));
}

PowerMonitor* PowerMonitor::instance = 0;

PowerMonitor* PowerMonitor::getInstance() {
  if (!instance) instance = new PowerMonitor();
  return instance;
}