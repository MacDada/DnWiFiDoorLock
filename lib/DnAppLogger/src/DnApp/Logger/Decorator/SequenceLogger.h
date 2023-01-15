#pragma once

#include <functional>
#include <type_traits>
#include <vector>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Decorator {
    class SequenceLogger final:
        public DnApp::Logger::Logger {
    public:
         // A `vector` cannot store instances of abstract classes,
         // but luckily we can store pointers/references to them.
         //
         // todo: "iterable" declaration?
         //       I don't really care if it is a vector, array, or any other container here.
         //       I just need it to be able to give me a list of `Logger`s on demand.
         //       I could do it with Templates, but then there is no clear interface,
         //       to see what methods I need,
         //       without reading all the code, to notice the usage.
        using Loggers = std::vector<std::reference_wrapper<Logger>>;

        explicit
        SequenceLogger(
            const Loggers& loggers
        ) noexcept:
            loggers{loggers} {
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using Logger::log;

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        }

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        }
    private:
        // todo: maybe I should not store references in the fields after all?
        //       https://discord.com/channels/583251190591258624/1063607252113702983/
        const Loggers& loggers;

        template<typename Message>
        void doLog(LOG_LEVEL level, const Message message) const {
            for (const auto& logger: loggers) {
                logger.get().log(level, message);
            }
        }
    };

    static_assert(!std::is_abstract<SequenceLogger>());
}
