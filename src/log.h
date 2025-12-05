#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/**
 * @brief Log severity levels.
 */
typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_ERROR = 3
} LogLevel;

/**
 * @brief Global minimal log level.
 *
 * Messages with a level lower than this value are ignored.
 */
extern LogLevel CURRENT_LOG_LEVEL;

/**
 * @brief Change the current global log level.
 *
 * @param level New minimal log level to use.
 */
void log_set_level(LogLevel level);

/**
 * @brief Low-level logging function.
 *
 * Usually you call the LOG_DEBUG/INFO/WARN/ERROR macros instead of this
 * function directly.
 *
 * @param level Severity level of the message.
 * @param file Source file name (normally __FILE__).
 * @param line Source line number (normally __LINE__).
 * @param fmt  printf-style format string followed by optional arguments.
 */
void log_message(LogLevel level,
                 const char* file,
                 int line,
                 const char* fmt, ...);

/** @brief Log a DEBUG level message. */
#define LOG_DEBUG(fmt, ...) log_message(LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
/** @brief Log a INFO level message. */
#define LOG_INFO(fmt, ...)  log_message(LOG_LEVEL_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
/** @brief Log a WARN level message. */
#define LOG_WARN(fmt, ...)  log_message(LOG_LEVEL_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
/** @brief Log a ERROR level message. */
#define LOG_ERROR(fmt, ...) log_message(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* LOG_H */
