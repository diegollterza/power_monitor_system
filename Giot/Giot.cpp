#include <Giot.h>

Giot::Giot() { setupCloudIoT(); }

void Giot::setupCloudIoT() {
  // Cloud iot details.
  const char* project_id = "smart-outlet-320623";
  const char* location = "us-central1";
  const char* registry_id = "iotcore-registry";
  const char* device_id = "esp8266";
  const unsigned char private_key[] = {
      0x18, 0x37, 0xbb, 0xea, 0x13, 0xa5, 0x60, 0x56, 0xd1, 0xbc, 0x15,
      0x78, 0x2b, 0xa4, 0xb3, 0x79, 0xc5, 0x09, 0x90, 0xb8, 0x70, 0xfc,
      0x41, 0x3a, 0x57, 0x3a, 0xc1, 0xd2, 0xf6, 0xa0, 0x48, 0x14};

  // Certificates for SSL on the LTS server
  const char* ca =
      "-----BEGIN CERTIFICATE-----\n"
      "MIIBxTCCAWugAwIBAgINAfD3nVndblD3QnNxUDAKBggqhkjOPQQDAjBEMQswCQYD\n"
      "VQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzERMA8G\n"
      "A1UEAxMIR1RTIExUU1IwHhcNMTgxMTAxMDAwMDQyWhcNNDIxMTAxMDAwMDQyWjBE\n"
      "MQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExM\n"
      "QzERMA8GA1UEAxMIR1RTIExUU1IwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAATN\n"
      "8YyO2u+yCQoZdwAkUNv5c3dokfULfrA6QJgFV2XMuENtQZIG5HUOS6jFn8f0ySlV\n"
      "eORCxqFyjDJyRn86d+Iko0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUw\n"
      "AwEB/zAdBgNVHQ4EFgQUPv7/zFLrvzQ+PfNA0OQlsV+4u1IwCgYIKoZIzj0EAwID\n"
      "SAAwRQIhAPKuf/VtBHqGw3TUwUIq7TfaExp3bH7bjCBmVXJupT9FAiBr0SmCtsuk\n"
      "miGgpajjf/gFigGM34F9021bCWs1MbL0SA==\n"
      "-----END CERTIFICATE-----\n";

  device = new CloudIoTCoreDevice(project_id, location, registry_id, device_id);

  certList.append(ca);
  // certList.append(backup_ca);
  netClient.setTrustAnchors(&certList);

  device->setPrivateKey(private_key);

  mqttClient = new MQTTClient(512);
  mqttClient->setOptions(180, true, 1000);  // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, &netClient, device);
  mqtt->setUseLts(true);
  mqtt->startMQTTAdvanced();  // Opens connection using advanced callback
}

bool Giot::publishTelemetry(String data) {
  return mqtt->publishTelemetry(data);
}

bool Giot::isConnected() {
  bool isConnected = mqttClient->connected();
  log->I(TAG, "Is connected: " + String(isConnected));
  return isConnected;
}

String getJwt() {
  Giot* giot = Giot::getInstance();
  return giot->getJwt();
}

String Giot::getJwt() {
  // Disable software watchdog as these operations can take a while.
  ESP.wdtDisable();
  time_t iat = time(nullptr);
  Serial.println("Refreshing JWT");
  String jwt = device->createJWT(iat, jwt_exp_secs);
  ESP.wdtEnable(0);
  return jwt;
}

void Giot::connect() {
  if (!mqtt->loop()) {
    mqtt->mqttConnect();
  }
}

void Giot::setCa(String ca) {
  log->I(TAG, "Set new CA");
  giotdata->saveCa(ca);
}

void Giot::setProjectId(String project_id) {
  log->I(TAG, "Set new project id " + project_id);
  giotdata->saveProjectId(project_id);
}

void Giot::setLocation(String location) {
  log->I(TAG, "Set new location " + location);
  giotdata->saveLocation(location);
}

void Giot::setRegistryId(String registry_id) {
  log->I(TAG, "Set new registry id " + registry_id);
  giotdata->saveRegistryId(registry_id);
}

void Giot::setDeviceId(String device_id) {
  log->I(TAG, "Set new device id " + device_id);
  giotdata->saveDeviceId(device_id);
}

void Giot::setPrimaryKey(String private_key) {
  log->I(TAG, "Set new primary key");
  giotdata->savePrivateKey(private_key);
}

Giot* Giot::instance = 0;

Giot* Giot::getInstance() {
  if (!instance) instance = new Giot();
  return instance;
}

// this isn't used now since we don't receive messages
void messageReceivedAdvanced(MQTTClient* client, char topic[], char bytes[],
                             int length) {}