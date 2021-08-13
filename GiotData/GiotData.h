#ifndef GIOTDATA_H
#define GIOTDATA_H

#include <Arduino.h>
#include <DataManager.h>
#include <Log.h>

class GiotData {
 public:
  static GiotData *getInstance();
  void saveCa(String ca);
  void saveProjectId(String project_id);
  void saveLocation(String location);
  void saveRegistryId(String registry_id);
  void saveDeviceId(String device_id);
  String getSavedCa();
  String getSavedProjectId();
  String getSavedLocation();
  String getSavedRegistryId();
  String getSavedDeviceId();

 private:
  GiotData();
  static const inline String TAG = "GiotData";
  static const inline int int_ca_buffer_size =
      2048;  // maximum ssl certificate size
  static const inline int int_project_info_buffer_size =
      128;  // maximum project info size
  static inline Log *LOG = Log::getInstance();
  static GiotData *instance;
  static inline DataManager *dm = DataManager::getInstance();
};
#endif