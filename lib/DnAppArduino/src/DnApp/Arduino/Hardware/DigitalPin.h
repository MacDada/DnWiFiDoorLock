#pragma once

#include <type_traits> // std::is_abstract

#include <Arduino.h>

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Arduino::Hardware {
    class DigitalPin final:
        public DnApp::Hardware::DigitalPin {
    public:
        explicit
        DigitalPin(const byte id):
            id{id} {
        }

        auto getId() const -> byte {
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
        const byte id;
    };

    static_assert(!std::is_abstract<DigitalPin>());
}
