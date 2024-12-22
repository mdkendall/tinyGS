#include "MQTT_credentials.h"

#include <esp_log.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <stdlib.h> // For random number generation

#define API_URL "https://api.tinygs.com/credentials?otp="

bool getMqttData () {
    // Existing logic for getting MQTT data
    ESP_LOGI(LOG_TAG, "Getting MQTT data");
    return true; // Placeholder
}

void generateAndFetchCredentialsTask(void * parameter) {
    while(true) {
        // Generate a 6-digit random code
        int randomCode = 100000 + (rand() % 900000);
        ESP_LOGI(LOG_TAG, "Generated OTP: %d", randomCode);

        // Construct the URL
        String url = String(API_URL) + String(randomCode);
        ESP_LOGI(LOG_TAG, "Fetching URL: %s", url.c_str());

        HTTPClient http;
        http.begin(url);
        int httpResponseCode = http.GET();

        if (httpResponseCode == 200) {
            String payload = http.getString();
            ESP_LOGI(LOG_TAG, "Received 200 OK, payload: %s", payload.c_str());
            // Process the payload here if needed
            http.end();
            break; // Exit the loop when a 200 is received
        } else {
            ESP_LOGI(LOG_TAG, "Received status code: %d", httpResponseCode);
            http.end();
        }
        delay(1000); // Wait for a second before retrying
    }
    vTaskDelete(NULL); // Delete the task after successful execution
}
