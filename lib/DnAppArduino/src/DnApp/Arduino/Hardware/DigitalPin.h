#pragma once

#include <cstdint>     // uint8_t
#include <type_traits> // std::is_abstract

#include <Arduino.h>

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Arduino::Hardware {
    class DigitalPin final:
        public DnApp::Hardware::DigitalPin {
    public:
        explicit
        DigitalPin(const uint8_t id):
            id{id} {
        }

        auto getId() const -> uint8_t {
            return id;
        }

        auto setOutputMode() -> void override {
            pinMode(id, OUTPUT);
        }

        auto setInputMode() -> void override {
            pinMode(id, INPUT);
        }

        auto setHigh() -> void override {
            digitalWrite(id, HIGH);
        }

        auto setLow() -> void override {
            digitalWrite(id, LOW);
        }

        auto isHigh() const -> bool override {
            return digitalRead(id) == HIGH;
        }

        auto isLow() const -> bool override {
            return digitalRead(id) == LOW;
        }
    private:
        const uint8_t id;
    };

    static_assert(!std::is_abstract<DigitalPin>());
}
