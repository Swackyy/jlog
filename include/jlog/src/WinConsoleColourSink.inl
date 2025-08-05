#pragma once

#include "jlog/WinConsoleColourSink.h"

namespace JLog {
    inline WinConsoleColourSink::WinConsoleColourSink(
        const uint32_t handle,
        const bool logLevelColours)
    : ConsoleColourSink(logLevelColours), m_handle(GetStdHandle(handle)) {
        if (m_handle == INVALID_HANDLE_VALUE) {
            JLOG_THROW("Could not resolve handle");
        }
    }

    inline void WinConsoleColourSink::log(const std::string_view& msg) {
        WriteConsoleA(m_handle, msg.data(), msg.size(), nullptr, nullptr);
    }

    inline void WinConsoleColourSink::log(const std::string_view& msg, const LogLevel level) {
        if (logLevelColours()) {
            const uint8_t original = getColour8bit();

            setFg4Bit(getLevelColour(level));
            log(msg);
            setColour8BitRaw(original);
        } else {
            log(msg);
        }
    }

    inline void WinConsoleColourSink::log(const std::string_view& msg, const LogLevel level, const Colour4Bit fgColour) {
        const uint8_t original = getColour8bit();

        setFg4Bit(fgColour);
        log(msg, level);
        setColour8BitRaw(original);
    }

    inline uint8_t WinConsoleColourSink::getColour8bit() const {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(m_handle, &info);
        return info.wAttributes;
    }

    inline void WinConsoleColourSink::setColour8BitRaw(const uint8_t colour) const {
        SetConsoleTextAttribute(m_handle, colour);
    }

    inline void WinConsoleColourSink::setFg4Bit(const Colour4Bit colour) {
        SetConsoleTextAttribute(m_handle, COLOURS[colour] | MASK_BG & getColour8bit());
    }

    inline void WinConsoleColourSink::setBg4Bit(const Colour4Bit colour) {
        SetConsoleTextAttribute(m_handle, COLOURS[colour] << 4 | MASK_FG & getColour8bit());
    }

    inline void WinConsoleColourSink::setColour8Bit(const Colour4Bit fgColour, const Colour4Bit bgColour) {
        setColour8BitRaw(COLOURS[bgColour] << 4 | COLOURS[fgColour]);
    }

    // Unused for Windows
    inline void WinConsoleColourSink::flush() {}
}
