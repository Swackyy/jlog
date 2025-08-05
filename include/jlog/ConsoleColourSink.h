#pragma once

#include "Sink.h"

namespace JLog {
    class ConsoleColourSink : public Sink {
        bool m_logLevelColours;
    public:
        explicit ConsoleColourSink(bool logLevelColours);

        bool logLevelColours() const;

        virtual void setFg4Bit(Colour4Bit colour) = 0;

        virtual void setBg4Bit(Colour4Bit colour) = 0;

        virtual void setColour8Bit(Colour4Bit fgColour, Colour4Bit bgColour) = 0;

        virtual void log(const std::string_view& msg, LogLevel level, Colour4Bit fgColour) = 0;
    };
}

#include "src/ConsoleColourSink.inl"
