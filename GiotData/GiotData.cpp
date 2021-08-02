#include <GiotData.h>

GiotData::GiotData() {
  EEPROM.begin(16 * 1024);
  int i = 0, j;
  while (i < int_ca_buffer_size) {
    j = i + 1024;  // ca is saved at position 1024 of EEPROM
    c_ca[i] = EEPROM.read(j);
    if (i < int_project_info_buffer_size) {
      c_project_id[i] = EEPROM.read(j + 2048);
      c_location[i] = EEPROM.read(j + 2048 + int_project_info_buffer_size);
      c_registry_id[i] =
          EEPROM.read(j + 2048 + 2 * int_project_info_buffer_size);
      c_device_id[i] = EEPROM.read(j + 2048 + 3 * int_project_info_buffer_size);
    }
    i++;
  }
  EEPROM.end();
  LOG->I(TAG, "GiotData initialized");
}

void GiotData::saveCa(String ca) {
  EEPROM.begin(16 * 1024);
  for (int i = 0; i <= ca.length(); i++) {
    if (i == int_ca_buffer_size) break;
    EEPROM.write(i + 1024, ca[i]);
    EEPROM.commit();
    c_ca[i] = ca[i];
  }
  LOG->I(TAG, "Saving new ca: " + ca);
  EEPROM.end();
}

void GiotData::saveProjectId(String project_id) {
  EEPROM.begin(16 * 1024);
  for (int i = 0; i <= project_id.length(); i++) {
    if (i == int_project_info_buffer_size) break;
    EEPROM.write(i + 1024 + 2048, project_id[i]);
    EEPROM.commit();
    c_project_id[i] = project_id[i];
  }
  LOG->I(TAG, "Saving new project id: " + project_id);
  EEPROM.end();
}

void GiotData::saveLocation(String location) {
  EEPROM.begin(16 * 1024);
  for (int i = 0; i <= location.length(); i++) {
    EEPROM.write(i + 1024 + 2048 + int_project_info_buffer_size, location[i]);
    EEPROM.commit();
    if (i == int_project_info_buffer_size) break;
  }
  LOG->I(TAG, "Saving new location: " + location);
  EEPROM.end();
}

void GiotData::saveRegistryId(String registry_id) {
  EEPROM.begin(16 * 1024);
  for (int i = 0; i <= registry_id.length(); i++) {
    if (i == int_project_info_buffer_size) break;
    EEPROM.write(i + 1024 + 2048 + 2 * int_project_info_buffer_size,
                 registry_id[i]);
    EEPROM.commit();
    c_registry_id[i] = registry_id[i];
  }
  LOG->I(TAG, "Saving new registry id: " + registry_id);
  EEPROM.end();
}

void GiotData::saveDeviceId(String device_id) {
  EEPROM.begin(16 * 1024);
  for (int i = 0; i <= device_id.length(); i++) {
    if (i == int_project_info_buffer_size) break;
    EEPROM.write(i + 1024 + 2048 + 3 * int_project_info_buffer_size,
                 device_id[i]);
    EEPROM.commit();
    c_device_id[i] = device_id[i];
  }
  LOG->I(TAG, "Saving new device id: " + device_id);
  EEPROM.end();
}

String GiotData::getSavedCa() {
  EEPROM.begin(16 * 1024);
  int i = 0;
  while (i <= int_ca_buffer_size) {
    c_ca[i] = EEPROM.read(i + 1024);
    i++;
  }
  String str_ca = String(c_ca);
  LOG->I(TAG, "Retrieving saved ca: " + str_ca);
  EEPROM.end();
  return str_ca;
}

String GiotData::getSavedProjectId() {
  EEPROM.begin(16 * 1024);
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_project_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  String str_project_id = String(c_project_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_project_id);
  EEPROM.end();
  return str_project_id;
}

String GiotData::getSavedLocation() {
  EEPROM.begin(16 * 1024);
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_location[i] = EEPROM.read(i + 1024 + 2048 + int_project_info_buffer_size);
    i++;
  }
  String str_location = String(c_location);
  LOG->I(TAG, "Retrieving saved project id: " + str_location);
  EEPROM.end();
  return str_location;
}

String GiotData::getSavedRegistryId() {
  EEPROM.begin(16 * 1024);
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_registry_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  String str_registry_id = String(c_registry_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_registry_id);
  EEPROM.end();
  return str_registry_id;
}

String GiotData::getSavedDeviceId() {
  EEPROM.begin(16 * 1024);
  int i = 0;
  while (i <= int_project_info_buffer_size) {
    c_device_id[i] = EEPROM.read(i + 1024 + 2048);
    i++;
  }
  String str_device_id = String(c_device_id);
  LOG->I(TAG, "Retrieving saved project id: " + str_device_id);
  EEPROM.end();
  return str_device_id;
}

GiotData* GiotData::instance = 0;

GiotData* GiotData::getInstance() {
  if (!instance) instance = new GiotData();
  return instance;
}