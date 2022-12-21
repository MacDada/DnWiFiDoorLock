#pragma once

#include <cstdarg>
#include <memory>

namespace DnApp::Common::Strings {
    // adopted from https://stackoverflow.com/a/10388547/666907
    // published at https://stackoverflow.com/a/72875362/666907
    inline
    std::unique_ptr<char[]> format(const char *const format...) {
        // `vsnprintf()` changes `va_list`'s state, so using it after that is UB.
        // We need the args twice, so it is safer to just get two copies.
        va_list args1;
        va_list args2;
        va_start(args1, format);
        va_start(args2, format);

        const size_t needed = 1 + vsnprintf(nullptr, 0, format, args1);

        auto buffer = std::make_unique<char[]>(needed);

        vsnprintf(buffer.get(), needed, format, args2);

        va_end(args1);
        va_end(args2);

        return buffer;
    }

    inline
    std::unique_ptr<char[]> makeUniquePtrOfChars(const char string[]) {
        auto ptr = std::make_unique<char[]>(strlen(string) + 1);

        strcpy(ptr.get(), string);

        return ptr;
    }
}
