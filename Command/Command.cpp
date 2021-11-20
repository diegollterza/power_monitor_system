#include <Command.h>

Command::Command() {
  command = "";
  ca = "";
  max_command_size = 128;
}

bool Command::readCommand() {
  if (!Serial.available()) return false;
  log->I(TAG, "New command received");
  if (parseCommand(Serial.readString())) {
    command_container->executeCommand(command, parameters);
  }
}

bool Command::parseCommand(String command) {
  if (command == "") return false;
  int len = command.length() + 1;
  int i = 0;
  char com[len];
  command.toCharArray(com, len);
  this->command = String(strtok(com, ":"));
  this->command.trim();
  memset(parameters, 0, sizeof(parameters));  // clear parameters list
  char* param;
  param = strtok(NULL, ":");
  while (param != NULL) {
    parameters[i] = String(param);
    parameters[i].trim();
    param = strtok(NULL, ":");
    i++;
  }
  log->I(TAG, "Command received: " + this->command);
  String p = "";
  for (int j = 0; j <= i; j++) {
    p = p + parameters[j] + " ";
  }
  log->I(TAG, "Command parameters: " + p);
  return true;
}

Command* Command::instance = 0;

Command* Command::getInstance() {
  if (!instance) instance = new Command();
  return instance;
}