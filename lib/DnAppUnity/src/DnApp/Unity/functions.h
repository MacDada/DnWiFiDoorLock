#pragma once

#include <type_traits>

namespace DnApp::Unity {
    // https://stackoverflow.com/a/25231384/666907
    template<typename BaseClass, typename ObjectClass>
    inline bool instance_of(const ObjectClass *) {
        return std::is_base_of<BaseClass, ObjectClass>::value;
    }
}
