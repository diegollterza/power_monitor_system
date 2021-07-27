#include <Arduino.h>
#include <EEPROM.h>
#include <GiotData.h>
#include <Log.h>

GiotData::GiotData(Log *LOG) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_ca[int_ca_buffer_size];
  char c_project_id[int_project_info_buffer_size];
  char c_location[int_project_info_buffer_size];
  char c_registry_id[int_project_info_buffer_size];
  char c_device_id[int_project_info_buffer_size];
  int i = 0, j;
  while (i <= int_ca_buffer_size) {
    {
      j = i + 1024;  // ca is saved at position 1024 of EEPROM
      c_ca[i] = EEPROM.read(j);
      c_project_id[i] = EEPROM.read(j + 2048);
      c_location[i] = EEPROM.read(j + 2048 + int_project_info_buffer_size);
      c_registry_id[i] =
          EEPROM.read(j + 2048 + 2 * int_project_info_buffer_size);
      c_device_id[i] = EEPROM.read(j + 2048 + 3 * int_project_info_buffer_size);
      i++;
    }
    str_ca = String(c_ca);
    str_project_id = String(c_project_id);
    str_location = String(c_location);
    str_registry_id = String(c_registry_id);
    str_device_id = String(c_device_id);
    this->LOG = LOG;
    EEPROM.end();
  }
}

void GiotData::saveCa(String ca) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  str_ca = ca;
  for (int i = 0; i <= str_ca.length(); i++) {
    EEPROM.write(i + 1024, str_ca[i]);
    EEPROM.commit();
    if (i == int_ca_buffer_size) break;
  }
  LOG->I(TAG, "Saving new ca: " + str_ca);
  EEPROM.end();
}

void GiotData::saveProjectId(String project_id) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  str_project_id = project_id;
  for (int i = 0; i <= str_project_id.length(); i++) {
    EEPROM.write(i + 1024 + 2048, str_project_id[i]);
    EEPROM.commit();
    if (i == int_project_info_buffer_size) break;
  }
  LOG->I(TAG, "Saving new project id: " + str_project_id);
  EEPROM.end();
}

void GiotData::saveLocation(String location) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  str_location = location;
  for (int i = 0; i <= str_location.length(); i++) {
    EEPROM.write(i + 1024 + 2048 + int_project_info_buffer_size,
                 str_location[i]);
    EEPROM.commit();
    if (i == int_project_info_buffer_size) break;
  }
  LOG->I(TAG, "Saving new location: " + str_location);
  EEPROM.end();
}

void GiotData::saveRegistryId(String registry_id) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  str_registry_id = registry_id;
  for (int i = 0; i <= str_registry_id.length(); i++) {
    EEPROM.write(i + 1024 + 2048 + 2 * int_project_info_buffer_size,
                 str_registry_id[i]);
    EEPROM.commit();
    if (i == int_project_info_buffer_size) break;
  }
  LOG->I(TAG, "Saving new registry id: " + str_registry_id);
  EEPROM.end();
}

void GiotData::saveDeviceId(String device_id) {
  EEPROM.begin(int_ca_buffer_size + 4096);
  str_device_id = device_id;
  for (int i = 0; i <= str_device_id.length(); i++) {
    EEPROM.write(i + 1024 + 2048 + 3 * int_project_info_buffer_size,
                 str_device_id[i]);
    EEPROM.commit();
    if (i == int_project_info_buffer_size) break;
  }
  LOG->I(TAG, "Saving new device id: " + str_device_id);
  EEPROM.end();
}

String GiotData::getSavedCa() {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_ca[int_ca_buffer_size];
  int i = 0;
  while (i <= int_ca_buffer_size) {
    c_ca[i] = EEPROM.read(i + 1024);
    i++;
  }
  str_ca = String(c_ca);
  LOG->I(TAG, "Retrieving saved ca: " + str_ca);
  EEPROM.end();
  return str_ca;
}

String GiotData::getSavedProjectId() {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_project_id[int_project_info_buffer_size];
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_project_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  str_project_id = String(c_project_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_project_id);
  EEPROM.end();
  return str_project_id;
}

String GiotData::getSavedLocation() {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_location[int_project_info_buffer_size];
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_location[i] = EEPROM.read(i + 1024 + 2048 + int_project_info_buffer_size);
    i++;
  }
  str_location = String(c_location);
  LOG->I(TAG, "Retrieving saved project id: " + str_location);
  EEPROM.end();
  return str_location;
}

String GiotData::getSavedRegistryId() {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_registry_id[int_project_info_buffer_size];
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_registry_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  str_registry_id = String(c_registry_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_registry_id);
  EEPROM.end();
  return str_registry_id;
}

String GiotData::getSavedDeviceId() {
  EEPROM.begin(int_ca_buffer_size + 4096);
  char c_device_id[int_project_info_buffer_size];
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_device_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  str_device_id = String(c_device_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_device_id);
  EEPROM.end();
  return str_device_id;
}