#include "DString.h"
#include <gtest/gtest.h>

TEST(DString_Tests, DString_Test1)
{
    using namespace testing;
    DStringT* str = str_create_empty(10);
    ASSERT_NE(NULL, str);
    str_destroy(str);
}

TEST(DString_Tests, DString_Test2)
{
    using namespace testing;
    DStringT* str = str_create_empty(0);
    ASSERT_NE(NULL, str);
    str_destroy(str);
}

TEST(DString_Tests, DString_Test3)
{
    using namespace testing;
    DStringT* str = str_create("test", 4);
    ASSERT_NE(NULL, str);
    str_destroy(str);
}

TEST(DString_Tests, DString_Test4)
{
    using namespace testing;
    DStringT* str = str_create("test", 0);
    ASSERT_NE(NULL, str);
    str_destroy(str);
}

TEST(DString_Tests, DString_Test5)
{
    using namespace testing;
    DArrayT* strArr = str_arr_create();
    ASSERT_NE(NULL, strArr);
    str_arr_destroy(strArr);
}

TEST(DString_Tests, DString_Test6)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_get(str, 0), 'T');
    ASSERT_EQ(str_get(str, 1), 'e');
    ASSERT_EQ(str_get(str, 2), 's');
    ASSERT_EQ(str_get(str, 3), 't');
    ASSERT_EQ(str_get(str, 4), '\0');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test7)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_get_ptr(str, 0), &str->data[0]);
    ASSERT_EQ(str_get_ptr(str, 1), &str->data[1]);
    ASSERT_EQ(str_get_ptr(str, 2), &str->data[2]);
    ASSERT_EQ(str_get_ptr(str, 3), &str->data[3]);
    ASSERT_EQ(str_get_ptr(str, 4), &str->data[4]);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test8)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_front(str), 'T');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test9)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_front_ptr(str), &str->data[0]);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test10)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_back(str), 't');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test11)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str_back_ptr(str), &str->data[3]);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test12)
{
    using namespace testing;
    DStringT* str = str_create_empty(4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(is_str_empty(str), FALSE);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test13)
{
    using namespace testing;
    DStringT* str = str_create_empty(0);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(is_str_empty(str), TRUE);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test14)
{
    using namespace testing;
    DStringT* str = str_create("T", 1);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 1);
    str_resize(str, 2);
    ASSERT_EQ(str->length, 2);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test15)
{
    using namespace testing;
    DStringT* str = str_create("T", 1);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 1);
    str_resize(str, 0);
    ASSERT_EQ(str->length, 0);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test16)
{
    using namespace testing;
    DStringT* str = str_create("Te", 2);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 2);
    str_erase(str, 0);
    ASSERT_EQ(str->length, 1);
    ASSERT_EQ(str_get(str, 0), 'e');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test17)
{
    using namespace testing;
    DStringT* str = str_create("Tes", 3);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 3);
    str_erase(str, 1);
    ASSERT_EQ(str->length, 2);
    ASSERT_EQ(str_get(str, 1), 's');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test18)
{
    using namespace testing;
    DStringT* str = str_create("Tes", 3);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 3);
    str_erase(str, 4);
    ASSERT_EQ(str->length, 3);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test19)
{
    using namespace testing;
    DStringT* str = str_create("Tes", 3);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 3);
    str_insert(str, 3, "t");
    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->data[0], 'T');
    ASSERT_EQ(str->data[1], 'e');
    ASSERT_EQ(str->data[2], 's');
    ASSERT_EQ(str->data[3], 't');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test20)
{
    using namespace testing;
    DStringT* str = str_create("est", 3);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 3);
    str_insert(str, 0, "T");
    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->data[0], 'T');
    ASSERT_EQ(str->data[1], 'e');
    ASSERT_EQ(str->data[2], 's');
    ASSERT_EQ(str->data[3], 't');

    str_destroy(str);
}

TEST(DString_Tests, DString_Test21)
{
    using namespace testing;
    DStringT* str = str_create("Testttt", 7);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 7);
    ASSERT_EQ(str->capacity, 7);
    str_append_cstring(str, "opa");
    ASSERT_EQ(str->capacity, 22);
    ASSERT_EQ(str->length, 10);
    str_shring_to_fit(str);
    ASSERT_EQ(str->length, 10);
    ASSERT_EQ(str->capacity, 10);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test22)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 4);
    str_shring_to_fit(str);
    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 4);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test23)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 4);

    str_reserve(str, 4);

    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 4);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test24)
{
    using namespace testing;
    DStringT* str = str_create("Test", 4);
    ASSERT_NE(NULL, str);

    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 4);

    str_reserve(str, 5);

    ASSERT_EQ(str->length, 4);
    ASSERT_EQ(str->capacity, 5);

    str_destroy(str);
}

TEST(DString_Tests, DString_Test25)
{
    using namespace testing;

    ASSERT_EQ(cstr_length("test"), 4);
}