#pragma once

#include "jlog/FDSink.h"

#include <cstdio>

#include "jlog/Common.h"

#ifdef WIN32
#include "io.h"
#endif

namespace JLog {
    inline FDSink::FDSink(
        FILE* file)
    : m_file(file) {
#ifdef WIN32
        m_handle = reinterpret_cast<HANDLE>(_get_osfhandle(_fileno(file)));

        if (m_handle == INVALID_HANDLE_VALUE) {
            JLOG_THROW("Could not resolve handle");
        }
#endif
    }

    inline FDSink::~FDSink() {
        fclose(m_file);
    }

    inline void FDSink::log(const std::string_view& msg) {
#ifdef WIN32
        unsigned long written = 0;

        if (!WriteFile(m_handle, msg.data(), msg.size(), &written, nullptr)) {
            JLOG_THROW("Could not write to handle, error code " + std::to_string(GetLastError()));
        }
#else
        std::fwrite(msg.data(), 1, msg.size(), m_file);
#endif
        flush();
    }

    inline void FDSink::flush() {
        fflush(m_file);
    }
}
