#include "user/user.h"

#include "core/logger.h"

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define SD_CS 1 // Chip Select

void SDCardSetup() {
    if(!SD.begin(SD_CS)) {
        Logger::error("SD Card initialization failed!");
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
    }
    void loop() {
        // User loop code here
    }
} // namespace user
