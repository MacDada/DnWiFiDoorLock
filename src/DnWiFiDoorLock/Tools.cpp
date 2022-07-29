#include "Tools.h"

namespace DnWiFiDoorLock {

    // adopted from https://stackoverflow.com/a/10388547/666907
    // published at https://stackoverflow.com/a/72875362/666907
    std::unique_ptr<char[]> Tools::format(char const *format...) {
        va_list args;
        va_start(args, format);

        size_t needed = 1 + vsnprintf(nullptr, 0, format, args);

        auto buffer = std::make_unique<char[]>(needed);

        vsnprintf(buffer.get(), needed, format, args);

        return buffer;
    }

}
