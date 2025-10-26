#pragma once

#include <Arduino.h>
#include <iomanip>
#include <sstream>
#include <stdarg.h>
#include <string>

class Logger {
    public:
        enum LogType {
            INFO,
            DEBUG,
            WARNING,
            ERROR
        };

        static void info(const char *fmt, ...);
        static void debug(const char *fmt, ...);
        static void warning(const char *fmt, ...);
        static void error(const char *fmt, ...);

    private:
        static void        log(LogType type, const char *fmt, va_list args);
        static const char *typeToString(LogType type);
};