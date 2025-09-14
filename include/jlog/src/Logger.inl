#pragma once

#include "jlog/Logger.h"

#include "../bundled/fmt/ranges.h"

#include "jlog/ConsoleColourSink.h"

namespace JLog {
    inline Logger::Logger() {}

    inline void Logger::format(const std::string_view& pattern) {
        m_format = std::make_shared<Format>(pattern);
    }

    template<class... Args>
    void Logger::log(const LogLevel level, const std::string_view& msg, Args&&... args) {
        if (level >= getLevel()) {
            for (const std::shared_ptr<Sink>& sink : m_sinks) {
                sink->log(fmt::vformat(m_format->emit(msg, level) + '\n', fmt::make_format_args(args...)), level);
            }
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
        for (const std::shared_ptr<Sink>& sink : m_sinks) {
            sink->flush();
        }
    }

    inline std::vector<std::shared_ptr<Sink>>& Logger::getSinks() {
        return m_sinks;
    }

    inline void Logger::setColour8Bit(const Colour4Bit fgColour, const Colour4Bit bgColour) const {
        for (const std::shared_ptr<Sink>& sink : m_sinks) {
            const auto consoleSink = dynamic_cast<ConsoleColourSink*>(sink.get());

            if (consoleSink != nullptr) {
                return consoleSink->setColour8Bit(fgColour, bgColour);
            }
        }
    }

    inline void Logger::setFg4Bit(const Colour4Bit colour) const {
        for (const std::shared_ptr<Sink>& sink : m_sinks) {
            const auto consoleSink = dynamic_cast<ConsoleColourSink*>(sink.get());

            if (consoleSink != nullptr) {
                return consoleSink->setFg4Bit(colour);
            }
        }
    }

    inline void Logger::setBg4Bit(const Colour4Bit colour) const {
        for (const std::shared_ptr<Sink>& sink : m_sinks) {
            const auto consoleSink = dynamic_cast<ConsoleColourSink*>(sink.get());

            if (consoleSink != nullptr) {
                return consoleSink->setBg4Bit(colour);
            }
        }
    }
}
