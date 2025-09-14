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

    inline std::shared_ptr<Logger> Registry::get(const std::string_view& key) {
        return m_loggers.try_emplace<Logger*>(key, new Logger()).first->second;
    }

    template<class SinkT, class ... Args>
    std::shared_ptr<Logger> Registry::get(const std::string_view& key, Args&&... args) {
        const auto&[iterator, flag] = m_loggers.try_emplace(key, new Logger());
        const std::shared_ptr<Logger> logger = iterator->second;

        if (flag) {
            logger->getSinks().push_back(std::make_shared<SinkT>(std::forward<Args>(args)...));
        }

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

    inline std::shared_ptr<Logger> getLogger(const std::string_view& key) {
        return getRegistry().get(key);
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getLogger(const std::string_view& key, Args&&... args) {
        return getRegistry().get<SinkT>(key, std::forward<Args>(args)...);
    }

    inline std::shared_ptr<Logger> getDefaultNew(const std::string_view& key) {
        const std::shared_ptr<Logger> logger = getRegistry().get(key);
        std::vector<std::shared_ptr<Sink>>& sinks = logger->getSinks();

        if (sinks.empty()) {
            sinks.push_back(getStdOutSink());
        }

        return logger;
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getDefault(Args&&... args) {
        return getLogger<SinkT>("jlog", std::forward<Args>(args)...);
    }

    inline std::shared_ptr<Logger> getDefault() {
        return getDefaultNew("jlog");
    }
}
