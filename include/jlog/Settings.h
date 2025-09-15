#pragma once

#include "ConsoleColour.h"

// !! TweakMe !!

// If defined, will forcibly exit the program with the specified exit code (default 1) on a fatal logging
// Comment out the line below to enable this functionality
//#define JLOG_EXIT_ON_FATAL 1

// Set to the lowest log level to log (default LogLevel_Debug)
// This applies to macros and the initial value of JLog::getLevel();
#define JLOG_LEVEL LogLevel_Debug

// The string name associated with each logging level
#define JLOG_LEVEL_NAMES \
    "trace",             \
    "debug",             \
    "info",              \
    "warn",              \
    "error",             \
    "fatal",             \
    "off"

// The (4 bit) text colour associated with each logging level
#define JLOG_LEVEL_COLOURS  \
    JLog::COL_LIGHT_CYAN,   \
    JLog::COL_LIGHT_GREEN,  \
    JLog::COL_LIGHT_YELLOW, \
    JLog::COL_YELLOW,       \
    JLog::COL_LIGHT_RED,    \
    JLog::COL_RED,          \
    JLog::COL_BLACK

// #define this if you wish to use your own fmtlib implementation
#ifndef JLOG_FMTLIB_RANGES
#define JLOG_FMTLIB_RANGES "bundled/fmt/ranges.h"
#endif

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif