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

    /**
     * Get the current global minimum logging level
     * @return the current global minimum logging level
     */
    LogLevel getLevel();

    /**
     * Allows setting the global minimum logging level at runtime
     * @param level the level to set the global context to
     */
    void setLevel(LogLevel level);

    /**
     * Get the level name associated with a logging level
     * @param level @code LogLevel@endcode enum value
     * @return the English name corresponding to the specified @code level@endcode
     */
    constexpr std::string_view getLevelName(LogLevel level);

    /**
     * Get the level colour associated with a logging level
     * @param level @code LogLevel@endcode enum value
     * @return the 4 bit colour corresponding to the specified @code level@endcode
     */
    constexpr Colour4Bit getLevelColour(LogLevel level);
}

#include "src/LogLevel.inl"