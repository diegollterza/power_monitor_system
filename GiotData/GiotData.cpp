#include <GiotData.h>

GiotData::GiotData() { log->I(TAG, "GiotData initialized"); }

void GiotData::saveCa(String ca) {
  log->I(TAG, "Saving new CA");
  char c_ca[ca_buffer_size];
  ca.toCharArray(c_ca, ca_buffer_size);
  dm->saveData(1024, ca_buffer_size, c_ca);
}

void GiotData::saveProjectId(String project_id) {
  log->I(TAG, "Saving new project id " + project_id);
  char c_project_id[project_info_buffer_size];
  project_id.toCharArray(c_project_id, project_info_buffer_size);
  dm->saveData(2048, project_info_buffer_size, c_project_id);
}

void GiotData::saveLocation(String location) {
  log->I(TAG, "Saving new location " + location);
  char c_location[project_info_buffer_size];
  location.toCharArray(c_location, project_info_buffer_size);
  dm->saveData(2048 + project_info_buffer_size,
               project_info_buffer_size, c_location);
}

void GiotData::saveRegistryId(String registry_id) {
  log->I(TAG, "Saving new registry id " + registry_id);
  char c_registry_id[project_info_buffer_size];
  registry_id.toCharArray(c_registry_id, project_info_buffer_size);
  dm->saveData(2048 + 2 * project_info_buffer_size,
               project_info_buffer_size, c_registry_id);
}

void GiotData::saveDeviceId(String device_id) {
  log->I(TAG, "Saving new device id " + device_id);
  char c_device_id[project_info_buffer_size];
  device_id.toCharArray(c_device_id, project_info_buffer_size);
  dm->saveData(2048 + 3 * project_info_buffer_size,
               project_info_buffer_size, c_device_id);
}

void GiotData::savePrivateKey(String private_key) {
  log->I(TAG, "Saving new private key");
  char c_private_key[project_info_buffer_size];
  private_key.toCharArray(c_private_key, project_info_buffer_size);
  dm->saveData(2048 + 4 * project_info_buffer_size,
               project_info_buffer_size, c_private_key);
}

void GiotData::getSavedCa(char **ca) {
  log->I(TAG, "Retrieving saved ca");
  *ca = (char *)malloc(ca_buffer_size);
  dm->readData(1024, ca_buffer_size, *ca);
}

void GiotData::getSavedProjectId(char **project_id) {
  *project_id = (char *)malloc(project_info_buffer_size);
  dm->readData(2048, project_info_buffer_size, *project_id);
  log->I(TAG, "Retrieved saved ca");
}
void GiotData::getSavedLocation(char **location) {
  *location = (char *)malloc(project_info_buffer_size);
  dm->readData(2048 + project_info_buffer_size,
               project_info_buffer_size, *location);
  log->I(TAG, "Retrieved saved location: " + String(**location));
}

void GiotData::getSavedRegistryId(char **registry_id) {
  *registry_id = (char *)malloc(project_info_buffer_size);
  dm->readData(2048 + 2 * project_info_buffer_size,
               project_info_buffer_size, *registry_id);
  log->I(TAG, "Retrieved saved registry id: " + String(**registry_id));
}

void GiotData::getSavedDeviceId(char **device_id) {
  *device_id = (char *)malloc(project_info_buffer_size);
  dm->readData(2048 + 3 * project_info_buffer_size,
               project_info_buffer_size, *device_id);
  log->I(TAG, "Retrieved saved device id: " + String(**device_id));
}
void GiotData::getSavedPrivateKey(char **private_key) {
  *private_key = (char *)malloc(project_info_buffer_size);
  dm->readData(2048 + 4 * project_info_buffer_size,
               project_info_buffer_size, *private_key);
  log->I(TAG, "Retrieved saved private key");
}

GiotData *GiotData::instance = 0;

GiotData *GiotData::getInstance() {
  if (!instance) instance = new GiotData();
  return instance;
}