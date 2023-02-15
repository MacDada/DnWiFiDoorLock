#pragma once

#include <type_traits>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"

namespace DnApp::Logger::Decorator {
    class PrefixPostfixMessageLoggerDecorator final:
        public DnApp::Logger::Logger {
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
        using DnApp::Logger::Logger::log;

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };
    private:
        DnApp::Logger::Logger& logger;

        const char* const prefix;

        const char* const postfix;

        template<typename Message>
        void doLog(LOG_LEVEL level, const Message message) {
            logger.log(
                level,
                DnApp::Common::Strings::format(
                    "%s%s%s",
                    prefix,
                    message,
                    postfix
                )
            );
        }
    };

    static_assert(!std::is_abstract<PrefixPostfixMessageLoggerDecorator>());
}
