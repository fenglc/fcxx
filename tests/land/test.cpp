#include "test.h"
#include <stdio.h>

using namespace land;

test::test()
    : _has_fatal_failure(false),
      _has_nonfatal_failure(false)
{
}

bool test::has_fatal_failure()
{
    return _has_fatal_failure;
}

bool test::has_nonfatal_failure()
{
    return _has_nonfatal_failure;
}

void test::set_failure(bool is_fatal)
{
    if (is_fatal)
        _has_fatal_failure = true;
    else
        _has_nonfatal_failure = true;
}

void test::print_failure_message(const char *file, size_t line, const char *expr)
{
    fprintf(stdout, "%s:%ld\n", file, line);
    fprintf(stdout, "\t%s: %s\n", "FAILED", expr);
}
