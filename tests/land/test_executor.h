#ifndef _LAND_TEST_EXECUTOR_H
#define _LAND_TEST_EXECUTOR_H

#include <land/list.h>
#include <land/pair.h>

namespace land
{
    class test;
    class test_executor
    {
    public:
        test_executor();
        ~test_executor();
        test_executor(const test_executor &) = delete;
        test_executor &operator=(const test_executor &) = delete;
        static test_executor *instance();
        void register_test(land::test *t);
        void unregister_test(land::test *t);
        void run_all();

    private:
        list<pair<const char *, list<land::test *>>> _test_list;
    };
}
#endif
