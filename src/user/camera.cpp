#include "user/camera.h"

#include "SD.h"
#include "SPI.h"
#include "core/filesystem.h"
#include "core/logger.h"
#include "esp_camera.h"

#include <Arduino.h>

// camera pins for xiao esp32s3
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39

#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    11
#define Y7_GPIO_NUM    12
#define Y6_GPIO_NUM    14
#define Y5_GPIO_NUM    16
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    17
#define Y2_GPIO_NUM    15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

#define LED_GPIO_NUM   21

namespace user {
    Camera::Camera() {
    }

    Camera::~Camera() {
    }

    bool Camera::init() {
        camera_config_t config;
        config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer   = LEDC_TIMER_0;
        config.pin_d0       = Y2_GPIO_NUM;
        config.pin_d1       = Y3_GPIO_NUM;
        config.pin_d2       = Y4_GPIO_NUM;
        config.pin_d3       = Y5_GPIO_NUM;
        config.pin_d4       = Y6_GPIO_NUM;
        config.pin_d5       = Y7_GPIO_NUM;
        config.pin_d6       = Y8_GPIO_NUM;
        config.pin_d7       = Y9_GPIO_NUM;
        config.pin_xclk     = XCLK_GPIO_NUM;
        config.pin_pclk     = PCLK_GPIO_NUM;
        config.pin_vsync    = VSYNC_GPIO_NUM;
        config.pin_href     = HREF_GPIO_NUM;
        config.pin_sccb_sda = SIOD_GPIO_NUM;
        config.pin_sccb_scl = SIOC_GPIO_NUM;
        config.pin_pwdn     = PWDN_GPIO_NUM;
        config.pin_reset    = RESET_GPIO_NUM;
        config.xclk_freq_hz = 20000000;
        config.frame_size   = FRAMESIZE_VGA;
        config.pixel_format = PIXFORMAT_JPEG; // for streaming
        config.grab_mode    = CAMERA_GRAB_LATEST;
        config.fb_location  = CAMERA_FB_IN_PSRAM;
        config.jpeg_quality = 10;
        config.fb_count     = 2;

        esp_err_t err       = esp_camera_init(&config);
        if(err != ESP_OK) {
            Logger::error("Camera init failed with error 0x%x", err);
            return false;
        }

        initialized = true;
        return true;
    }

    void Camera::savePicture(std::string filename) {
        camera_fb_t *fb = esp_camera_fb_get();

        if(!fb) {
            Logger::error("Failed to get camera frame buffer");
            return;
        }

        core::writeFile(SD, filename.c_str(), fb->buf, fb->len);
        esp_camera_fb_return(fb);
        Logger::debug("Photo saved to file");
        this->last_capture_time = millis();
    }
} // namespace user