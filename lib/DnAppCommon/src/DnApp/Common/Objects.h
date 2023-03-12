#pragma once

#include <type_traits> // std::is_base_of

namespace DnApp::Common::Objects {
    // https://stackoverflow.com/a/25231384/666907
    template<typename BaseClass, typename ObjectClass>
    inline
    bool instanceOf(const ObjectClass*) {
        return std::is_base_of<BaseClass, ObjectClass>::value;
    }
}
