#include <Relay.h>

Relay::Relay() {
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  int_pin = 0;
  b_is_on = false;
}

void Relay::setPin(int pin) { int_pin = pin; }

void Relay::turnOn() {
  digitalWrite(int_pin, HIGH);
  b_is_on = true;
  LOG->I(TAG, "Relay turned on");
}

void Relay::turnOff() {
  b_is_on = false;
  digitalWrite(int_pin, LOW);
  LOG->I(TAG, "Relay turned off");
}

bool Relay::isOn() {
  LOG->I(TAG, "Is on: " + String(b_is_on));
  return b_is_on;
}

Relay* Relay::instance = 0;

Relay* Relay::getInstance() {
  if (instance == 0) {
    instance = new Relay();
  }
  return instance;
}