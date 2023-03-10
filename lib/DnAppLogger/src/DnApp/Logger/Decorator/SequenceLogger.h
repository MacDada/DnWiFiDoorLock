#pragma once

#include <functional>
#include <span>
#include <type_traits>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Decorator {
    class SequenceLogger final:
        public DnApp::Logger::Logger {
    public:
         // A `vector` cannot store instances of abstract classes (todo: what about `span`s?),
         // but luckily we can store pointers/references to them.
         //
         // todo: pass in array instead of vector?
         //       * https://stackoverflow.com/questions/50942556/
         //       * https://stackoverflow.com/questions/26351587/
         //       * https://quuxplusone.github.io/blog/2020/08/06/array-size/
         //       * https://en.cppreference.com/w/cpp/container/array/deduction_guides
        using Loggers = std::span<const std::reference_wrapper<Logger>>;

        explicit
        SequenceLogger(
            const Loggers loggers
        ) noexcept:
            loggers{loggers} {
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using Logger::log;

        void log(const LOG_LEVEL level, const char* const message) override {
            for (const auto& logger: loggers) {
                logger.get().log(level, message);
            }
        }
    private:
        // todo: storing a span is probably the same kind of problem as storing a reference
        //       - the contents can be "gone" while i still may want to use it – yes/no?
        const Loggers loggers;
    };

    static_assert(!std::is_abstract<SequenceLogger>());
}
