#ifndef _LAND_PAIR_H
#define _LAND_PAIR_H

namespace land
{
    template <class T1, class T2>
    struct pair
    {
        T1 first;
        T2 second;
    };

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 first, T2 second)
    {
        pair<T1, T2> p;
        p.first = first;
        p.second = second;
        return p;
    }
}

#endif
