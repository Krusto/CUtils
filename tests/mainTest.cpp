#include <gtest/gtest.h>
#define USE_SPECIFIC_STD_TYPES

#include "darr_tests.hpp"
#include "dstr_tests.hpp"

int main(int argc, char** argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
