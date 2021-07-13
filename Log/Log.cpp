#include "Arduino.h"
#include "Log.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

Log::Log(NTPClient *timeClient)
{
  this->timeClient = timeClient;
}

void Log::E(String TAG, String logMessage)
{
  timeClient->update();
  Serial.println(timeClient->getFormattedTime() + " E " + TAG + ": " + logMessage);
}

void Log::I(String TAG, String logMessage)
{
  timeClient->update();
  Serial.println(timeClient->getFormattedTime() + " I " + TAG + ": " + logMessage);
}