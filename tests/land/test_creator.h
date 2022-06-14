#ifndef _LAND_TEST_CREATOR_H
#define _LAND_TEST_CREATOR_H

#include <land/test_executor.h>

namespace land
{
    template <class T>
    class test_creator
    {
    public:
        test_creator()
            : _instance(new T)
        {
            land::test_executor::instance()->register_test(_instance);
        }
        ~test_creator()
        {
            land::test_executor::instance()->unregister_test(_instance);
            delete _instance;
        }
        test_creator(const test_creator &) = delete;
        test_creator &operator=(const test_creator &) = delete;

    private:
        T *_instance;
    };
}
#endif
