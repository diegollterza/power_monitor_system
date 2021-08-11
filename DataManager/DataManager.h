#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Log.h>

class DataManager {
 public:
  static DataManager *getInstance();
  void saveData(int offset, int max_size, char *data);
  char *readData(int offset, int max_size);

 private:
  DataManager();
  static const inline String TAG = "DataManager";
  static inline Log *LOG = Log::getInstance();
  static DataManager *instance;
};

#endif