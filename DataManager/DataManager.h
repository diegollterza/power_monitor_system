#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Log.h>

class DataManager {
 public:
  DataManager();
  void saveData(int offset, int max_size, char *data);
  char *readData(int offset, int max_size);

 private:
  static const inline String TAG = "DataManager";
  static inline Log *LOG = Log::getInstance();
};

#endif