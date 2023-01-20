#pragma once

#include <type_traits>

#include <Print.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class PrintWelcomeMessageSetup final:
        public SetupAndLoopAware {
    public:
        explicit
        PrintWelcomeMessageSetup(
            Print& printer,
            const char* const appName
        ):
            printer{printer},
            appName{appName} {
        }

        void onSetup() override {
            printer.print(DnApp::Common::Strings::format(
                PSTR(
                    "\n\n\n"
                    "%s"
                    "================================"
                    "%s"
                    "\n\n"
                    "%s"
                    "  Hello from `%s`!"
                    "%s"
                    "\n\n"
                    "%s"
                    "================================"
                    "%s"
                    "\n\n\n"
                ),
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_GREEN,
                appName,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET
            ).get());
        }

        void onLoop() override {
            // do nothing
        }
    private:
        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_RESET = "\e[0m";

        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_BOLD_BLUE = "\e[1;34m";

        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_BOLD_GREEN = "\e[1;32m";

        Print& printer;

        const char* const appName;
    };

    static_assert(!std::is_abstract<PrintWelcomeMessageSetup>());
}