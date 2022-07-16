#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {

    class Tools final {
    public:
        static char *format(char const *format...);
    };

}
