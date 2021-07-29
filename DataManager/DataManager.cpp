#include <Arduino.h>
#include <DataManager.h>
#include <EEPROM.h>
#include <Log.h>

DataManager::DataManager(Log *LOG) {
  this->LOG = LOG;
  LOG->I(TAG, "DataManager initialized");
}

void DataManager::saveData(int offset, int max_size, char *data) {
  EEPROM.begin(offset + max_size);
  int i = 0;
  while (i < max_size) {
    EEPROM.write(offset + max_size, data[i]);
  }
  EEPROM.end();
  LOG->I(TAG, "Saved data in EEPROM at position " + String(offset) +
                 "with max size of " + String(max_size) +
                 "data saved:" + String(data));
}

char *DataManager::readData(int offset, int max_size) {
  EEPROM.begin(offset + max_size);
  int i = 0;
  char c_data[max_size];
  while (i < max_size) {
    c_data[i] = EEPROM.read(offset + i);
  }
  EEPROM.end();
  LOG->I(TAG, "Read data in EEPROM at position " + String(offset) +
                 "with max size of " + String(max_size) +
                 "data read: " + String(c_data));
  return c_data;
}