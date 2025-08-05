#pragma once

#include "ConsoleColour.h"

namespace JLog {
    enum LogLevel {
        LogLevel_Trace,
        LogLevel_Debug,
        LogLevel_Info,
        LogLevel_Warn,
        LogLevel_Error,
        LogLevel_Fatal,
        LogLevel_Off,
    };

    LogLevel getLevel();

    constexpr std::string_view getLevelName(LogLevel level);

    constexpr Colour4Bit getLevelColour(LogLevel level);
}

#include "src/LogLevel.inl"