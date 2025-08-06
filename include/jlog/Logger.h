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
        /**
         * Create a logger with a character sink
         * @param sink a shared pointer to a character sink
         */
        explicit Logger(const std::shared_ptr<Sink>& sink);

        /**
         * Set a custom formatting pattern from this logger,
         * does not affect the global pattern
         * @param pattern a format to parse, default: @code[%l]: %v@endcode
         */
        void format(const std::string_view& pattern);

        /**
         * Main logging method
         * @tparam Args class types for the format arguments
         * @param level the logging level of this message
         * @param msg the message contents
         * @param args arguments to replace @code{}@endcode in the @code msg@endcode parameter
         */
        template<class... Args>
        void log(LogLevel level, const std::string_view& msg, Args&&... args);

        /**
         * Flush the character sink
         */
        void flush() const;

        /**
         * Set the character sink to a new one
         * @param sink a shared pointer to a character sink
         */
        void setSink(const std::shared_ptr<Sink>& sink);

        /**
         * Sets the foreground and background colours for the output text
         *
         * Only works for console sinks
         * @param fgColour @code Colour4Bit@endcode enum value
         * @param bgColour @code Colour4Bit@endcode enum value
         */
        void setColour8Bit(Colour4Bit fgColour, Colour4Bit bgColour) const;

        /**
         * Sets the foreground colour for the output text
         * @param colour @code Colour4Bit@endcode enum value
         */
        void setFg4Bit(Colour4Bit colour) const;

        /**
         * Sets the background colour for the output text
         * @param colour @code Colour4Bit@endcode enum value
         */
        void setBg4Bit(Colour4Bit colour) const;
    };
}

#include "src/Logger.inl"
