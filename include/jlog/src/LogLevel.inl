#pragma once

#include "jlog/LogLevel.h"

#include "jlog/Settings.h"

namespace JLog {
    inline LogLevel _level = JLOG_LEVEL;

    inline LogLevel getLevel() {
        return _level;
    }

    inline void setLevel(const LogLevel level) {
        _level = level;
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
