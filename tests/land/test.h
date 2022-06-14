#ifndef _LAND_TEST_H
#define _LAND_TEST_H

#include <stddef.h>

namespace land
{
    class test
    {
    public:
        virtual ~test() = default;
        test(const test &) = delete;
        test &operator=(const test &) = delete;
        virtual const char *get_suite_name() const = 0;
        virtual const char *get_case_name() const = 0;
        bool has_failure() { return has_fatal_failure() || has_nonfatal_failure(); }
        bool has_fatal_failure();
        bool has_nonfatal_failure();
        virtual void run() = 0;

    protected:
        test();
        void set_failure(bool is_fatal);
        void print_failure_message(const char *file, size_t line, const char *expr);

    private:
        bool _has_fatal_failure;
        bool _has_nonfatal_failure;
    };
}
#endif
