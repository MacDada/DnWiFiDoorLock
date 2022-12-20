#pragma once

#include <memory>

namespace DnApp::Common::Strings {
    inline auto makeUniquePtrOfChars(const char string[]) {
        auto ptr = std::make_unique<char[]>(strlen(string) + 1);

        strcpy(ptr.get(), string);

        return ptr;
    }
}
