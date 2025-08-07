#pragma once

#include "Registry.h"

#if 0 >= JLOG_LEVEL
#define JLOG_TRACE(...) JLog::getDefault()->log(JLog::LogLevel_Trace, __VA_ARGS__)
#else
#define JLOG_TRACE(msg, ...)
#endif

#if 1 >= JLOG_LEVEL
#define JLOG_DEBUG(...) JLog::getDefault()->log(JLog::LogLevel_Debug, __VA_ARGS__)
#else
#define JLOG_DEBUG(msg, ...)
#endif

#if 2 >= JLOG_LEVEL
#define JLOG_INFO(...) JLog::getDefault()->log(JLog::LogLevel_Info, __VA_ARGS__)
#else
#define JLOG_INFO(msg, ...)
#endif

#if 3 >= JLOG_LEVEL
#define JLOG_WARN(...) JLog::getDefault()->log(JLog::LogLevel_Warn, __VA_ARGS__)
#else
#define JLOG_WARN(msg, ...)
#endif

#if 4 >= JLOG_LEVEL
#define JLOG_ERROR(...) JLog::getDefault()->log(JLog::LogLevel_Error, __VA_ARGS__)
#else
#define JLOG_ERROR(msg, ...)
#endif

#if 5 >= JLOG_LEVEL
#ifdef JLOG_EXIT_ON_FATAL
#define JLOG_FATAL(...) JLog::getDefault()->log(JLog::LogLevel_Fatal, __VA_ARGS__); exit(JLOG_EXIT_ON_FATAL)
#else
#define JLOG_FATAL(...) JLog::getDefault()->log(JLog::LogLevel_Fatal, __VA_ARGS__)
#endif
#else
#define JLOG_FATAL(msg, ...)
#endif

// todo: Colour stack (8 bit), so you can push/pop colours to be used
// todo: Coloured text in a range, so for instance where the pattern is '[%l]: %v', only colour the logging level ('%l') with its associated colour, instead of the entire message
// todo: Allow for multiple sinks, giving out a public reference to their storage
// todo: Scan over for any potential performance improvements
// todo: Add mutex support for multithreaded logging
// todo: Consider changing the sinks being stored as std::shared_ptr to std::unique_ptr
// todo: Allow for "dropping" of loggers