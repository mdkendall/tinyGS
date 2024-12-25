#include "MQTT_credentials.h"
#include <esp_log.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <stdlib.h> // For random number generation
#include "../certs.h"
#include "../Logger/Logger.h"
#include <ArduinoJson.h>

#ifdef TEST_API
const char* API_URL = "https://api.test.tinygs.com/credentials?otp=";
#else
const char* API_URL = "https://api.tinygs.com/credentials?otp=";
#endif

const time_t CHECKEVERY = 15000;
time_t httpLastChecked = 10000;
int randomCode;
String url;

void generateRandomCode () {
    char randomCode[7];
    sprintf (randomCode, "%06ld", random (0, 1000000));
    Log::console ("Generated OTP: %s", randomCode);
    url = String (API_URL) + randomCode;
}

String fetchCredentials () {
    time_t now = millis ();
    if (now > httpLastChecked + CHECKEVERY) {
        httpLastChecked = now;
        Log::debug ("Fetching URL: %s", url.c_str ());
        Log::console("Trying to get MQTT credentials");

        HTTPClient http;
        http.begin (url, ISRGroot_CA);
        int httpResponseCode = http.GET ();

        if (httpResponseCode == 200) {
            String payload = http.getString ();
            Log::debug ("Received 200 OK, payload: %s", payload.c_str ());
            http.end ();
            return payload;
        } else {
            Log::debug ("Received status code: %d", httpResponseCode);
            http.end ();
            return "";
        }
    }
    return "";
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
