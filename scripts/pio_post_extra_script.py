# Activate the script with `extra_scripts = pre:scripts/pio_post_extra_script.py` in `platformio.ini` config.
#
# https://docs.platformio.org/en/latest/projectconf/sections/env/options/advanced/extra_scripts.html
# https://docs.platformio.org/en/latest/scripting/actions.html

Import("env")

# Silencing `volatile` warnings
#
# There is a lot "invalid" usages of `volatile` in the external libraries (dependencies):
#
# > .platformio/packages/framework-arduinoespressif8266/cores/esp8266/core_esp8266_i2s.cpp:179:23:
# > warning: '++' expression of 'volatile'-qualified type is deprecated [-Wvolatile]
#
# The problem appears with the upgrade to C++20,
# but they apparently de-deprecated it in C++23,
# so there is little to no will to fix the usages:
# https://github.com/esp8266/Arduino/issues/8916
#
# Therefore, I'm silencing `volatile`, so that the build keeps being clean,
# and I don't miss any issues within _my_ code, hidden between the dependencies shitstorm.
# Luckily, I don't use `volatile` myself, so _my_ code should not be at risk.
#
# todo: remove the the silencing, when GCC is upgraded, and I can use C++23 standard,
#       or if they fix the issues in the libs (not gonna happen ;p)
#
# I cannot set the flag with `build_flags`, because then it applies to both C++ and C,
# while it is not valid for C -> and the warning appears:
#
# > cc1: warning: command-line option '-Wno-volatile' is valid for C++/ObjC++ but not for C
#
# Therefore, "hacking" with the `extra_scripts`:
#  * https://github.com/platformio/platformio-core/issues/1728
#  * https://github.com/platformio/platformio-core/issues/2144
#    * todo: get rid of `extra_scripts` when a "native to PIO" `build_flags` option can be properly set
#  * https://community.platformio.org/t/separate-settings-for-c-and-c-versions/21647
#  * https://community.platformio.org/t/silence-warnings-for-dependencies-external-libraries/33387
#
# Using `env` as it applies to everything, including the external libraries,
# while `projenv` would apply only to _my_ code,
# https://github.com/platformio/platformio-core/issues/1728#issuecomment-403297776
env.Append(CXXFLAGS=["-Wno-volatile"])
