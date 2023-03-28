#include "DnWiFiDoorLock/App.h"

DnWiFiDoorLock::App app{{
    .name = APP_NAME,
    .buildGitCommitHash = BUILD_GIT_COMMIT_HASH,
    .serialBitsPerSecond = SERIAL_BITS_PER_SECOND,
    .servoPin = SERVO_PIN,
    .wiFi = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASSWORD,
    },
    .webServer = {
        .hostname = WEB_SERVER_HOSTNAME,
        .port = WEB_SERVER_PORT,
    },
    .otaUpload = {
        // todo: figure out why PSTR/PROGMEM does not work after Config extraction,
        //       for ANY of these values
        .hostname = OTA_UPLOAD_HOSTNAME,
        .port = OTA_UPLOAD_PORT,
        .passwordMd5 = OTA_UPLOAD_PASSWORD_MD5,
    },
    .furnaceHeaterButton = {
        .pressingAngle = FURNACE_HEATER_BUTTON_PRESSING_ANGLE,
        .notPressingAngle = FURNACE_HEATER_BUTTON_NOT_PRESSING_ANGLE,
        .pressingMilliseconds = FURNACE_HEATER_BUTTON_PRESSING_MILLISECONDS,
    },
}};

auto setup() -> void {
    app.onSetup();
}

auto loop() -> void {
    app.onLoop();
}
