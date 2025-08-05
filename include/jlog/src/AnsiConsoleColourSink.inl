#pragma once

#include "jlog/AnsiConsoleColourSink.h"

namespace JLog {
    inline AnsiConsoleColourSink::AnsiConsoleColourSink(
        FILE* file,
        const bool logLevelColours)
    : ConsoleColourSink(logLevelColours), m_backingSink(FDSink(file)) {}

    inline void AnsiConsoleColourSink::log(const std::string_view& msg) {
        m_backingSink.log(msg);
    }

    inline void AnsiConsoleColourSink::writeAnsiCode(const std::string_view& code) {
        log(code); // It does the same thing, just better clarification
    }

    inline void AnsiConsoleColourSink::resetFormatting() {
        writeAnsiCode(RESET);
    }

    inline void AnsiConsoleColourSink::log(const std::string_view& msg, const LogLevel level) {
        if (logLevelColours()) {
            writeAnsiCode(FG_CODES[getLevelColour(level)]);
            log(msg);
            resetFormatting();
        } else {
            log(msg);
        }
    }

    inline void AnsiConsoleColourSink::log(const std::string_view& msg, const LogLevel level, const Colour4Bit fgColour) {
        writeAnsiCode(FG_CODES[fgColour]);
        log(msg, level);
        writeAnsiCode(RESET);
    }

    inline void AnsiConsoleColourSink::setFg4Bit(const Colour4Bit colour) {
        writeAnsiCode(FG_CODES[colour]);
    }

    inline void AnsiConsoleColourSink::setBg4Bit(const Colour4Bit colour) {
        writeAnsiCode(BG_CODES[colour]);
    }

    inline void AnsiConsoleColourSink::setColour8Bit(const Colour4Bit fgColour, const Colour4Bit bgColour) {
        setFg4Bit(fgColour);
        setBg4Bit(bgColour);
    }

    inline void AnsiConsoleColourSink::flush() {
        m_backingSink.flush();
    }
}
