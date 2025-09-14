#pragma once

#include "jlog/Registry.h"

#ifdef WIN32
#include "jlog/WinConsoleColourSink.h"
#else
#include "jlog/AnsiConsoleColourSink.h"
#endif

namespace JLog {
    inline std::shared_ptr<Logger> Registry::attemptGet(const std::string_view& key) {
        if (m_loggers.contains(key)) {
            return m_loggers.at(key);
        }

        return nullptr;
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> Registry::get(const std::string_view& key, Args&&... args) {
        if (m_loggers.contains(key)) {
            return m_loggers.at(key);
        }

        // Would love to use a Logger constructor specialised for one character sink,
        // however it would not be possible to specify template parameter SinkT because of C++ limitations
        const std::shared_ptr<Logger> logger = m_loggers.try_emplace<Logger*>(key, new Logger()).first->second;

        logger->getSinks().push_back(std::make_shared<SinkT>(args...));

        return logger;
    }

    inline std::shared_ptr<Sink> getStdOutSink() {
#ifdef WIN32
        static auto sink = std::make_shared<WinConsoleColourSink>(STD_OUTPUT_HANDLE, true);
#else
        static auto sink = std::make_shared<AnsiConsoleColourSink>(stdout, true);
#endif

        return sink;
    }

    inline std::shared_ptr<Sink> getStdErrSink() {
#ifdef WIN32
        static auto sink = std::make_shared<WinConsoleColourSink>(STD_ERROR_HANDLE, true);
#else
        static auto sink = std::make_shared<AnsiConsoleColourSink>(stderr, true);
#endif

        return sink;
    }

    inline Registry& getRegistry() {
        static Registry _registry;

        return _registry;
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getLogger(const std::string_view& key, Args&&... args) {
        return getRegistry().get<SinkT>(key, args...);
    }

    inline std::shared_ptr<Logger> getDefaultNew(const std::string_view& key) {
        const std::shared_ptr<Logger> logger = getRegistry().get(key);
        logger->getSinks().emplace_back(getStdOutSink());
        return logger;
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getDefault(Args&&... args) {
        return getRegistry().get<SinkT>("jlog", args...);
    }

    inline std::shared_ptr<Logger> getDefault() {
        return getDefaultNew("jlog");
    }
}
