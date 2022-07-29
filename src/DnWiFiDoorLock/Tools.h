#pragma once

#include <memory>

#include <Arduino.h>

namespace DnWiFiDoorLock {

    class Tools final {
    public:
        static std::unique_ptr<char[]> format(const char *format, ...);
    };

}
