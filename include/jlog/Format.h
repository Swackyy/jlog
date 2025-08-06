#pragma once

#include <memory>
#include <string>
#include <vector>

#include "LogLevel.h"

namespace JLog {
    class Format;

    /**
     * Base interface for formatter types
     */
    class Formatter {
    public:
        virtual ~Formatter() = default;

        virtual std::string emit(Format* format, const std::string_view& msg, LogLevel level) = 0;
    };

    class MessageFormatter final : public Formatter {
    public:
        std::string emit(Format* format, const std::string_view& msg, LogLevel level) override;
    };

    class ConstStringFormatter final : public Formatter {
        const std::string m_value;
    public:
        explicit ConstStringFormatter(const std::string& value);

        std::string emit(Format* format, const std::string_view& msg, LogLevel level) override;
    };

    class CapitaliseFormatter final : public Formatter {
    public:
        std::string emit(Format* format, const std::string_view& msg, LogLevel level) override;
    };

    class LevelFormatter final : public Formatter {
    public:
        std::string emit(Format* format, const std::string_view& msg, LogLevel level) override;
    };

    class UppercaseFormatter final : public Formatter {
    public:
        std::string emit(Format* format, const std::string_view& msg, LogLevel level) override;
    };

    class Format {
        std::vector<std::unique_ptr<Formatter>> m_formatters;
        bool m_capitalise = false;
        bool m_uppercase = false;

        template<class Formatter, class... Args>
        void addFormatter(std::string& current, Args&&... args);
    public:
        explicit Format(const std::string_view& pattern);

        void toggleCapitalise();

        void toggleUppercase();

        std::string emit(const std::string_view& msg, LogLevel level);
    };

    void format(const std::string_view& pattern);

    const std::shared_ptr<Format>& getGlobalFormat();
}

#include "src/Format.inl"