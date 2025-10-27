#include "user/user.h"

#include "core/logger.h"
#include "esp_camera.h"
#include "user/camera.h"

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <string>
#include <vector>

#define SD_CS 21 // Chip Select

user::Camera camera;

std::string  base64Encode(const unsigned char *data, size_t len) {
    static const char table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
     "abcdefghijklmnopqrstuvwxyz"
     "0123456789+/";

    std::string encoded;
    encoded.reserve(((len + 2) / 3) * 4); // pre-allocate

    for(size_t i = 0; i < len; i += 3) {
        unsigned int octet_a = i < len ? data[i] : 0;
        unsigned int octet_b = (i + 1) < len ? data[i + 1] : 0;
        unsigned int octet_c = (i + 2) < len ? data[i + 2] : 0;

        unsigned int triple  = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded.push_back(table[(triple >> 18) & 0x3F]);
        encoded.push_back(table[(triple >> 12) & 0x3F]);
        encoded.push_back((i + 1) < len ? table[(triple >> 6) & 0x3F] : '=');
        encoded.push_back((i + 2) < len ? table[triple & 0x3F] : '=');
    }

    return encoded;
}

void SDCardSetup() {
    if(!SD.begin(SD_CS)) {
        Logger::error("SD Card initialization failed! ");
        return;
    }

    Logger::info("SD Card initialized.");

    // List root directory
    File root = SD.open("/");
    while(true) {
        File entry = root.openNextFile();
        if(!entry) break;

        Serial.print(entry.name());
        Serial.print("  ");
        Serial.println(entry.size());
    }

    // Write test file
    File myFile = SD.open("/test.txt", FILE_WRITE);
    myFile.println("Hello from ESP32-S3!");
    myFile.close();
}

namespace user {
    void init() {
        SDCardSetup();
        camera.init();
    }
    void loop() {
        // User loop code here
        camera_fb_t *fb = esp_camera_fb_get();

        if(!fb) {
            Logger::error("Failed to get camera frame buffer");
            return;
        }

        Serial.write(base64Encode(fb->buf, fb->len).c_str());

        esp_camera_fb_return(fb);
        delay(15000);
    }
} // namespace user
