#pragma once

#include "ConsoleColourSink.h"
#include "FDSink.h"
#include "LogLevel.h"

namespace JLog {
    /**
     * The default character sink for non-windows platforms, supporting colour through Ansi escape sequences
     */
    class AnsiConsoleColourSink final : public ConsoleColourSink {
        FDSink m_backingSink;

        static constexpr char FG_CODES[][16] = {
            "\033[30m",
            "\033[31m",
            "\033[32m",
            "\033[33m",
            "\033[34m",
            "\033[35m",
            "\033[36m",
            "\033[37m",
            "\033[90m",
            "\033[91m",
            "\033[92m",
            "\033[93m",
            "\033[94m",
            "\033[95m",
            "\033[96m",
            "\033[97m"
        };

        static constexpr char BG_CODES[][16] = {
            "\033[40m",
            "\033[41m",
            "\033[42m",
            "\033[43m",
            "\033[44m",
            "\033[45m",
            "\033[46m",
            "\033[47m",
            "\033[100m",
            "\033[101m",
            "\033[102m",
            "\033[103m",
            "\033[104m",
            "\033[105m",
            "\033[106m",
            "\033[107m"
        };

        const std::string_view RESET = "\033[m";
    public:
        AnsiConsoleColourSink(FILE* file, bool logLevelColours);

        void log(const std::string_view& msg) override;

        void writeAnsiCode(const std::string_view& code);

        void resetFormatting();

        void log(const std::string_view& msg, LogLevel level) override;

        void log(const std::string_view& msg, LogLevel level, Colour4Bit fgColour) override;

        void setFg4Bit(Colour4Bit colour) override;

        void setBg4Bit(Colour4Bit colour) override;

        void setColour8Bit(Colour4Bit fgColour, Colour4Bit bgColour) override;

        void flush() override;
    };
}

#include "src/AnsiConsoleColourSink.inl"