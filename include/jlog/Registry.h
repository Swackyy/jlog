#pragma once

#include <map>

#include "Logger.h"

namespace JLog {
    class Registry {
        std::map<std::string_view, std::shared_ptr<Logger>> m_loggers;
    public:
        [[nodiscard]] std::shared_ptr<Logger> attemptGet(const std::string_view& key);

        template<class SinkT, class... Args>
        std::shared_ptr<Logger> get(const std::string_view& key, Args&&... args);
    };

    Registry& getRegistry();

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getLogger(const std::string_view& key, Args&&... args);

    std::shared_ptr<Logger> getDefaultNew(const std::string_view& key);

    template<class SinkT, class... Args>
    std::shared_ptr<Logger> getDefault(Args&&... args);

    std::shared_ptr<Logger> getDefault();
}

#include "src/Registry.inl"