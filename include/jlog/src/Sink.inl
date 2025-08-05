#pragma once

#include "jlog/Sink.h"

namespace JLog {
    inline void Sink::log(const std::string_view& msg, LogLevel level) {
        log(msg);
    }
}