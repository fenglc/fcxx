#ifndef _LAND_LAND_H
#define _LAND_LAND_H

#include <land/test.h>
#include <land/test_creator.h>

#define __TEST_CLASS_NAME(suite_name, case_name) \
    suite_name##_##case_name##_test

#define __CREATE_TEST(suite_name, case_name) \
    static land::test_creator<__TEST_CLASS_NAME(suite_name, case_name)> suite_name##_##case_name##_creator

#define TEST(suite_name, case_name)                                                 \
    class __TEST_CLASS_NAME(suite_name, case_name) : public land::test              \
    {                                                                               \
    public:                                                                         \
        virtual const char *get_suite_name() const override { return #suite_name; } \
        virtual const char *get_case_name() const override { return #case_name; }   \
        virtual void run() override;                                                \
    };                                                                              \
    __CREATE_TEST(suite_name, case_name);                                           \
    void __TEST_CLASS_NAME(suite_name, case_name)::run()

#define __TEST_EXPR_STR(macro_name, condition) macro_name "( " #condition " )"

#define __TEST_BOOLEAN(macro_name, is_fatal, condition, expected)                          \
    if (condition != expected)                                                             \
    {                                                                                      \
        print_failure_message(__FILE__, __LINE__, __TEST_EXPR_STR(macro_name, condition)); \
        set_failure(is_fatal);                                                             \
        if (is_fatal)                                                                      \
            return;                                                                        \
    }

#define EXPECT_TRUE(condition) __TEST_BOOLEAN("EXPECT_TRUE", false, condition, true)
#define EXPECT_FALSE(condition) __TEST_BOOLEAN("EXPECT_FALSE", false, condition, false)

#define REQUIRE_TRUE(condition) __TEST_BOOLEAN("REQUIRE_TRUE", true, condition, true)
#define REQUIRE_FALSE(condition) __TEST_BOOLEAN("REQUIRE_FALSE", true, condition, false)

#endif
