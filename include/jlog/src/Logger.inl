#pragma once

#include "jlog/Logger.h"

#include <format>

#include "jlog/ConsoleColourSink.h"

namespace JLog {
    inline Logger::Logger(
        const std::shared_ptr<Sink>& sink)
    : m_sink(sink) {}

    inline void Logger::format(const std::string_view& pattern) {
        m_format = std::make_shared<Format>(pattern);
    }

    template<class... Args>
    void Logger::log(const LogLevel level, const std::string_view& msg, Args&&... args) {
        if (level >= getLevel()) {
            m_sink->log(std::vformat(m_format->emit(msg, level) + '\n', std::make_format_args(args...)), level);
        }

#ifdef JLOG_EXIT_ON_FATAL
        if (level == LogLevel_Fatal) {
            exit(JLOG_EXIT_ON_FATAL);
        }
#endif
    }

    template<class Message, class... Args, std::enable_if_t<!std::is_convertible_v<Message, std::string_view>, bool>>
    void Logger::log(const LogLevel level, const Message& msg, Args&&... args) {
        log(level, std::to_string(msg), args...);
    }

    inline void Logger::flush() const {
        m_sink->flush();
    }

    inline void Logger::setSink(const std::shared_ptr<Sink>& sink) {
        m_sink = sink;
    }

    inline void Logger::setColour8Bit(const Colour4Bit fgColour, const Colour4Bit bgColour) const {
        const auto sink = dynamic_cast<ConsoleColourSink*>(m_sink.get());

        if (sink != nullptr) {
            return sink->setColour8Bit(fgColour, bgColour);
        }
    }

    inline void Logger::setFg4Bit(const Colour4Bit colour) const {
        const auto sink = dynamic_cast<ConsoleColourSink*>(m_sink.get());

        if (sink != nullptr) {
            return sink->setFg4Bit(colour);
        }
    }

    inline void Logger::setBg4Bit(const Colour4Bit colour) const {
        const auto sink = dynamic_cast<ConsoleColourSink*>(m_sink.get());

        if (sink != nullptr) {
            return sink->setBg4Bit(colour);
        }
    }
}
