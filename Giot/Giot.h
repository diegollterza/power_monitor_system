#ifndef GIOT_H
#define GIOT_H

#include <Arduino.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
#include <GiotData.h>
#include <Log.h>
#include <MQTT.h>
// #include <time.h>

#include "WiFiClientSecureBearSSL.h"

class Giot {
 public:
  static Giot *getInstance();
  void setCa(String ca);
  void setProjectId(String project_id);
  void setLocation(String location);
  void setRegistryId(String registry_id);
  void setDeviceId(String device_id);
  void setPrimaryKey(String primary_key);

 private:
  Giot();
  void getDataFromEeprom();
  void initializeDevice();
  static Giot *instance;
  static const inline String TAG = "Giot";
  char *ca;
  char *project_id;
  char *location;
  char *registry_id;
  char *device_id;
  char *private_key;
  static const inline int int_ca_buffer_size =
      2048;  // maximum ssl certificate size
  static const inline int int_project_info_buffer_size =
      128;  // maximum project info size
  static inline Log *log = Log::getInstance();
  static inline GiotData *giotdata = GiotData::getInstance();
  MQTTClient *mqttClient;
  BearSSL::WiFiClientSecure netClient;
  BearSSL::X509List certList;
  CloudIoTCoreDevice *device;
  CloudIoTCoreMqtt *mqtt;
  void setupCertAndPrivateKey();
};

#endif