#pragma once

#include <type_traits> // std::is_abstract

#include <Print.h>
#include <WString.h>

#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Common/Strings.h"

namespace DnApp::Arduino {
    class WelcomeMessagePrinter final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    public:
        struct Build final {
            const char* const gitCommitHash;

            // Defaults are taken from the preprocessor run,
            // so we can assume that it is the latest timestamp
            // of ANY file changed, not only this one.
            // https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
            const char* const date = __DATE__;

            const char* const time = __TIME__;

            const struct Compiler final {
                const long standard = __cplusplus;

#ifdef __clang__
                const char* const name = "CLANG";

                int versionMajor = __clang_major__;

                int versionMinor = __clang_minor__;

                int versionPatchLevel = __clang_patchlevel__;
#else
                const char* const name = "GCC";

                int versionMajor = __GNUC__;

                int versionMinor = __GNUC_MINOR__;

                int versionPatchLevel = __GNUC_PATCHLEVEL__;
#endif
            } compiler = {};
        };

        explicit
        WelcomeMessagePrinter(
            Print& printer,
            const char* const appName,
            const Build build
        ):
            printer{printer},
            appName{appName},
            build{build} {
        }

        auto onSetup() -> void override {
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
                    "\n"
                    "%s" // bold green
                    // build.compiler.name,
                    // build.compiler.versionMajor,
                    // build.compiler.versionMinor,
                    // build.compiler.versionPatchLevel,
                    // build.compiler.standard,
                    "         %s %d.%d.%d @ %d"
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
                VT100_FORMAT_GREEN,
                build.compiler.name,
                build.compiler.versionMajor,
                build.compiler.versionMinor,
                build.compiler.versionPatchLevel,
                build.compiler.standard,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET
            ).get());
        }

        auto onLoop() -> void override {
            // do nothing
        }
    private:
        static
        PROGMEM
        constexpr
        const auto VT100_FORMAT_RESET = "\e[0m";

        static
        PROGMEM
        constexpr
        const auto VT100_FORMAT_BOLD_BLUE = "\e[1;34m";

        static
        PROGMEM
        constexpr
        const auto VT100_FORMAT_BOLD_GREEN = "\e[1;32m";

        static
        PROGMEM
        constexpr
        const auto VT100_FORMAT_GREEN = "\e[0;32m";

        Print& printer;

        const char* const appName;

        const Build build;
    };

    static_assert(!std::is_abstract<WelcomeMessagePrinter>());
}
