#include <Wifi.h>

Wifi::Wifi() {
  espClient = new WiFiClient();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void Wifi::getDataFromEeprom() {
  log->I(TAG, "Retrieving data from EEPROM");
  ssid = wifidata->getSavedSsid();
  password = wifidata->getSavedPassword();
}

bool Wifi::connect() {
  if (WiFi.status() == WL_CONNECTED) {
    log->I(TAG, "Wifi already connected, no action to be done");
  }

  getDataFromEeprom();

  WiFi.begin(ssid, password);
  log->I(TAG, "Trying to connect to SSID: " + ssid);
  unsigned long time = millis();

  while (WiFi.status() != WL_CONNECTED) {
    yield();
    if (millis() - time > TIMEOUT) {
      log->E(TAG, "Could not connect to wifi. Error code: " + String(WiFi.status()));
      return false;
    }
  }
  log->I(TAG, "Connected succesfully to SSID: " + ssid);
  log->I(TAG, "Connection info: IP=" + WiFi.localIP().toString() +
                  " rssi=" + WiFi.RSSI());
  digitalWrite(LED_BUILTIN, LOW);
  return true;
}

void Wifi::disconnect() {
  WiFi.disconnect();
  log->I(TAG, "Disconnected from ssid:" + ssid);
  digitalWrite(LED_BUILTIN, HIGH);
}

bool Wifi::isConnected() {
  bool isConn = WiFi.isConnected();
  log->I(TAG, "Is connected: " + String(isConn));
  return isConn;
}

void Wifi::setSsid(String ssid) {
  String old_ssid = this->ssid;
  this->ssid = ssid;
  log->I(TAG, "Set ssid:" + ssid);
  wifidata->saveSsid(ssid);
}

void Wifi::setPassword(String password) {
  this->password = password;
  log->I(TAG, "Set password");
  log->D(TAG, "Password set to " + password);
  wifidata->savePassword(password);
}

Wifi* Wifi::instance = 0;

Wifi* Wifi::getInstance() {
  if (instance == 0) {
    instance = new Wifi();
  }
  return instance;
}