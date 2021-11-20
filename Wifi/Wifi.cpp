#include <Wifi.h>

Wifi::Wifi() {
  espClient = new WiFiClient();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

bool Wifi::connect() {
  if (WiFi.status() == WL_CONNECTED) {
    log->I(TAG, "Wifi already connected, no action to be done");
  }

  String ssid = wifidata->getSavedSsid();
  String password = wifidata->getSavedPassword();
  WiFi.begin(ssid, password);
  log->I(TAG, "Trying to connect to SSID: " + ssid);
  unsigned long time = millis();

  while (WiFi.status() != WL_CONNECTED) {
    yield();
    if (millis() - time > TIMEOUT) {
      log->E(TAG,
             "Could not connect to wifi. Error code: " + String(WiFi.status()));
      return false;
    }
  }
  log->I(TAG, "Connected succesfully to SSID: " + ssid);
  log->I(TAG, "Connection info: IP=" + WiFi.localIP().toString() +
                  " rssi=" + WiFi.RSSI());
  digitalWrite(LED_BUILTIN, LOW);
  configureWebTime();
  return true;
}

void Wifi::configureWebTime() {
  log->I(TAG, "Synchronizing time with internet.");
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 1510644967) delay(100);
}

void Wifi::disconnect() {
  WiFi.disconnect();
  log->I(TAG, "Disconnected from wifi");
  digitalWrite(LED_BUILTIN, HIGH);
}

bool Wifi::isConnected() {
  bool isConn = WiFi.isConnected();
  log->I(TAG, "Is connected: " + String(isConn));
  return isConn;
}

void Wifi::setSsid(String ssid) {
  log->I(TAG, "Set ssid:" + ssid);
  wifidata->saveSsid(ssid);
}

void Wifi::setPassword(String password) {
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