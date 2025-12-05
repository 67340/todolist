#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_ERROR = 3
} LogLevel;

/* Global log level (messages en dessous de ce niveau sont ignorés) */
extern LogLevel CURRENT_LOG_LEVEL;

/* Change le niveau courant (par ex. LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, etc.) */
void log_set_level(LogLevel level);

/* Fonction de logging bas niveau (utilise plutôt les macros ci-dessous) */
void log_message(LogLevel level,
                 const char* file,
                 int line,
                 const char* fmt, ...);

/* Macros pratiques qui injectent __FILE__ et __LINE__ automatiquement */
#define LOG_DEBUG(fmt, ...) log_message(LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  log_message(LOG_LEVEL_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  log_message(LOG_LEVEL_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* LOG_H */
