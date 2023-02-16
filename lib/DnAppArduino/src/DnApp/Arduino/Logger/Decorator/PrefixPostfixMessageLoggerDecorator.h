#pragma once

#include <type_traits>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Logger.h"

// todo: get rid of the copy–paste
//       DnApp::Logger::Decorator::PrefixPostfixMessageLoggerDecorator
//       is almost the same, and the tests as well…
//       https://discord.com/channels/583251190591258624/1070381312638206083
namespace DnApp::Arduino::Logger::Decorator {
    class PrefixPostfixMessageLoggerDecorator final:
        public DnApp::Arduino::Logger::WithArduinoStringLogger {
    public:
        explicit
        PrefixPostfixMessageLoggerDecorator(
            DnApp::Logger::Logger& logger,
            const char* const prefix = "",
            const char* const postfix = ""
        ):
            logger{logger},
            prefix{prefix},
            postfix{postfix} {
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using DnApp::Arduino::Logger::WithArduinoStringLogger::log;

        void log(LOG_LEVEL level, const char* message) override {
            logger.log(
                level,
                DnApp::Common::Strings::format(
                    "%s%s%s",
                    prefix,
                    message,
                    postfix
                )
            );
        };
    private:
        DnApp::Logger::Logger& logger;

        const char* const prefix;

        const char* const postfix;
    };

    static_assert(!std::is_abstract<PrefixPostfixMessageLoggerDecorator>());
}
