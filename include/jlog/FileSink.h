#pragma once

#include <filesystem>
#include <fstream>

#include "Sink.h"

namespace JLog {
    class FileSink final : public Sink {
        std::ofstream m_file;
    public:
        FileSink(const std::filesystem::path& path, bool append);

        ~FileSink() override;

        void log(const std::string_view& msg) override;

        void flush() override;
    };
}

#include "src/FileSink.inl"