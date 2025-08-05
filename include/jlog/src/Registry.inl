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

        return m_loggers.try_emplace<Logger*>(key, new Logger(std::make_shared<SinkT>(args...))).first->second;
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
#ifdef WIN32
        return getRegistry().get<WinConsoleColourSink>(key, STD_OUTPUT_HANDLE, true);
#else
        return getRegistry().get<AnsiConsoleColourSink>(key, stdout, true);
#endif
    }

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getDefault(Args&&... args) {
        return getRegistry().get<SinkT>("jlog", args...);
    }

    inline std::shared_ptr<Logger> getDefault() {
        return getDefaultNew("jlog");
    }
}
