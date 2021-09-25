/*
 * How to create commands: make a method to handle the parameters
 * and register the command using registerCommand in the constructor of this
 * class. We pass the command and the method memory to it.
 */
#include <CommandContainer.h>

CommandContainer::CommandContainer() {
  registerCommand("Wifi", &CommandContainer::wifiCommand);
}

/*
 * Create a struct of commands and method pointers
 */
void CommandContainer::registerCommand(
    String command, bool((CommandContainer::*mptr)(String[]))) {
  static int i = 0;
  if (i == 128) return;
  command_list[i] = command;
  ptr_list[i] = mptr;
  i++;
}

bool CommandContainer::executeCommand(String command, String parameters[]) {
  if (setMethodPointer(command)) {
    log->E(TAG, "Command not found");
    return false;
  }
  // Create a local pointer to method to call it inside this class
  bool((CommandContainer::*lmptr)(String[]));
  lmptr = ptr_list[pointer_index];
  (this->*lmptr)(parameters);
  return true;
}

/*
 * Set p_i to the command used. This will give the pointer to the method
 * containing the command we want to use
 */
bool CommandContainer::setMethodPointer(String command) {
  this->pointer_index = 0;
  while (command_list[pointer_index].compareTo(command)) {
    log->D(TAG, "Teste: |" + command_list[pointer_index] + "|" + command + "|");
    pointer_index++;
    if (pointer_index == 3) {
      return true;
    }
  }
  log->D(TAG, "Saiu do Loop");
  return false;
}

bool CommandContainer::wifiCommand(String parameters[]) {
  if (parameters[0] == "connect") {
    if (wifi->connect()) {
      log->I(TAG, "connected to wifi by command");
    } else {
      log->E(TAG, "couldn't connect on wifi by command");
    }
    return true;
  } else if (parameters[0] == "disconnect") {
    wifi->disconnect();
    log->I(TAG, "disconnected to wifi");
    return true;
  }
  log->E(TAG, "Wrong wifi command parameters");
  return false;
}

CommandContainer* CommandContainer::instance = 0;

CommandContainer* CommandContainer::getInstance() {
  if (!instance) instance = new CommandContainer();
  return instance;
}