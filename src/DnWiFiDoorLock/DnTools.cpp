#include "DnTools.h"

namespace DnWiFiDoorLock {
    // adopted from https://stackoverflow.com/a/10388547/666907
    // published at https://stackoverflow.com/a/72875362/666907
    char *DnTools::format(char const *format...) {
        va_list args;
        va_start(args, format);

        size_t needed = 1 + vsnprintf(NULL, 0, format, args);

        // they say to cast, so I cast…
        // https://stackoverflow.com/a/5099675/666907
        char *buffer = (char *) malloc(needed);

        vsprintf(buffer, format, args);

        return buffer;
    }
}
