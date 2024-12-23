#include "MQTT_credentials.h"
#include <esp_log.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <stdlib.h> // For random number generation
#include "../certs.h"
#include "../Logger/Logger.h"

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

            // Los datos del payload tienen este formato: {"mqtt":{"user":"26865","pass":"i51DFm0dc","server":"mqtt.test.tinygs.com","port":8855}} guárda cada valor en una variable. AI!

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