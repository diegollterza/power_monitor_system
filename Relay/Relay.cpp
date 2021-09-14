#include <Relay.h>

Relay::Relay() {
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  pin = 0;
  is_on = false;
}

void Relay::setPin(int pin) {
  log->I(TAG, "Relay pin set to " + String(pin));
  this->pin = pin;
}

void Relay::turnOn() {
  digitalWrite(pin, HIGH);
  is_on = true;
  log->I(TAG, "Relay turned on");
}

void Relay::turnOff() {
  is_on = false;
  digitalWrite(pin, LOW);
  log->I(TAG, "Relay turned off");
}

bool Relay::isOn() {
  log->I(TAG, "Is on: " + String(is_on));
  return is_on;
}

Relay* Relay::instance = 0;

Relay* Relay::getInstance() {
  if (instance == 0) {
    instance = new Relay();
  }
  return instance;
}