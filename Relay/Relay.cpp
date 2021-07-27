#include "Relay.h"

#include "Arduino.h"
#include "Log.h"

Relay::Relay(Log *LOG) {
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  this->pin = 0;
  this->LOG = LOG;
  this->is_on = false;
}

Relay::Relay(int pin, Log *LOG) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  this->pin = pin;
  this->LOG = LOG;
  this->is_on = false;
}

void Relay::turnOn() {
  digitalWrite(pin, HIGH);
  is_on = true;
  LOG->I(TAG, "Relay turned on");
}

void Relay::turnOff() {
  is_on = false;
  digitalWrite(pin, LOW);
  LOG->I(TAG, "Relay turned off");
}

bool Relay::isOn() {
  LOG->I(TAG, "Is on: " + String(is_on));
  return is_on;
}