#pragma once

#include <map>

#include "Logger.h"

namespace JLog {
    class Registry {
        std::map<std::string_view, std::shared_ptr<Logger>> m_loggers;
    public:
        /**
         * Attempt to get a logger
         * @param key the identifier for this logger
         * @return the logger with provided @code key@endcode if it exists, else @code nullptr@endcode
         */
        [[nodiscard]] std::shared_ptr<Logger> attemptGet(const std::string_view& key);

        // For 0 sinks
        std::shared_ptr<Logger> get(const std::string_view& key);

        // For 1 sink
        template<class SinkT, class... Args>
        std::shared_ptr<Logger> get(const std::string_view& key, Args&&... args);
    };

    /**
     * Get the default standard out sink corresponding to the target platform
     * @return sink of type:
     * - Windows: @code WinConsoleColourSink@endcode
     * - Other:   @code AnsiConsoleColourSink@endcode
     */
    std::shared_ptr<Sink> getStdOutSink();

    /**
     * Get the default standard error sink corresponding to the target platform
     * @return sink of type:
     * - Windows: @code WinConsoleColourSink@endcode
     * - Other:   @code AnsiConsoleColourSink@endcode
     */
    std::shared_ptr<Sink> getStdErrSink();

    /**
     * Get the logger registry
     * @return the global logger registry
     */
    Registry& getRegistry();

    /**
     * Get or create a logger, holding no character sinks
     * @param key the identifier for this logger
     * @return the logger with provided @code key@endcode if it exists, else a new logger
     */
    std::shared_ptr<Logger> getLogger(const std::string_view& key);

    /**
     * Get or create a logger holding one character sink
     * @tparam SinkT type of character sink
     * @tparam Args class types for character sink construction
     * @param key the identifier for this logger
     * @param args arguments for character sink construction
     * @return the logger with provided @code key@endcode if it exists, else a new logger
     */
    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getLogger(const std::string_view& key, Args&&... args);

    /**
     * Get or create a default console logger
     * @param key the identifier for this logger
     * @return the logger with provided @code key@endcode if it exists, else a new logger. It will be backed by a:
     * - Windows: @code WinConsoleColourSink@endcode
     * - Other:   @code AnsiConsoleColourSink@endcode
     */
    std::shared_ptr<Logger> getDefaultNew(const std::string_view& key);

    /**
     * Get or create the default console logger
     * @tparam SinkT type of character sink
     * @tparam Args class types for character sink construction
     * @param args arguments for character sink construction
     * @return the default logger if it exists, else a new default logger
     */
    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getDefault(Args&&... args);

    /**
     * Get the default console logger
     * @return the default console logger
     */
    std::shared_ptr<Logger> getDefault();
}

#include "src/Registry.inl"