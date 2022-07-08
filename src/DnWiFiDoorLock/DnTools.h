#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {
    class DnTools {
    public:
        static char *format(char const *format...);
    };
}
