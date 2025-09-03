#pragma once

#include <memory>

#include "Format.h"
#include "LogLevel.h"
#include "Sink.h"

namespace JLog {
    /**
     * A logger
     *
     * Do not instantiate these directly, use the Registry methods provided
     */
    class Logger {
        std::shared_ptr<Format> m_format = getGlobalFormat();

        std::vector<std::shared_ptr<Sink>> m_sinks;
    public:
        /**
         * Instantiate an empty logger, holding no character sinks
         */
        Logger();

        /**
         * Set a custom formatting pattern from this logger,
         * does not affect the global pattern
         * @param pattern a format to parse, default: @code[%l]: %v@endcode
         */
        void format(const std::string_view& pattern);

        /**
         * Logging method for any string type
         * @tparam Args class types for the format arguments
         * @param level the logging level of this message
         * @param msg the message contents
         * @param args arguments to replace @code{}@endcode in the @code msg@endcode parameter
         */
        template<class... Args>
        void log(LogLevel level, const std::string_view& msg, Args&&... args);

        /**
         * Logging method for any non-string type
         * @tparam Message any type which can be converted to a string through @code std::to_string@endcode
         * @tparam Args class types for the format arguments
         * @param level the logging level of this message
         * @param msg the message contents
         * @param args arguments to replace @code{}@endcode in the @code msg@endcode parameter
         */
        template<class Message, class... Args, std::enable_if_t<!std::is_convertible_v<Message, std::string_view>, bool> = false>
        void log(LogLevel level, const Message& msg, Args&&... args);

        /**
         * Flush all character sinks
         */
        void flush() const;

        /**
         * Returns a mutable reference to the character sinks held by this logger
         */
        std::vector<std::shared_ptr<Sink>>& getSinks();

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
