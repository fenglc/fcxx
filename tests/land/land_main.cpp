#include <land/land.h>
#include <land/test_executor.h>

int main(int argc, char *argv[])
{
    land::test_executor::instance()->run_all();
}
