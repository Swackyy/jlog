#pragma once

#include "jlog/LogLevel.h"

#include "jlog/Settings.h"

namespace JLog {
    inline LogLevel getLevel() {
        static LogLevel _level = JLOG_LEVEL;
        
        return _level;
    }

    constexpr std::string_view levelNames[] = {
        JLOG_LEVEL_NAMES
    };

    constexpr Colour4Bit levelColours[] = {
        JLOG_LEVEL_COLOURS
    };

    constexpr std::string_view getLevelName(const LogLevel level) {
        return levelNames[level];
    }

    constexpr Colour4Bit getLevelColour(const LogLevel level) {
        return levelColours[level];
    }
}
