#pragma once

#include <windows.h>

#include "LogLevel.h"

namespace JLog {
    /**
     * For compatibility reasons, this is used as the default character sink on windows,
     * however you can use an Ansi sink instead by calling @code JLog::getDefault<AnsiConsoleColourSink>(...);@endcode
     */
    class WinConsoleColourSink final : public ConsoleColourSink {
        const HANDLE m_handle;

        static constexpr uint8_t MASK_FG = 0x0f; // 00001111
        static constexpr uint8_t MASK_BG = 0xf0; // 11110000

        static constexpr uint8_t COLOURS[] = {
            0,
            FOREGROUND_RED,
            FOREGROUND_GREEN,
            FOREGROUND_RED        | FOREGROUND_GREEN,
            FOREGROUND_BLUE,
            FOREGROUND_RED        | FOREGROUND_BLUE,
            FOREGROUND_GREEN      | FOREGROUND_BLUE,
            FOREGROUND_RED        | FOREGROUND_GREEN      | FOREGROUND_BLUE,
            FOREGROUND_INTENSITY,
            FOREGROUND_RED        | FOREGROUND_INTENSITY,
            FOREGROUND_GREEN      | FOREGROUND_INTENSITY,
            FOREGROUND_RED        | FOREGROUND_GREEN      | FOREGROUND_INTENSITY,
            FOREGROUND_BLUE       | FOREGROUND_INTENSITY,
            FOREGROUND_RED        | FOREGROUND_BLUE       | FOREGROUND_INTENSITY,
            FOREGROUND_GREEN      | FOREGROUND_BLUE       | FOREGROUND_INTENSITY,
            FOREGROUND_RED        | FOREGROUND_GREEN      | FOREGROUND_BLUE       | FOREGROUND_INTENSITY
        };
    public:
        WinConsoleColourSink(uint32_t handle, bool logLevelColours);

        void log(const std::string_view& msg) override;

        void log(const std::string_view& msg, LogLevel level) override;

        void log(const std::string_view& msg, LogLevel level, Colour4Bit fgColour) override;

        uint8_t getColour8bit() const;

        void setColour8BitRaw(uint8_t colour) const;

        void setFg4Bit(Colour4Bit colour) override;

        void setBg4Bit(Colour4Bit colour) override;

        void setColour8Bit(Colour4Bit fgColour, Colour4Bit bgColour) override;

        void flush() override;
    };
}

#include "src/WinConsoleColourSink.inl"