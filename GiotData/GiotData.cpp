#include <GiotData.h>

GiotData::GiotData() {}

void GiotData::saveCa(String ca) {
  log->I(TAG, "Saving new CA");
  dm->saveData(1024, ca_buffer_size, ca);
}

void GiotData::saveProjectId(String project_id) {
  log->I(TAG, "Saving new project id " + project_id);
  dm->saveData(2048, project_info_buffer_size, project_id);
}

void GiotData::saveLocation(String location) {
  log->I(TAG, "Saving new location " + location);
  dm->saveData(2048 + project_info_buffer_size, project_info_buffer_size,
               location);
}

void GiotData::saveRegistryId(String registry_id) {
  log->I(TAG, "Saving new registry id " + registry_id);
  dm->saveData(2048 + 2 * project_info_buffer_size, project_info_buffer_size,
               registry_id);
}

void GiotData::saveDeviceId(String device_id) {
  log->I(TAG, "Saving new device id " + device_id);
  dm->saveData(2048 + 3 * project_info_buffer_size, project_info_buffer_size,
               device_id);
}

void GiotData::savePrivateKey(String private_key) {
  log->I(TAG, "Saving new private key");
  dm->saveData(2048 + 4 * project_info_buffer_size, project_info_buffer_size,
               private_key);
}

String GiotData::getSavedCa() {
  log->I(TAG, "Retrieving saved ca");
  return dm->readData(1024, ca_buffer_size);
}

String GiotData::getSavedProjectId() {
  return dm->readData(2048, project_info_buffer_size);
}
String GiotData::getSavedLocation() {
  return dm->readData(2048 + project_info_buffer_size,
                      project_info_buffer_size);
}

String GiotData::getSavedRegistryId() {
  return dm->readData(2048 + 2 * project_info_buffer_size,
                      project_info_buffer_size);
}

String GiotData::getSavedDeviceId() {
  return dm->readData(2048 + 3 * project_info_buffer_size,
                      project_info_buffer_size);
}
String GiotData::getSavedPrivateKey() {
  return dm->readData(2048 + 4 * project_info_buffer_size,
                      project_info_buffer_size);
}

GiotData *GiotData::instance = 0;

GiotData *GiotData::getInstance() {
  if (!instance) instance = new GiotData();
  return instance;
}