#pragma once

#include <string_view>

#include "LogLevel.h"

namespace JLog {
    /**
     * Base interface for character sinks
     */
    class Sink {
    public:
        virtual ~Sink() = default;

        /**
         * Main logging method
         * @param msg the message contents
         */
        virtual void log(const std::string_view& msg) = 0;

        /**
         * Alternative logging method
         * @param msg the message contents
         * @param level the logging level of this message
         */
        virtual void log(const std::string_view& msg, LogLevel level);

        /**
         * Flush the message, may not need to be overridden or called
         */
        virtual void flush() = 0;
    };
}

#include "src/Sink.inl"