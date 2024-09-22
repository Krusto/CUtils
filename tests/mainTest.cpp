#include <gtest/gtest.h>

#include "DArray.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(DArr_Tests, DArr_Test1)
{
    using namespace testing;
    DArrayT* arr = darr_create_generic(4);
    ASSERT_NE(NULL, arr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test2)
{
    using namespace testing;
    DArrayT* arr = darr_create_generic(0);
    ASSERT_EQ(NULL, arr);
}

TEST(DArr_Tests, DArr_Test3)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test4)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test5)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test6)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test7)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test8)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test9)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test10)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test11)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test12)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_i32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test13)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u16(arr, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test14)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_i16(arr, 0xF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test15)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u8(arr, 0xAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test16)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_i8(arr, 0xF0);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test17)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(((uint32_t*) (arr->data))[0], 0xBAADF00D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test18)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u32(arr, 1, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test19)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(((int32_t*) (arr->data))[0], 0xBAADF00D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test20)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i32(arr, 1, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test21)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(((uint16_t*) (arr->data))[0], 0xBAAD);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test22)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u16(arr, 1, 0xF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test23)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(((int16_t*) (arr->data))[0], (int16_t) 0xBAAD);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test24)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i16(arr, 1, 0xF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test25)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u8(arr, 0, 0x0D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(arr->data[0], 0x0D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test26)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u8(arr, 1, 0x0D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test27)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i8(arr, 0, 0x0D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(arr->data[0], 0x0D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test28)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i8(arr, 1, 0x0D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test29)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint32_t result = darr_get_u32(arr, 0);
    ASSERT_EQ(result, 0xBAADF00D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test30)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint32_t result = darr_get_u32(arr, 0);
    ASSERT_EQ(result, 0xBAADF00D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test31)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint32_t* result = (uint32_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test32)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int32_t result = darr_get_i32(arr, 0);
    ASSERT_EQ(result, 0xBAADF00D);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test33)
{
    using namespace testing;
    DArrayI32T* arr = darr_create_i32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i32(arr, 0, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int32_t* result = (int32_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test34)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint32_t result = darr_get_u16(arr, 0);
    ASSERT_EQ(result, 0xBAAD);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test35)
{
    using namespace testing;
    DArrayU16T* arr = darr_create_u16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint16_t* result = (uint16_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test36)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int16_t result = darr_get_i16(arr, 0);
    ASSERT_EQ(result, (int16_t) 0xBAAD);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test37)
{
    using namespace testing;
    DArrayI16T* arr = darr_create_i16();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int16_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i16(arr, 0, 0xBAAD);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int16_t* result = (int16_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test38)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u8(arr, 0, 0xBA);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint32_t result = darr_get_u8(arr, 0);
    ASSERT_EQ(result, 0xBA);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test39)
{
    using namespace testing;
    DArrayU8T* arr = darr_create_u8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_u8(arr, 0, 0xBA);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    uint16_t* result = (uint16_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test40)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i8(arr, 0, 0xBA);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int8_t result = darr_get_i8(arr, 0);
    ASSERT_EQ(result, (int8_t) 0xBA);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test41)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i16(arr, 0, 0xBA);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    int8_t* result = (int8_t*) darr_get_ptr(arr, 0);
    ASSERT_NE(result, nullptr);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test42)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_insert_i8(arr, 0, 0xBA);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    void* result = darr_get_ptr(arr, 0);
    ASSERT_NE(result, NULL);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test43)
{
    using namespace testing;
    DArrayI8T* arr = darr_create_i8();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(int8_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_resize(arr, 1);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test44)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_push_u32(arr, 0xB105F00D);
    ASSERT_EQ(arr->capacity, 4);
    ASSERT_EQ(arr->length, 2);

    void* frontPtr = darr_front_ptr(arr);
    ASSERT_NE(frontPtr, NULL);
    ASSERT_EQ(0xBAADF00D, *((uint32_t*) frontPtr));

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test45)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    darr_push_u32(arr, 0xB105F00D);
    ASSERT_EQ(arr->capacity, 4);
    ASSERT_EQ(arr->length, 2);

    void* backPtr = darr_back_ptr(arr);
    ASSERT_NE(backPtr, NULL);
    ASSERT_EQ(0xB105F00D, *((uint32_t*) backPtr));

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test46)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(darr_is_empty(arr), FALSE);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test47)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    ASSERT_EQ(darr_is_empty(arr), TRUE);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test48)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);
    ASSERT_EQ(darr_capacity(arr), 1);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test49)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);
    darr_push_u32(arr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 4);
    ASSERT_EQ(arr->length, 2);
    ASSERT_EQ(darr_capacity(arr), 4);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test50)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    ASSERT_EQ(darr_capacity(arr), 1);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test51)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_erase(arr, 0);
    ASSERT_EQ(arr->length, 0);
    ASSERT_EQ(arr->capacity, 1);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test52)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);
    darr_push_u32(arr, 0xBAADF00D);

    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);

    darr_erase(arr, 0);

    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test53)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_erase(arr, 3);

    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test54)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_push_u32(arr, 0xBAADF00D);
    darr_push_u32(arr, 0xBAADF00D);

    ASSERT_EQ(arr->capacity, 4);
    ASSERT_EQ(arr->length, 2);

    darr_shrink_to_fit(arr);
    ASSERT_EQ(arr->capacity, 2);
    ASSERT_EQ(arr->length, 2);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test55)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_reserve(arr, 3);
    ASSERT_EQ(arr->capacity, 3);
    ASSERT_EQ(arr->length, 0);

    darr_destroy(arr);
}

TEST(DArr_Tests, DArr_Test57)
{
    using namespace testing;
    DArrayU32T* arr = darr_create_u32();
    ASSERT_NE(NULL, arr);
    ASSERT_EQ(arr->elementSize, sizeof(uint32_t));
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_push_u32(arr, 0xBAADF00D);

    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 1);

    uint32_t* elementPtr = (uint32_t*) darr_pop(arr);

    ASSERT_NE(elementPtr, NULL);
    ASSERT_EQ(*elementPtr, 0xBAADF00D);
    ASSERT_EQ(arr->capacity, 1);
    ASSERT_EQ(arr->length, 0);

    darr_destroy(arr);
}