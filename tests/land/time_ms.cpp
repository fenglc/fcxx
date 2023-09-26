#include "time_ms.h"

#ifdef _WIN32
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#endif

using namespace land;

time_ms land::get_time_ms()
{
#ifdef _WIN32
    SYSTEMTIME lt;
    GetLocalTime(&lt);

    tm tm;
    tm.tm_year = lt.wYear - 1900;
    tm.tm_mon = lt.wMonth - 1;
    tm.tm_mday = lt.wDay;
    tm.tm_hour = lt.wHour;
    tm.tm_min = lt.wMinute;
    tm.tm_sec = lt.wSecond;
    tm.tm_isdst = -1;

    timeval tv{};
    time_t sec = mktime(&tm);
    return (sec * 1000) + lt.wMilliseconds;
#else
    timeval tv{};
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
}

double land::diff_time_ms(time_ms end, time_ms begin)
{
    return end - begin;
}
