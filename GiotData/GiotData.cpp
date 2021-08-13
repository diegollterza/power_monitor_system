#include <GiotData.h>

GiotData::GiotData() { LOG->I(TAG, "GiotData initialized"); }

void GiotData::saveCa(String ca) {
  char c_ca[int_ca_buffer_size];
  ca.toCharArray(c_ca, int_ca_buffer_size);
  dm->saveData(1024, int_ca_buffer_size, c_ca);
}

void GiotData::saveProjectId(String project_id) {
  char c_project_id[int_project_info_buffer_size];
  project_id.toCharArray(c_project_id, int_project_info_buffer_size);
  dm->saveData(2048, int_project_info_buffer_size, c_project_id);
}

void GiotData::saveLocation(String location) {
  char c_location[int_project_info_buffer_size];
  location.toCharArray(c_location, int_project_info_buffer_size);
  dm->saveData(2048 + int_project_info_buffer_size,
               int_project_info_buffer_size, c_location);
}

void GiotData::saveRegistryId(String registry_id) {
  char c_registry_id[int_project_info_buffer_size];
  registry_id.toCharArray(c_registry_id, int_project_info_buffer_size);
  dm->saveData(2048 + 2 * int_project_info_buffer_size,
               int_project_info_buffer_size, c_registry_id);
}

void GiotData::saveDeviceId(String device_id) {
  char c_device_id[int_project_info_buffer_size];
  device_id.toCharArray(c_device_id, int_project_info_buffer_size);
  dm->saveData(2048 + 3 * int_project_info_buffer_size,
               int_project_info_buffer_size, c_device_id);
}

String GiotData::getSavedCa() {
  char c_ca[int_ca_buffer_size];
  dm->readData(1024, int_ca_buffer_size, c_ca);
  return String(c_ca);
}

String GiotData::getSavedProjectId() {
  char c_project_id[int_project_info_buffer_size];
  dm->readData(2048,
               int_project_info_buffer_size, c_project_id);
  return String(c_project_id);
}

String GiotData::getSavedLocation() {
  char c_location[int_project_info_buffer_size];
  dm->readData(2048 + int_project_info_buffer_size,
               int_project_info_buffer_size, c_location);
  return String(c_location);
}

String GiotData::getSavedRegistryId() {
  char c_registry_id[int_project_info_buffer_size];
  dm->readData(2048 + 2*int_project_info_buffer_size,
               int_project_info_buffer_size, c_registry_id);
  return String(c_registry_id);
}

String GiotData::getSavedDeviceId() {
  char device_id[int_project_info_buffer_size];
  dm->readData(2048 + 3*int_project_info_buffer_size,
               int_project_info_buffer_size, device_id);
  return String(device_id);
}

GiotData* GiotData::instance = 0;

GiotData* GiotData::getInstance() {
  if (!instance) instance = new GiotData();
  return instance;
}