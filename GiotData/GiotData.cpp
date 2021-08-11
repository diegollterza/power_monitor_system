#include <GiotData.h>

GiotData::GiotData() {
  c_ca = dm->readData(1024, int_ca_buffer_size);
  c_project_id = dm->readData(2048, int_project_info_buffer_size);
  c_location = dm->readData(2048 + int_project_info_buffer_size,
                            int_project_info_buffer_size);
  c_registry_id = dm->readData(2048 + 2 * int_project_info_buffer_size,
                               int_project_info_buffer_size);
  c_device_id = dm->readData(2048 + 3 * int_project_info_buffer_size,
                             int_project_info_buffer_size);
  LOG->I(TAG, "GiotData initialized");
}

void GiotData::saveCa(String ca) {
  char* c_ca;
  ca.toCharArray(c_ca, int_ca_buffer_size);
  dm->saveData(1024, int_ca_buffer_size, c_ca);
}

void GiotData::saveProjectId(String project_id) {
  char* c_project_id;
  project_id.toCharArray(c_project_id, int_project_info_buffer_size);
  dm->saveData(2048, int_project_info_buffer_size, c_project_id);
}

void GiotData::saveLocation(String location) {
  char* c_location;
  location.toCharArray(c_location, int_project_info_buffer_size);
  dm->saveData(2048 + int_project_info_buffer_size,
               int_project_info_buffer_size, c_location);
}

void GiotData::saveRegistryId(String registry_id) {
  char* c_registry_id;
  registry_id.toCharArray(c_registry_id, int_project_info_buffer_size);
  dm->saveData(2048 + 2 * int_project_info_buffer_size,
               int_project_info_buffer_size, c_registry_id);
}

void GiotData::saveDeviceId(String device_id) {
  char* c_device_id;
  device_id.toCharArray(c_device_id, int_project_info_buffer_size);
  dm->saveData(2048 + 3 * int_project_info_buffer_size,
               int_project_info_buffer_size, c_device_id);
}

String GiotData::getSavedCa() {
  return String(dm->readData(1024, int_ca_buffer_size));
}

String GiotData::getSavedProjectId() {
  return String(dm->readData(2048, int_project_info_buffer_size));
}

String GiotData::getSavedLocation() {
  return String(dm->readData(2048 + int_project_info_buffer_size, int_project_info_buffer_size));
}

String GiotData::getSavedRegistryId() {
  return String(dm->readData(2048 + 2*int_project_info_buffer_size, int_project_info_buffer_size));
}

String GiotData::getSavedDeviceId() {
  return String(dm->readData(2048 + 3*int_project_info_buffer_size, int_project_info_buffer_size));
}

GiotData* GiotData::instance = 0;

GiotData* GiotData::getInstance() {
  if (!instance) instance = new GiotData();
  return instance;
}