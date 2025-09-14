#include "jlog/FileSink.h"
#include "jlog/JLog.h"

#ifdef WIN32
#define JLOG_SLEEP(x) Sleep(x)
#else
#define JLOG_SLEEP(x) usleep(x);
#endif

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

    // Ensure changing local formats does not mess with the global one
    JLOG_DEBUG("Should be prepended by '>[%l]: '");

    // Ensure changing the global format does not mess with local ones
    JLog::format(">[%l]: %v"); // No changes

    customLogger->log(JLog::LogLevel_Debug, "Should be prepended by 'Custom logger> '");

    // Ensure the global format did not change
    JLOG_DEBUG("Testing global logger pattern");

    // File sink
    const std::shared_ptr<JLog::Logger> fileLogger = JLog::getLogger<JLog::FileSink>("fileLogger", "test.txt", false);

    // Test time formatters (%t + code -> strftime)
    fileLogger->format("[%tH:%tM:%tS] [%l]: %v");

    fileLogger->log(JLog::LogLevel_Debug, "Hello, world!");
    fileLogger->log(JLog::LogLevel_Trace, "Trace file sink message");

    // todo: This is clunky, make a utility / factory method for this
    // todo: updated it once so it is a bit cleaner in the backend, but still complete the above
    const std::shared_ptr<JLog::Logger> multiSinkLogger = JLog::getLogger("multiSinkLogger");
    std::vector<std::shared_ptr<JLog::Sink>>& sinks = multiSinkLogger->getSinks();
    sinks.reserve(2);
    sinks.push_back(JLog::getStdOutSink());
    sinks.push_back(std::make_shared<JLog::FileSink>("multiLogger.txt", false));
    multiSinkLogger->log(JLog::LogLevel_Debug, "This should be logged in both the console and 'multiLogger.txt'");

    // todo: move to separate thread
    for (int i = 1; i <= 100; i++) {
        fileLogger->log(JLog::LogLevel_Debug, "Iteration {}", i);
        JLOG_SLEEP(20);
    }

    // - - -
    // Keep autoclosing consoles open
    JLOG_SLEEP(999999999);
}
