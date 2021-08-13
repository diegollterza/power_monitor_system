#include <SystemStateMachine.h>

SystemStateMachine::SystemStateMachine() {
  restart();
}

void SystemStateMachine::state() {
  switch (int_state) {
    case INITIAL_STATE:
      LOG->I(TAG, "State: INACTIVE->" + String(STATE_NAMES[int_state]));
      break;
    case WORKING:
      break;
    case NOPOWER:
      break;
    case NOWIFI:
      wifi->getDataFromEeprom();
      wifi->connect();
      break;
  }
  if (int_old_state != int_state) {
    LOG->I(TAG, "State: " + String(STATE_NAMES[int_old_state]) + "->" +
                    String(STATE_NAMES[int_state]));
  }
}

void SystemStateMachine::restart() {
  b_isWifiOn = false;
  b_isRelayOn = false;
  b_isGcon = false;
  int_state = 0;
  int_old_state = 0;
}

void SystemStateMachine::nextState() {
  setInputs();
  int_old_state = int_state;
  int_state = WORKING;
  // if(!b_isGcon) state = NOGCCONNECT;
  if (!b_isRelayOn) int_state = NOPOWER;
  if (!b_isWifiOn) int_state = NOWIFI;
  state();
}

void SystemStateMachine::setInputs() {
  b_isWifiOn = wifi->isConnected();
  b_isRelayOn = relay->isOn();
}

SystemStateMachine *SystemStateMachine::instance = 0;

SystemStateMachine *SystemStateMachine::getInstance() {
  if (!instance) instance = new SystemStateMachine();
  return instance;
}