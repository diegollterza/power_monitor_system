#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"
#include "Log.h"
#include "Wifi.h"

class Command
{
  public:
   Command(Wifi *wifi, Log *LOG);
   Command(int max_command_size, Wifi *wifi, Log *LOG);
    void readCommand();
  private:
    bool executeCommand();
    String command;
    String parameters;
    String TAG;
    int max_command_size;
    Log *LOG;
    Wifi *wifi;
};

#endif