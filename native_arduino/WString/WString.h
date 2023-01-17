#pragma once

/**
 * `<WString.h>` is a part of <Arduino.h>,
 * but I want to include this file directly,
 * for more precise dependency requirements.
 *
 * It's supposed to be mocked by `ArduinoFake` I guess…
 *
 * Include this file with `lib_extra_dirs` config in `platformio.ini`.
 */
#include <Arduino.h>
