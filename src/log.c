#include "log.h"
#include <stdarg.h>
#include <time.h>

LogLevel CURRENT_LOG_LEVEL = LOG_LEVEL_INFO;

void log_set_level(LogLevel level) {
    CURRENT_LOG_LEVEL = level;
}

static const char* level_to_str(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        default:              return "UNK";
    }
}

void log_message(LogLevel level,
                 const char* file,
                 int line,
                 const char* fmt, ...) {
    if (level < CURRENT_LOG_LEVEL) {
        return; /* on ne log pas en dessous du niveau courant */
    }

    /* Timestamp simple */
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char time_buf[20];
    if (tm_info != NULL) {
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    } else {
        snprintf(time_buf, sizeof(time_buf), "unknown-time");
    }

    /* Préfixe du message */
    fprintf(stderr, "[%s] %s:%d [%s] ",
            time_buf,
            file,
            line,
            level_to_str(level));

    /* Partie variable du message */
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");
}
