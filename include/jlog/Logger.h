#pragma once

#include <memory>

#include "Format.h"
#include "LogLevel.h"
#include "Sink.h"

namespace JLog {
    class Logger {
        std::shared_ptr<Format> m_format = getGlobalFormat();
    protected:
        std::shared_ptr<Sink> m_sink;
    public:
        explicit Logger(const std::shared_ptr<Sink>& sink);

        void format(const std::string_view& pattern);

        template<class... Args>
        void log(LogLevel level, const std::string_view& msg, Args&&... args);

        void flush() const;

        void setSink(const std::shared_ptr<Sink>& sink);

        void setColour8Bit(Colour4Bit fgColour, Colour4Bit bgColour) const;

        void setFg4Bit(Colour4Bit colour) const;

        void setBg4Bit(Colour4Bit colour) const;
    };
}

#include "src/Logger.inl"
