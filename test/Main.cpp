#include "jlog/FileSink.h"
#include "jlog/JLog.h"

// An internal test used when developing the library
// Not added to the '.gitignore' because it may be useful reference material
int main() {
    // Custom default message formatting with % key replacements
    JLog::format(">[%l]: %v");

    // Testing the logging system using the macros
    JLOG_TRACE("Testing trace, {}", "02");
    JLOG_DEBUG("Testing debug, {}", "02");
    JLOG_INFO(" Testing info,  {}", "02");
    JLOG_WARN(" Testing warn,  {}", "02");
    JLOG_ERROR("Testing error, {}", "02");
    JLOG_FATAL("Testing fatal, {}", "02");

    // Logging non-string messages
    JLOG_DEBUG(123);

    // Create a new text logger that will automatically be cross-platform
    const std::shared_ptr<JLog::Logger> customLogger = JLog::getDefaultNew("customLogger");

    // Local message formatting
    customLogger->format("Custom logger> %v");

    // Ensure changing the global format does not mess with local ones
    JLog::format(">[%l]: %v"); // No changes

    customLogger->log(JLog::LogLevel_Info, "Hello from our custom logger!");

    // Ensure the global format did not change
    JLOG_DEBUG("Testing global logger pattern");

    // File sink
    const std::shared_ptr<JLog::Logger> fileLogger = JLog::getLogger<JLog::FileSink>("fileLogger", "test.txt", false);

    fileLogger->log(JLog::LogLevel_Debug, "Hello, world!");
    fileLogger->log(JLog::LogLevel_Trace, "Trace file sink message");

    // - - -
    // Keep autoclosing consoles open
#ifdef WIN32
    Sleep(999999999);
#else
    usleep(999999999);
#endif
}
