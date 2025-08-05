#pragma once

#include <stdexcept>

#define JLOG_THROW(msg) throw std::runtime_error('[' + std::string(__FILE__) + ':' + __FUNCTION__ + "] " + msg)