#include "logger.h"

#if (USE_SERIAL)
void Logger::log(LogType type, const char *fmt, va_list args) {
    if(!Serial) return;

    // print log header
    std::ostringstream out;
    out << std::fixed << std::setprecision(3) << (((float) millis()) / 1000.0f);
    std::string str = out.str();

    Serial.print(str.c_str());
    Serial.print(" [");
    Serial.print(typeToString(type));
    Serial.print("] ");

    // format the message into a buffer
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    Serial.println(buffer);
}

const char *Logger::typeToString(LogType type) {
    switch(type) {
        case INFO:    return "INFO";
        case DEBUG:   return "DEBUG";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

void Logger::info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log(INFO, fmt, args);
    va_end(args);
}

void Logger::debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log(DEBUG, fmt, args);
    va_end(args);
}

void Logger::warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log(WARNING, fmt, args);
    va_end(args);
}

void Logger::error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log(ERROR, fmt, args);
    va_end(args);
}
#else
void        Logger::log(LogType type, const char *fmt, va_list args) {}
const char *Logger::typeToString(LogType type) {}
void        Logger::info(const char *fmt, ...) {}
void        Logger::debug(const char *fmt, ...) {}
void        Logger::warning(const char *fmt, ...) {}
void        Logger::error(const char *fmt, ...) {}
#endif
