#include <SystemStateMachine.h>

SystemStateMachine::SystemStateMachine() { restart(); }

void SystemStateMachine::setState() {
  switch (state) {
    case INITIAL_STATE:
      log->I(TAG, "State: INACTIVE->" + String(STATE_NAMES[state]));
      break;
    case WORKING:
      giot->publishTelemetry(String(power_monitor->readPower()));
      break;
    case NOPOWER:
      break;
    case NOWIFI:
      wifi->connect();
      break;
    case NOGIOT:
      giot->connect();
      break;
  }
  if (old_state != state) {
    log->I(TAG, "State: " + String(STATE_NAMES[old_state]) + "->" +
                    String(STATE_NAMES[state]));
  }
}

void SystemStateMachine::restart() {
  isWifiOn = false;
  isRelayOn = false;
  isGcon = false;
  state = 0;
  old_state = 0;
}

void SystemStateMachine::nextState() {
  setInputs();
  old_state = state;
  state = WORKING;
  if (!isGcon) state = NOGIOT;
  if (!isRelayOn) state = NOPOWER;
  if (!isWifiOn) state = NOWIFI;
  setState();
}

void SystemStateMachine::setInputs() {
  log->I(TAG, "Getting statemachine inputs");
  isWifiOn = wifi->isConnected();
  isRelayOn = relay->isOn();
  isGcon = giot->isConnected();
}

SystemStateMachine *SystemStateMachine::instance = 0;

SystemStateMachine *SystemStateMachine::getInstance() {
  if (!instance) instance = new SystemStateMachine();
  return instance;
}