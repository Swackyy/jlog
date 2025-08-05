#pragma once

#include <string_view>

namespace JLog {
    class Sink {
    public:
        virtual ~Sink() = default;

        virtual void log(const std::string_view& msg) = 0;

        virtual void log(const std::string_view& msg, LogLevel level);

        virtual void flush() = 0;
    };
}

#include "src/Sink.inl"