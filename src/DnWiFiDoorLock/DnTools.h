#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {

    class DnTools final {
    public:
        static char *format(char const *format...);
    };

}
