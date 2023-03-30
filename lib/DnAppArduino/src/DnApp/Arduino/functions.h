#pragma once

#include <WString.h> // String

namespace DnApp::Arduino::functions {
    auto dataToString(
        const uint8_t* const data,
        const size_t dataLength
    ) -> String {
        auto string = String{};
        string.reserve(dataLength);

        for (auto i = decltype(dataLength){0}; i < dataLength; i++) {
            string += char(data[i]);
        }

        return string;
    }
}
