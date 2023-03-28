#pragma once

#include <type_traits> // std::is_abstract

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

        auto log(const LOG_LEVEL level, const char* const message) -> void override {
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
        // todo: maybe I should not store references in the fields after all?
        //       https://discord.com/channels/583251190591258624/1063607252113702983/
        DnApp::Logger::Logger& logger;

        const char* const prefix;

        const char* const postfix;
    };

    static_assert(!std::is_abstract<PrefixPostfixMessageLoggerDecorator>());
}
