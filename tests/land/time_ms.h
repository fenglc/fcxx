#ifndef _LAND_TIME_MS_H
#define _LAND_TIME_MS_H

#include <sys/time.h>

namespace land
{
    typedef long int time_ms;

    time_ms get_time_ms()
    {
        timeval tv{};
        gettimeofday(&tv, nullptr);
        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    }

    double diff_time_ms(time_ms end, time_ms begin)
    {
        return end - begin;
    }
}

#endif
