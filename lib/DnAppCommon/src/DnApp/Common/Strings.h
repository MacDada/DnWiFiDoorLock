#pragma once

#include <cstdarg>
#include <memory>

namespace DnApp::Common::Strings {
    // adopted from https://stackoverflow.com/a/10388547/666907
    // published at https://stackoverflow.com/a/72875362/666907
    inline std::unique_ptr<char[]> format(const char *const format...) {
        va_list args;
        va_start(args, format);

        const size_t needed = 1 + vsnprintf(nullptr, 0, format, args);

        auto buffer = std::make_unique<char[]>(needed);

        vsnprintf(buffer.get(), needed, format, args);

        va_end(args);

        return buffer;
    }

    inline std::unique_ptr<char[]> makeUniquePtrOfChars(const char string[]) {
        auto ptr = std::make_unique<char[]>(strlen(string) + 1);

        strcpy(ptr.get(), string);

        return ptr;
    }
}
