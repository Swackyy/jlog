#pragma once

#include "jlog/console-colour-sink.h"

namespace JLog {
    inline ConsoleColourSink::ConsoleColourSink(
        const bool logLevelColours)
    : m_logLevelColours(logLevelColours) {}

    inline bool ConsoleColourSink::logLevelColours() const {
        return m_logLevelColours;
    }
}
