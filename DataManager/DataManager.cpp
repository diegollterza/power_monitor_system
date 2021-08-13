#include <Arduino.h>
#include <DataManager.h>
#include <EEPROM.h>
#include <Log.h>

DataManager::DataManager() { LOG->I(TAG, "DataManager initialized"); }

void DataManager::saveData(int offset, int max_size, char *data) {
  EEPROM.begin(10 * 1024);
  int i = 0;
  while (i < max_size) {
    EEPROM.write(offset + i, data[i]);
    i++;
  }
  EEPROM.write(offset + i + 1, '\0');
  EEPROM.commit();
  LOG->D(TAG, "Saved data in EEPROM at position " + String(offset) +
                  " with max size of " + String(max_size));
  LOG->D(TAG, "Data saved: " + String(data));
  EEPROM.end();
}

void DataManager::readData(int offset, int max_size, char *buffer) {
  EEPROM.begin(10 * 1024);
  int i = 0;
  char c = 'a';
  while (i < max_size && c != '\0') {
    c = EEPROM.read(offset + i);
    buffer[i] = c;
    i++;
  }
  LOG->D(TAG, "Read data in EEPROM at position " + String(offset) +
                  " with max size of " + String(max_size) +
                  " data read: " + String(buffer));
  EEPROM.end();
}

DataManager *DataManager::instance = 0;

DataManager *DataManager::getInstance() {
  if (!instance) instance = new DataManager();
  return instance;
}