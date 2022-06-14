#ifndef _LAND_ALGORITHM_H
#define _LAND_ALGORITHM_H

namespace land
{
    template <class InputIt, class T>
    InputIt find(InputIt first, InputIt last, const T &value)
    {
        for (auto it = first; it != last; ++it)
        {
            if (value == *it)
                return it;
        }
        return last;
    }

    template <class InputIt, class UnaryPredicate>
    InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        for (auto it = first; it != last; ++it)
        {
            if (p(*it))
                return it;
        }
        return last;
    }
}

#endif
