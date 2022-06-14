#include "test_executor.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "test.h"
#include "algorithm.h"
#include "time_ms.h"

using namespace land;

test_executor::test_executor()
    : _test_list()
{
}

test_executor::~test_executor()
{
    for (auto it = _test_list.begin(); it != _test_list.end(); ++it)
    {
        it->second.clear();
    }
    _test_list.clear();
}

test_executor *test_executor::instance()
{
    static test_executor self;
    return &self;
}

void test_executor::register_test(land::test *t)
{
    assert(t);
    auto it = find_if(_test_list.begin(), _test_list.end(),
                      [t](const pair<const char *, list<land::test *>> &p)
                      {
                          return strcmp(p.first, t->get_suite_name()) == 0;
                      });

    if (it != _test_list.end())
    {
        it->second.push_back(t);
        return;
    }

    list<test *> v;
    v.push_back(t);
    _test_list.push_back(land::make_pair<>(t->get_suite_name(), v));
}

void test_executor::unregister_test(land::test *t)
{
    assert(t);
    auto it = find_if(_test_list.begin(), _test_list.end(),
                      [t](const pair<const char *, list<land::test *>> &p)
                      {
                          return strcmp(p.first, t->get_suite_name()) == 0;
                      });

    if (it != _test_list.end())
    {
        auto test_it = find(it->second.begin(), it->second.end(), t);
        if (test_it != it->second.end())
            it->second.erase(test_it);
    }
}

void test_executor::run_all()
{
    size_t test_count = 0;
    for (const auto &p : _test_list)
    {
        test_count += p.second.size();
    }

    fprintf(stdout, "Running %ld %s from %ld test %s.\n",
            test_count,
            (test_count > 1 ? "tests" : "test"),
            _test_list.size(),
            (_test_list.size() > 1 ? "suites" : "suite"));

    list<test *> failed_list;
    time_ms all_start = get_time_ms();
    for (auto p : _test_list)
    {
        fprintf(stdout, "\n"
                        "%ld %s from %s\n",
                p.second.size(),
                (p.second.size() > 1 ? "tests" : "test"),
                p.first);

        time_ms start = get_time_ms();
        for (test *t : p.second)
        {
            fprintf(stdout, "\033[32m[%-8s]\033[0m %s.%s\n", "RUN", t->get_suite_name(), t->get_case_name());
            t->run();
            if (t->has_failure())
            {
                failed_list.push_back(t);
                fprintf(stdout, "\033[31m[%8s]\033[0m %s.%s\n", "FAILED", t->get_suite_name(), t->get_case_name());
            }
            else
            {
                fprintf(stdout, "\033[32m[%8s]\033[0m %s.%s\n", "PASSED", t->get_suite_name(), t->get_case_name());
            }
        }
        time_ms end = get_time_ms();

        fprintf(stdout, "%ld %s from %s (%0.0f ms total)\n",
                p.second.size(),
                (p.second.size() > 1 ? "tests" : "test"),
                p.first,
                diff_time_ms(end, start));
    }
    time_ms all_end = get_time_ms();

    double passed_percent = double(test_count - failed_list.size()) / test_count * 100;
    fprintf(stdout, "\n"
                    "%0.0f%% tests passed, %ld %s failed\n",
            passed_percent,
            failed_list.size(),
            (failed_list.size() > 1 ? "tests" : "test"));

    fprintf(stdout, "\n"
                    "Total Test time (real) = %0.0f ms\n",
            diff_time_ms(all_end, all_start));

    if (!failed_list.empty())
    {
        fprintf(stdout, "\n"
                        "The following %s FAILED:\n",
                (failed_list.size() > 1 ? "tests" : "test"));
        size_t i = 0;
        for (const auto &t : failed_list)
        {
            fprintf(stdout, "\t %ld - \033[31m%s.%s\033[0m \n", ++i, t->get_suite_name(), t->get_case_name());
        }
    }
}
