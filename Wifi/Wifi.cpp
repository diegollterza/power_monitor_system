#include <Wifi.h>

Wifi::Wifi() {
  ssid = wifidata->getSavedSsid();
  password = wifidata->getSavedPassword();
  espClient = new WiFiClient();
  this->max_try = 50;  // 5 seconds max try
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  LOG->I(TAG, "Wifi initialized");
}

bool Wifi::connect() {
  if (WiFi.status() == WL_CONNECTED) {
    LOG->I(TAG, "Wifi already connected, no action to be done");
  }

  WiFi.begin(ssid, password);
  int i = 0;
  LOG->I(TAG, "Trying to connect to SSID: " + ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    i++;
    if (i == max_try) {
      LOG->E(TAG, "Couldn't connect to SSID: " + ssid);
      return false;
    }
  }
  LOG->I(TAG, "Connected succesfully to SSID: " + ssid);
  LOG->I(TAG, "Connection info: IP=" + WiFi.localIP().toString() +
                  " rssi=" + WiFi.RSSI());
  digitalWrite(LED_BUILTIN, LOW);
  return true;
}

void Wifi::disconnect() {
  WiFi.disconnect();
  LOG->I(TAG, "Disconnected from ssid:" + ssid);
  digitalWrite(LED_BUILTIN, HIGH);
}


bool Wifi::isConnected() {
  bool isConn = WiFi.isConnected();
  LOG->I(TAG, "Is connected: " + String(isConn));
  return isConn;
}

void Wifi::setSsid(String ssid) {
  String old_ssid = this->ssid;
  this->ssid = ssid;
  LOG->I(TAG, "Set ssid:" + ssid);
  wifidata->saveSsid(ssid);
}

void Wifi::setPassword(String password) {
  this->password = password;
  LOG->I(TAG, "Set password");
  LOG->D(TAG, "Password set to " + password);
  wifidata->savePassword(password);
}

Wifi* Wifi::instance = 0;

Wifi* Wifi::getInstance() {
  if (instance == 0) {
    instance = new Wifi();
  }
  return instance;
}