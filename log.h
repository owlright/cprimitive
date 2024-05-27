#ifndef LOG_H
#define LOG_H

#ifndef LOG_LEVEL
#define LOG_LEVEL (7)
#endif

#ifndef LOG_COLOR
#define LOG_COLOR (1)
#endif

// log levels the same as syslog
#define EMERG (0)
#define ALERT (1)
#define CRIT (2)
#define ERR (3)
#define WARNING (4)
#define NOTICE (5)
#define INFO (6)
#define DEBUG (7)

// colors
#define NONE                 "\033[0m"
#define BLACK                "\033[0;30m"
#define L_BLACK              "\033[1;30m"
#define RED                  "\033[0;31m"
#define L_RED                "\033[1;31m"
#define GREEN                "\033[0;32m"
#define L_GREEN              "\033[1;32m"
#define BROWN                "\033[0;33m"
#define YELLOW               "\033[1;33m"
#define BLUE                 "\033[0;34m"
#define L_BLUE               "\033[1;34m"
#define PURPLE               "\033[0;35m"
#define L_PURPLE             "\033[1;35m"
#define CYAN                 "\033[0;36m"
#define L_CYAN               "\033[1;36m"
#define GRAY                 "\033[0;37m"
#define WHITE                "\033[1;37m"

#define BOLD                 "\033[1m"
#define UNDERLINE            "\033[4m"
#define BLINK                "\033[5m"
#define REVERSE              "\033[7m"
#define HIDE                 "\033[8m"
#define CLEAR                "\033[2J"
#define CLRLINE              "\r\033[K" //or "\033[1K\r"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// #define LOG_EMERG(M, ...)   do { fprintf(stderr, RED    "[EMERG]   " "%s (%s:%d) " NONE M YELLOW " errno: %s\n" NONE, __func__, __FILE__, __LINE__, ##__VA_ARGS__, clean_errno()); } while(0)
// #define LOG_ALERT(M, ...)   do { fprintf(stderr, PURPLE "[ALERT]   " "%s (%s:%d) " NONE M YELLOW " errno: %s\n" NONE, __func__, __FILE__, __LINE__, ##__VA_ARGS__, clean_errno()); } while(0)
// #define LOG_CRIT(M, ...)    do { fprintf(stderr, YELLOW "[CRIT]    " "%s (%s:%d) " NONE M YELLOW " errno: %s\n" NONE, __func__, __FILE__, __LINE__, ##__VA_ARGS__, clean_errno()); } while(0)



#define LOG_ERROR(M, ...)   do { fprintf(stderr, RED  "[ERR]     " "%s (%s:%d) " NONE M "\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_WARN(M, ...)    do { fprintf(stderr, YELLOW "[WARNING] " "%s (%s:%d) " NONE M "\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_NOTICE(M, ...)  do { fprintf(stderr, CYAN   "[NOTICE]  " "%s (%s:%d) " NONE M "\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_INFO(M, ...)    do { fprintf(stderr, GREEN  "[INFO]    " "%s (%s:%d) " NONE M "\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_DEBUG(M, ...)   do { fprintf(stderr, GRAY   "[DEBUG]   " "%s (%s:%d) " NONE M "\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)

/* LOG_LEVEL controls */
#if LOG_LEVEL < DEBUG
#undef LOG_DEBUG
#define LOG_DEBUG(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < INFO
#undef LOG_INFO
#define LOG_INFO(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < NOTICE
#undef LOG_NOTICE
#define LOG_NOTICE(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < WARNING
#undef LOG_WARN
#define LOG_WARN(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < ERR
#undef LOG_ERROR
#define LOG_ERROR(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < CRIT
#undef LOG_CRIT
#define LOG_CRIT(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < ALERT
#undef LOG_ALERT
#define LOG_ALERT(M, ...) do{}while(0)
#endif

#if LOG_LEVEL < EMERG
#undef LOG_EMERG
#define LOG_EMERG(M, ...) do{}while(0)
#endif

/* LOG_COLOR controls */
#if LOG_COLOR < 1

#undef NONE
#define NONE

#undef RED
#define RED

#undef PURPLE
#define PURPLE

#undef YELLOW
#define YELLOW

#undef BROWN
#define BROWN

#undef GREEN
#define GREEN

#undef CYAN
#define CYAN

#undef BLUE
#define BLUE

#undef GRAY
#define GRAY

#endif

#endif