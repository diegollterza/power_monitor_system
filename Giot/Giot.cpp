#include <Giot.h>

Giot::Giot() {
  getDataFromEeprom();
  device = new CloudIoTCoreDevice(project_id, location, registry_id, device_id);
  setupCertAndPrivateKey();
  mqttClient = new MQTTClient(512);
  mqttClient->setOptions(180, true, 1000);  // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, &netClient, device);
  mqtt->setUseLts(true);
  mqtt->startMQTTAdvanced();  // Opens connection using advanced callback
}

void Giot::getDataFromEeprom() {
/*   log->I(TAG, "Retrieving data from EEPROM");
  giotdata->getSavedCa();
  giotdata->getSavedProjectId();
  giotdata->getSavedLocation();
  giotdata->getSavedRegistryId();
  giotdata->getSavedDeviceId();
  giotdata->getSavedPrivateKey(); */
}

void Giot::setCa(String ca) {
  log->I(TAG, "Set new CA");
  ca.toCharArray(this->ca, sizeof(ca));
  giotdata->saveCa(ca);
}

void Giot::setProjectId(String project_id) {
  log->I(TAG, "Set new project id " + project_id);
  project_id.toCharArray(this->project_id, sizeof(project_id));
  giotdata->saveProjectId(project_id);
}

void Giot::setLocation(String location) {
  log->I(TAG, "Set new location " + location);
  location.toCharArray(this->location, sizeof(location));
  giotdata->saveLocation(location);
}

void Giot::setRegistryId(String registry_id) {
  log->I(TAG, "Set new registry id " + registry_id);
  registry_id.toCharArray(this->registry_id, sizeof(registry_id));
  giotdata->saveRegistryId(registry_id);
}

void Giot::setDeviceId(String device_id) {
  log->I(TAG, "Set new device id " + device_id);
  device_id.toCharArray(this->device_id, sizeof(device_id));
  giotdata->saveDeviceId(device_id);
}

void Giot::setPrimaryKey(String private_key) {
  log->I(TAG, "Set new primary key");
  private_key.toCharArray(this->private_key, sizeof(private_key));
  giotdata->savePrivateKey(private_key);
}
void Giot::setupCertAndPrivateKey() {
  certList.append(ca);
  netClient.setTrustAnchors(&certList);
  device->setPrivateKey(private_key);
  return;
}

Giot *Giot::instance = 0;

Giot *Giot::getInstance() {
  if (!instance) instance = new Giot();
  return instance;
}

//this isn't used now since we don't receive messages
void messageReceivedAdvanced(MQTTClient *client, char topic[], char bytes[],
                             int length) {}