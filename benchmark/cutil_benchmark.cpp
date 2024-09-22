#include "benchmark.hpp"

#define CUTILS_VERBOSE
#include "CLog.h"

void test() { LOG("%d", 1); }

int main()
{
    Benchmark::Run("TestBenchmark", &test, 10000);
    return 0;
}