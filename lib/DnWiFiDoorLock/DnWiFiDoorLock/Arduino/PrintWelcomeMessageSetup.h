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
        struct Build final {
            const char* const gitCommitHash;

            // Defaults are taken from the preprocessor run,
            // so we can assume that it is the latest timestamp
            // of ANY file changed, not only this one.
            // https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
            const char* const date = __DATE__;

            const char* const time = __TIME__;
        };

        explicit
        PrintWelcomeMessageSetup(
            Print& printer,
            const char* const appName,
            Build build
        ):
            printer{printer},
            appName{appName},
            build(build) {
        }

        void onSetup() override {
            printer.print(DnApp::Common::Strings::format(
                PSTR(
                    "\n\n\n"
                    "%s" // reset
                    "%s" // bold blue
                    "==========================================="
                    "%s" // reset
                    "\n\n"
                    "%s" // bold green
                    "  DnApp: `%s`!" // appName
                    "%s" // reset
                    "\n\n"
                    "%s" // bold green
                    // build.date, build.time, build.gitCommitHash
                    "  Built: %s @ %s @ %s"
                    "%s" // reset
                    "\n\n"
                    "%s" // bold blue
                    "==========================================="
                    "%s" // reset
                    "\n\n\n"
                ),
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_GREEN,
                appName,
                VT100_FORMAT_RESET,
                VT100_FORMAT_GREEN,
                build.date,
                build.time,
                build.gitCommitHash,
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

        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_GREEN = "\e[0;32m";

        Print& printer;

        const char* const appName;

        Build build;
    };

    static_assert(!std::is_abstract<PrintWelcomeMessageSetup>());
}