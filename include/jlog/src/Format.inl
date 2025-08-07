#pragma once

#include "jlog/Format.h"

#include <algorithm>

#include "jlog/Common.h"

namespace JLog {
    inline StdTimeFormatter::StdTimeFormatter(
        const char code)
    : m_code(code) {}

    inline std::string StdTimeFormatter::emit(Format* format, const std::string_view& msg, LogLevel level) {
        constexpr int bufferSize = 128;
        char buffer[bufferSize];

        const char formatStr[3] = {'%', m_code, '\0'};

        const auto epochSecs = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const std::tm* tm = std::localtime(&epochSecs);

        strftime(buffer, bufferSize, formatStr, tm);
        return buffer;
    }

    inline std::string MessageFormatter::emit(Format* format, const std::string_view& msg, LogLevel level) {
        return std::string(msg);
    }

    inline ConstStringFormatter::ConstStringFormatter(
        const std::string& value)
    : m_value(value) {}

    inline std::string ConstStringFormatter::emit(Format* format, const std::string_view& msg, LogLevel level) {
        return m_value;
    }

    inline std::string CapitaliseFormatter::emit(Format* format, const std::string_view& msg, LogLevel level) {
        format->m_capitalise = !format->m_capitalise;

        return "";
    }

    inline std::string LevelFormatter::emit(Format* format, const std::string_view& msg, const LogLevel level) {
        return std::string(getLevelName(level));
    }

    inline std::string UppercaseFormatter::emit(Format* format, const std::string_view& msg, LogLevel level) {
        format->m_uppercase = !format->m_uppercase;

        return "";
    }

    template<class Formatter, class... Args>
    void Format::addFormatter(std::string& current, Args&&... args) {
        if (!current.empty()) {
            m_formatters.emplace_back(std::make_unique<ConstStringFormatter>(current));
            current.clear();
        }

        m_formatters.emplace_back(std::make_unique<Formatter>(std::forward<Args>(args)...));
    }

    inline Format::Format(const std::string_view& pattern) {
        std::string current;

        for (size_t i = 0; i < pattern.size(); i++) {
            const char c = pattern.at(i);

            if (c == '%') {
                if (++i < pattern.size()) {
                    const char c0 = pattern.at(i);

                    switch (c0) {
                        case '%': {
                            current += '%';
                            break;
                        }

                        case 'c': {
                            addFormatter<CapitaliseFormatter>(current);
                            break;
                        }

                        case 'l': {
                            addFormatter<LevelFormatter>(current);
                            break;
                        }

                        case 't': {
                            if (++i < pattern.size()) {
                                addFormatter<StdTimeFormatter>(current, pattern.at(i));
                            } else {
                                JLOG_THROW("Expected a formatting code following '%t'");
                            }

                            break;
                        }

                        case 'u': {
                            addFormatter<UppercaseFormatter>(current);
                            break;
                        }

                        case 'v': {
                            addFormatter<MessageFormatter>(current);
                            break;
                        }

                        default: JLOG_THROW("'%" + c0 + "' is not a recognised formatting code");
                    }
                } else {
                    JLOG_THROW("Expected a formatting code following '%'");
                }
            } else {
                current += c;
            }
        }

        if (!current.empty()) {
            m_formatters.emplace_back(std::make_unique<ConstStringFormatter>(current));
        }
    }

    inline std::string Format::emit(const std::string_view& msg, const LogLevel level) {
        std::string out;

        m_capitalise = false;
        m_uppercase = false;

        for (const std::unique_ptr<Formatter>& formatter : m_formatters) {
            std::string string = formatter->emit(this, msg, level);

            if (m_uppercase) {
                std::ranges::transform(string, string.begin(), [](const char c){ return std::toupper(c); });
            } else if (m_capitalise) {
                if (string.length() >= 1) {
                    string.at(0) = std::toupper(string.at(0));
                }
            }

            out += string;
        }

        return out;
    }

    inline auto _format = std::make_shared<Format>("[%l] %v");

    inline void format(const std::string_view& pattern) {
        _format = std::make_shared<Format>(pattern);
    }

    inline const std::shared_ptr<Format>& getGlobalFormat() {
        return _format;
    }
}
