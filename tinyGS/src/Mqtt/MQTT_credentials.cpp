#include "MQTT_credentials.h"
#include <esp_log.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <stdlib.h> // For random number generation
#include "../certs.h"
#include "../Logger/Logger.h"
#include <ArduinoJson.h>

#define API_URL "https://api.test.tinygs.com/credentials?otp="

const time_t CHECKEVERY = 15000;
time_t httpLastChecked = 10000;
int randomCode;
String url;

void generateRandomCode () {
    randomCode = 100000 + (rand () % 900000);
    Serial.printf ("Generated OTP: %d\n", randomCode);
    url = String (API_URL) + String (randomCode);
}

bool fetchCredentials () {
    time_t now = millis ();
    if (now > httpLastChecked + CHECKEVERY) {
        httpLastChecked = now;
        Log::console ("Fetching URL: %s", url.c_str ());

        HTTPClient http;
        http.begin (url, ISRGroot_CA);
        int httpResponseCode = http.GET ();

        if (httpResponseCode == 200) {
            String payload = http.getString ();
            Log::console ("Received 200 OK, payload: %s", payload.c_str ());

            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                Log::console("deserializeJson() failed: %s", error.c_str());
                http.end();
                return false;
            }

            const char* user = doc["mqtt"]["user"];
            const char* pass = doc["mqtt"]["pass"];
            const char* server = doc["mqtt"]["server"];
            int port = doc["mqtt"]["port"];

            Log::console("MQTT User: %s", user);
            Log::console("MQTT Pass: %s", pass);
            Log::console("MQTT Server: %s", server);
            Log::console("MQTT Port: %d", port);

            http.end ();
            return true;
        } else {
            Log::console ("Received status code: %d", httpResponseCode);
            http.end ();
            return false;
        }
    }
    return false;
}
    
// bool getMqttData () {
// // Existing logic for getting MQTT data
//     ESP_LOGI (LOG_TAG, "Getting MQTT data");
//     xTaskCreate (generateAndFetchCredentialsTask, "generateAndFetchCredentialsTask", 4096, NULL, 5, NULL);
//     while (taskRunning) {
//         delay (1000);
//     }
//     Serial.println ("Task completed");
//     return true; // Placeholder
// }
