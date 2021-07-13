#include "Arduino.h"
#include "Log.h"
#include "Wifi.h"
#include "Command.h"

Command::Command(Wifi *wifi, Log *LOG){
  this->command = "";
  this->parameters = "";
  this->LOG = LOG;
  this->wifi = wifi;
  this->TAG = "Command";
  this->max_command_size = 128; //default command size
}

Command::Command(int max_command_size, Wifi *wifi, Log *LOG){
  this->command = "";
  this->parameters = "";
  this->LOG = LOG;
  this->wifi = wifi;
  this->TAG = "Command";
  this->max_command_size = max_command_size;
}

void Command::readCommand(){
  String full_command = Serial.readString();
  char com_ch[max_command_size];
  full_command.toCharArray(com_ch, max_command_size);
  command = strtok(com_ch, ":");
  parameters = strtok(NULL, ":");
  executeCommand();
}

bool Command::executeCommand(){
  if(!command.length()){
      LOG->E(TAG, "executeCommand() was called but there is no command to execute.");
      return false;
  }
  // Reset the command strings
  command = "";
  parameters = "";
}