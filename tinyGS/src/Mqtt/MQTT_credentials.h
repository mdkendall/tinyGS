#ifndef MQTT_CREDENTIALS_H
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define LOG_TAG "MQTT_CRED"

#include "../ConfigManager/ConfigManager.h"
#include "../Status.h"

//bool getMqttData ();
String fetchCredentials ();
void generateRandomCode ();

#endif // MQTT_CREDENTIALS_H