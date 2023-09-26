#ifndef _LAND_TIME_MS_H
#define _LAND_TIME_MS_H

namespace land
{
    typedef long int time_ms;

    time_ms get_time_ms();

    double diff_time_ms(time_ms end, time_ms begin);
}

#endif
