#pragma once

#include <memory>
#include <type_traits>

namespace DnApp::Common {
    // https://stackoverflow.com/a/25231384/666907
    template<typename BaseClass, typename ObjectClass>
    inline bool instanceOf(const ObjectClass *) {
        return std::is_base_of<BaseClass, ObjectClass>::value;
    }

    inline auto makeUniquePtrOfChars(const char string[]) {
        auto ptr = std::make_unique<char[]>(strlen(string) + 1);

        strcpy(ptr.get(), string);

        return ptr;
    }
}
