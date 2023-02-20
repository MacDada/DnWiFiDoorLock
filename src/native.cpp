#include <iostream>

// nothing to do here, we just need this file for the `native` env to be built
int main() {
    std::cout << __cplusplus << std::endl;

#ifdef __clang__
    std::cout << "CLANG" << std::endl;
#else
    std::cout << "GCC" << std::endl;
#endif

#ifdef __clang__
    std::cout
        << __clang_major__
        << "."
        << __clang_minor__
        << "."
        << __clang_patchlevel__
        << std::endl;
#else
    std::cout
        << __GNUC__
        << "."
        << __GNUC_MINOR__
        << "."
        << __GNUC_PATCHLEVEL__
        << std::endl;
#endif

    return 0;
}
