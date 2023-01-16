#pragma once

#include <type_traits>

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

        byte getId() const {
            return id;
        }

        void setOutputMode() override {
            pinMode(id, OUTPUT);
        }

        void setInputMode() override {
            pinMode(id, INPUT);
        }

        void setHigh() override {
            digitalWrite(id, HIGH);
        }

        void setLow() override {
            digitalWrite(id, LOW);
        }

        bool isHigh() const override {
            return digitalRead(id) == HIGH;
        }

        bool isLow() const override {
            return digitalRead(id) == LOW;
        }
    private:
        const byte id;
    };

    static_assert(!std::is_abstract<DigitalPin>());
}
