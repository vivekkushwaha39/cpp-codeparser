#include "logging.h"
void logd(const char *fmt, ...)
{   
    va_list list;
    va_start(list, fmt);
    vsnprintf(logBuff, 200, fmt, list);
    va_end(list);
    std::cout << logBuff << std::endl;
}