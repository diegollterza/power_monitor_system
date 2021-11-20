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
  static const inline int CA_BUFFER_SIZE =
      2048;  // maximum ssl certificate size
  static const inline int BUFFER_SIZE =
      128;  // maximum project info size
  char ca[CA_BUFFER_SIZE];
  char project_id[BUFFER_SIZE];
  char location[BUFFER_SIZE];
  char registry_id[BUFFER_SIZE];
  char device_id[BUFFER_SIZE];
  char private_key[BUFFER_SIZE];
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