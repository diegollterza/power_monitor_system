#ifndef GIOT_H
#define GIOT_H

#include <Arduino.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
#include <GiotData.h>
#include <Log.h>
#include <MQTT.h>
#include <Wifi.h>

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
  bool publishTelemetry(String data);
  bool isConnected();
  void connect();
  String getJwt();

 private:
  Giot();
  void initializeDevice();
  void setupCloudIoT();
  void setStaticProject();
  static Giot *instance;
  static const inline int jwt_exp_secs = 3600;
  static const inline String TAG = "Giot";
  static inline Log *log = Log::getInstance();
  static inline GiotData *giotdata = GiotData::getInstance();
  static inline Wifi *wifi = Wifi::getInstance();
  MQTTClient *mqttClient;
  BearSSL::WiFiClientSecure netClient;
  BearSSL::X509List certList;
  CloudIoTCoreDevice *device;
  CloudIoTCoreMqtt *mqtt;
  void setupCertAndPrivateKey();
};

#endif