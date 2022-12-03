// nothing to do here, we just need this file for the `native` env to be built
#include <stdio.h>

int main() {
    int foo = 4;

    int bar = 2;

    int baz = foo - bar;

    printf("\n\nHello world! %d\n\n", baz);

    return 0;
}
