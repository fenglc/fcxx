#include <land/land.h>
#include <cassert>

TEST(cassert_test, check_macro_define)
{
#if defined(assert)
    EXPECT_TRUE(true);
#else
    EXPECT_TRUE(false);
#endif
}
