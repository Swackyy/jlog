#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#include "Sink.h"

namespace JLog {
    /**
     * A basic sink backed by a file pointer
     */
    class FDSink final : public Sink {
        FILE* m_file;
#ifdef WIN32
    protected:
        HANDLE m_handle;
#endif
    public:
        explicit FDSink(FILE* file);

        ~FDSink() override;

        void log(const std::string_view& msg) override;

        void flush() override;
    };
}

#include "src/FDSink.inl"
