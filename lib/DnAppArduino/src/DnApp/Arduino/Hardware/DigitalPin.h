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

        [[nodiscard]]
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

        /**
         * CANNOT be trusted if `analogWrite()` was used before it!
         *
         * I've tested it on a loop of `analogWrite()` from `0` to `255`
         * – I don't see a pattern, the result must be treated as "random":
         * https://arduino.stackexchange.com/a/59820/85901
         */
        [[nodiscard]]
        auto isHigh() const -> bool override {
            return digitalRead(id) == HIGH;
        }

        /**
         * CANNOT be trusted if `analogWrite()` was used before it!
         *
         * I've tested it on a loop of `analogWrite()` from `0` to `255`
         * – I don't see a pattern, the result must be treated as "random":
         * https://arduino.stackexchange.com/a/59820/85901
         */
        [[nodiscard]]
        auto isLow() const -> bool override {
            return digitalRead(id) == LOW;
        }
    private:
        const uint8_t id;
    };

    static_assert(!std::is_abstract<DigitalPin>());
}
