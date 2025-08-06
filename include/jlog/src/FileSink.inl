#pragma once

#include "jlog/FileSink.h"

namespace JLog {
    inline FileSink::FileSink(const std::filesystem::path& path, const bool append) {
        if (append) {
            m_file = std::ofstream(path, std::ios_base::app | std::ios_base::out);
        } else {
            m_file = std::ofstream(path, std::ios_base::out);
        }
    }

    inline FileSink::~FileSink() {
        m_file.close();
    }

    inline void FileSink::log(const std::string_view& msg) {
        m_file << msg;
        flush();
    }

    inline void FileSink::flush() {
        m_file.flush();
    }
}
