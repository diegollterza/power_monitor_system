#ifndef GIOTDATA_H
#define GIOTDATA_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Log.h>

class GiotData {
 public:
  GiotData(Log *LOG);
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
  String str_ca;
  static const inline String TAG = "GiotData";
  Log *LOG;
  static const inline int int_ca_buffer_size =
      2048;  // maximum ssl certificate size
  static const inline int int_project_info_buffer_size =
      128;  // maximum project info size
  String str_project_id;
  String str_location;
  String str_registry_id;
  String str_device_id;
};
#endif