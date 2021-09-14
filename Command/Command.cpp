#include <Command.h>

Command::Command() {
  command = "";
  parameters = "";
  ca = "";
  max_command_size = 128;
  log->I(TAG, "Command initialized");
}

bool Command::readCommand() {
  if (!Serial.available()) return false;
  log->I(TAG, "New command received");
  String full_command = Serial.readString();
  char com[max_command_size];
  full_command.toCharArray(com, max_command_size);
  command = strtok(com, ":");
  parameters = strtok(NULL, ":");
  return executeCommand();
}

bool Command::executeCommand() {
  bool success = true;
  if (!command.length()) return false;
  if (command == "connect") {
    if (wifi->connect()) {
      log->I(TAG, "connected to wifi by command");
    } else {
      log->E(TAG, "couldn't connect on wifi by command");
    }
  } else if (command == "disconnect") {
    wifi->disconnect();
    log->I(TAG, "disconnected to wifi");
  } else if (command == "setssid") {
    wifi->setSsid(parameters);
    log->I(TAG, "ssid changed");
  } else if (command == "setpassword") {
    wifi->setPassword(parameters);
    log->I(TAG, "password changed");
  } else if (command == "relayon") {
    relay->turnOn();
    log->I(TAG, "relay turned on");
  } else if (command == "relayoff") {
    relay->turnOff();
    log->I(TAG, "relay turned off");
  } else if (command == "saveca") {
    ca = ca + parameters;
    log->I(TAG, "received line of ssl certificate: " + parameters);
  } else if (command == "test") {
    char teste[128];
    dm->readData(0,128,teste);
    log->I(TAG, String(teste));
  } else if (command == "commitca") {
    gdata->saveCa(ca);
    log->I(TAG, "saved google ssl certificate:\n" + ca);
  } else {
    success = false;
  }
  if (success) {
    log->I(TAG, "Command " + command +
                    " executed succesfully with parameters " + parameters);
  } else {
    log->I(TAG, "Command " + command + " failed with parameters " +
                    parameters);
  }
  // Reset the command strings (to avoid errors)
  command = "";
  parameters = "";
}

Command* Command::instance = 0;

Command* Command::getInstance() {
  if (!instance) instance = new Command();
  return instance;
}