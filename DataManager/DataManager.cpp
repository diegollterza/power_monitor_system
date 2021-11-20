#include <Arduino.h>
#include <DataManager.h>
#include <EEPROM.h>
#include <log.h>

DataManager::DataManager() {}

void DataManager::saveData(int offset, int max_size, String data) {
  int i = 0;
  while (i < max_size && i < data.length()) {
    EEPROM.write(offset + i, data[i]);
    i++;
  }
  EEPROM.write(offset + i, '\0');
  EEPROM.commit();
  log->D(TAG, "Saved data in EEPROM at position " + String(offset) +
                  " with max size of " + String(max_size));
  log->D(TAG, "Data saved: " + String(data));
}

String DataManager::readData(int offset, int max_size) {
  int i = 0;
  char c = 'a';
  String buffer;
  while (i < max_size && c != '\0') {
    c = EEPROM.read(offset + i);
    buffer += char(c);
    i++;
  }
  log->D(TAG, "Read data in EEPROM at position " + String(offset) +
                  " with max size of " + String(max_size) +
                  " data read: " + buffer);
  return buffer;
}

DataManager *DataManager::instance = 0;

DataManager *DataManager::getInstance() {
  if (!instance) instance = new DataManager();
  return instance;
}