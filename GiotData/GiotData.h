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
  void savePrivateKey(String private_key);
  void getSavedCa(char **ca);
  void getSavedProjectId(char **project_id);
  void getSavedLocation(char **location);
  void getSavedRegistryId(char **registry_id);
  void getSavedDeviceId(char **device_id);
  void getSavedPrivateKey(char **private_key);

 private:
  GiotData();
  static const inline String TAG = "GiotData";
  static const inline int ca_buffer_size =
      2048;  // maximum ssl certificate size
  static const inline int project_info_buffer_size =
      128;  // maximum project info size
  static inline Log *log = Log::getInstance();
  static GiotData *instance;
  static inline DataManager *dm = DataManager::getInstance();
};
#endif