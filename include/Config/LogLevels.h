#ifndef LogLevels_H
#define LogLevels_H
#include <cstdint>

enum class LogLevel: uint8_t
{
    Lvl_DEBUG = 0,
    Lvl_INFO = 1,
    Lvl_WARNING = 2,
    Lvl_ERROR = 3,
    Lvl_FATAL = 4
};

#endif // LogLevels_H