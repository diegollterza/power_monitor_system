#include "Arduino.h"
#include "Relay.h"
#include "Log.h"

Relay::Relay(int pin, Log *LOG){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  this->pin = pin;
  this->LOG = LOG;
  this->TAG = "Relay";
  this->is_on = false;
}

void Relay::turnOn(){
  digitalWrite(pin, HIGH);
  is_on = true;
  LOG->I(TAG, "Relay turned on");
}

void Relay::turnOff(){
  is_on = false;
  digitalWrite(pin, HIGH);
  LOG->I(TAG, "Relay turned off");
}

bool Relay::isOn(){
  LOG->I(TAG, "Is on: " + String(is_on));
  return is_on;
}