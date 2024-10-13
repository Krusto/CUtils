#ifndef DARRAY_HEADER
#define DARRAY_HEADER
/**
 * @file
 * @author Krusto Stoyanov ( k.stoianov2@gmail.com )
 * @brief 
 * @version 1.0
 * @date 
 * 
 * @section LICENSE
 * MIT License
 * 
 * Copyright (c) 2024 Krusto
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section DESCRIPTION
 * 
 * CArray Header
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CLog.h"
#include "CMemory.h"
#include "STDTypes.h"
/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/**
 * @def DARRAY_INITIAL_CAPACITY
 * @brief The initial capacity of a dynamic array.
 */
#define DARRAY_INITIAL_CAPACITY 1u

/**
 * @def DARRAY_RESIZE_FACTOR
 * @brief The resize factor of a dynamic array.
 *
 * If the length of the array exceeds the capacity, the capacity is doubled.
 */
#define DARRAY_RESIZE_FACTOR 2u

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

/**
 * @struct DArrayT
 * @brief A dynamic array.
 * 
 * A dynamic array is a type of array that can grow in size as elements are added
 * to it. This is useful for storing collections of data when the number of
 * elements is not known until runtime.
 * 
 * @var length The number of elements in the dynamic array.
 * @var capacity The maximum number of elements that the dynamic array can hold.
 * @var elementSize The size of each element in the dynamic array.
 * @var data The data of the dynamic array.
 */
typedef struct {
    size_t length;
    size_t capacity;
    size_t elementSize;
    int8_t* data;
} DArrayT;

/**
 * @typedef DArrayU32T
 * @brief A dynamic array of uint32_t.
 */
typedef DArrayT DArrayU32T;

/**
 * @typedef DArrayI32T
 * @brief A dynamic array of int32_t.
 */
typedef DArrayT DArrayI32T;

/**
 * @typedef DArrayU16T
 * @brief A dynamic array of uint16_t.
 */
typedef DArrayT DArrayU16T;

/**
 * @typedef DArrayI16T
 * @brief A dynamic array of int16_t.
 */
typedef DArrayT DArrayI16T;

/**
 * @typedef DArrayU8T
 * @brief A dynamic array of uint8_t.
 */
typedef DArrayT DArrayU8T;

/**
 * @typedef DArrayI8T
 * @brief A dynamic array of int8_t.
 */
typedef DArrayT DArrayI8T;

/***********************************************************************************************************************
Static functions declaration
***********************************************************************************************************************/
/**
 * @brief Destroy a dynamic array.
 * @param darr[in] The dynamic array to destroy.
 * @return None.
 */
static void darr_destroy(DArrayT* darr);

/**
 * @brief Create a dynamic array of uint32_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayU32T* darr_create_u32();

/**
 * @brief Create a dynamic array of int32_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayI32T* darr_create_i32();

/**
 * @brief Create a dynamic array of uint16_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayU16T* darr_create_u16();

/**
 * @brief Create a dynamic array of int16_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayI16T* darr_create_i16();

/**
 * @brief Create a dynamic array of uint8_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayU8T* darr_create_u8();

/**
 * @brief Create a dynamic array of int8_t.
 * @return A pointer to the new dynamic array.
 */
static DArrayI8T* darr_create_i8();

/**
 * @brief Create a dynamic array of any type.
 * @param typeSize[in] The size of the type to be stored in the array.
 * @return A pointer to the new dynamic array.
 */
static DArrayT* darr_create_generic(size_t typeSize);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_u32(DArrayU32T* darr, uint32_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_i32(DArrayI32T* darr, int32_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_u16(DArrayU16T* darr, uint16_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_i16(DArrayI16T* darr, int16_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_u8(DArrayU8T* darr, uint8_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_i8(DArrayI8T* darr, int8_t value);

/**
 * @brief Push a new element to the end of the dynamic array.
 * @param darr[in] The dynamic array.
 * @param value[in] The value to push.
 * @return None.
 */
static void darr_push_generic(DArrayT* darr, void* value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_u32(DArrayU32T* darr, size_t index, uint32_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_i32(DArrayI32T* darr, size_t index, int32_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_u16(DArrayU16T* darr, size_t index, uint16_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_i16(DArrayI16T* darr, size_t index, int16_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_u8(DArrayU8T* darr, size_t index, uint8_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_i8(DArrayI8T* darr, size_t index, int8_t value);

/**
 * @brief Insert a new element at the given index in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to insert.
 * @param value[in] The value to insert.
 * @return None.
 */
static void darr_insert_generic(DArrayT* darr, size_t index, void* valuePtr);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static uint32_t darr_get_u32(DArrayU32T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array, safely.
 *
 * This function is like darr_get_u32, but it will return 0 if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index, or 0 if the index is out of bounds.
 */
static uint32_t darr_get_u32_safe(DArrayU32T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static int32_t darr_get_i32(DArrayI32T* darr, size_t index);
/**
 * @brief Get a value from the dynamic array, safely.
 *
 * This function is like darr_get_i32, but it will return 0 if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index, or 0 if the index is out of bounds.
 */
static int32_t darr_get_i32_safe(DArrayI32T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static uint32_t* darr_get_u32_ptr(DArrayU32T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_u32_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static uint32_t* darr_get_u32_ptr_safe(DArrayU32T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static int32_t* darr_get_i32_ptr(DArrayI32T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_i32_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static int32_t* darr_get_i32_ptr_safe(DArrayI32T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static uint16_t darr_get_u16(DArrayU16T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array, safely.
 *
 * This function is like darr_get_u16, but it will return 0 if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index, or 0 if the index is out of bounds.
 */
static uint16_t darr_get_u16_safe(DArrayU16T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static int16_t darr_get_i16(DArrayI16T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array, safely.
 *
 * This function is like darr_get_i16, but it will return 0 if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index, or 0 if the index is out of bounds.
 */
static int16_t darr_get_i16_safe(DArrayI16T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static uint16_t* darr_get_u16_ptr(DArrayU16T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_u16_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static uint16_t* darr_get_u16_ptr_safe(DArrayU16T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static int16_t* darr_get_i16_ptr(DArrayI16T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_i16_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static int16_t* darr_get_i16_ptr_safe(DArrayI16T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static uint8_t darr_get_u8(DArrayU8T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index.
 */
static int8_t darr_get_i8(DArrayI8T* darr, size_t index);

/**
 * @brief Get a value from the dynamic array, safely.
 *
 * This function is like darr_get_i8, but it will return 0 if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return The value at the given index, or 0 if the index is out of bounds.
 */
static int8_t darr_get_i8_safe(DArrayI8T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static uint8_t* darr_get_u8_ptr(DArrayU8T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_u8_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static uint8_t* darr_get_u8_ptr_safe(DArrayU8T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static int8_t* darr_get_i8_ptr(DArrayI8T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_i8_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static int8_t* darr_get_i8_ptr_safe(DArrayI8T* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index.
 */
static void* darr_get_ptr(DArrayT* darr, size_t index);

/**
 * @brief Get a pointer to a value in the dynamic array, safely.
 *
 * This function is like darr_get_ptr, but it will return NULL if the index
 * is out of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to get.
 * @return A pointer to the value at the given index, or NULL if the index is
 * out of bounds.
 */
static void* darr_get_ptr_safe(DArrayT* darr, size_t index);

/**
 * @brief Resize the dynamic array.
 * @param darr[in] The dynamic array.
 * @param newLength[in] The new length of the dynamic array.
 */
static void darr_resize(DArrayT* darr, size_t newLength);

/**
 * @brief Get a pointer to the first value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @return A pointer to the first value in the dynamic array.
 */
static void* darr_front_ptr(DArrayT* darr);

/**
 * @brief Get a pointer to the first value in the dynamic array, safely.
 *
 * This function is like darr_front_ptr, but it will return NULL if the dynamic
 * array is empty.
 *
 * @param darr[in] The dynamic array.
 * @return A pointer to the first value in the dynamic array, or NULL if the
 * dynamic array is empty.
 */
static void* darr_front_ptr_safe(DArrayT* darr);

/**
 * @brief Get a pointer to the last value in the dynamic array.
 * @param darr[in] The dynamic array.
 * @return A pointer to the last value in the dynamic array.
 */
static void* darr_back_ptr(DArrayT* darr);

/**
 * @brief Get a pointer to the last value in the dynamic array, safely.
 *
 * This function is like darr_back_ptr, but it will return NULL if the dynamic
 * array is empty.
 *
 * @param darr[in] The dynamic array.
 * @return A pointer to the last value in the dynamic array, or NULL if the
 * dynamic array is empty.
 */
static void* darr_back_ptr_safe(DArrayT* darr);

/**
 * @brief Check if the dynamic array is empty.
 * @param darr[in] The dynamic array.
 * @return TRUE if the dynamic array is empty, FALSE otherwise.
 */
static BOOL darr_is_empty(DArrayT* darr);

/**
 * @brief Get the length of the dynamic array.
 * @param darr[in] The dynamic array.
 * @return The length of the dynamic array.
 */
static size_t darr_length(DArrayT* darr);

/**
 * @brief Get the capacity of the dynamic array.
 * @param darr[in] The dynamic array.
 * @return The capacity of the dynamic array.
 */
static size_t darr_capacity(DArrayT* darr);

/**
 * @brief Erase an element from the dynamic array.
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to erase.
 */
static void darr_erase(DArrayT* darr, size_t index);

/**
 * @brief Erase an element from the dynamic array, safely.
 *
 * This function is like darr_erase, but it will do nothing if the index is out
 * of bounds of the dynamic array.
 *
 * @param darr[in] The dynamic array.
 * @param index[in] The index of the element to erase.
 */
static void darr_erase_safe(DArrayT* darr, size_t index);

/**
 * @brief Shrink the capacity of the dynamic array to its length.
 * @param darr[in] The dynamic array.
 */
static void darr_shrink_to_fit(DArrayT* darr);

/**
 * @brief Reserve space for a number of elements in the dynamic array.
 * @param darr[in] The dynamic array.
 * @param newCapacity[in] The new capacity of the dynamic array.
 */
static void darr_reserve(DArrayT* darr, size_t newCapacity);

/**
 * @brief Pop a value from the dynamic array.
 * @param darr[in] The dynamic array.
 * @return A pointer to the popped value.
 */
static void* darr_pop(DArrayT* darr);
/**
 * @brief Pop a value from the dynamic array, safely.
 *
 * This function is like darr_pop, but it will return NULL if the dynamic array
 * is empty.
 *
 * @param darr[in] The dynamic array.
 * @return A pointer to the popped value, or NULL if the dynamic array is empty.
 */
static void* darr_pop_safe(DArrayT* darr);

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

inline static void darr_insert_generic(DArrayT* darr, size_t index, void* valuePtr)
{
    if (index < darr->length + 1)
    {
        darr_resize(darr, darr->length + 1);
        if (index < darr->length)
        {
            void* resultPtr = NULL;
            if (NULL != darr->data)
            {
                size_t len = (darr->length) - (index + 1);
                void* next = (void*) &darr->data[index * darr->elementSize + darr->elementSize];
                void* current = &darr->data[index * darr->elementSize];
                resultPtr = CMEMCPY(next, current, len * darr->elementSize);
                if (NULL != resultPtr) { CMEMCPY(&darr->data[index * darr->elementSize], valuePtr, darr->elementSize); }
            }
        }
    }
}

inline static void darr_insert_u32(DArrayU32T* darr, size_t index, uint32_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void darr_insert_i32(DArrayI32T* darr, size_t index, int32_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void darr_insert_u16(DArrayU16T* darr, size_t index, uint16_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void darr_insert_i16(DArrayI16T* darr, size_t index, int16_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void darr_insert_u8(DArrayU8T* darr, size_t index, uint8_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void darr_insert_i8(DArrayI8T* darr, size_t index, int8_t value)
{
    darr_insert_generic(darr, index, &value);
}

inline static void* darr_get_ptr(DArrayT* darr, size_t index) { return &darr->data[index * darr->elementSize]; }

inline static void* darr_get_ptr_safe(DArrayT* darr, size_t index)
{
    void* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_ptr(darr, index); }
    return result;
}

inline static uint32_t darr_get_u32(DArrayU32T* darr, size_t index) { return *((uint32_t*) darr_get_ptr(darr, index)); }

inline static uint32_t darr_get_u32_safe(DArrayU32T* darr, size_t index)
{
    uint32_t result = 0;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_u32(darr, index); }
    return result;
}

inline static int32_t darr_get_i32(DArrayI32T* darr, size_t index) { return *((int32_t*) darr_get_ptr(darr, index)); }

inline static int32_t darr_get_i32_safe(DArrayI32T* darr, size_t index)
{
    int32_t result = 0;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i32(darr, index); }
    return result;
}

inline static uint32_t* darr_get_u32_ptr(DArrayU32T* darr, size_t index)
{
    return ((uint32_t*) darr_get_ptr(darr, index));
}

inline uint32_t* darr_get_u32_ptr_safe(DArrayU32T* darr, size_t index)
{
    uint32_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_u32_ptr(darr, index); }
    return result;
}

inline static int32_t* darr_get_i32_ptr(DArrayI32T* darr, size_t index)
{
    return ((int32_t*) darr_get_ptr(darr, index));
}

inline int32_t* darr_get_i32_ptr_safe(DArrayU32T* darr, size_t index)
{
    int32_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i32_ptr(darr, index); }
    return result;
}

inline static uint16_t darr_get_u16(DArrayU16T* darr, size_t index) { return *((uint16_t*) darr_get_ptr(darr, index)); }

inline static int16_t darr_get_i16(DArrayI16T* darr, size_t index) { return *((int16_t*) darr_get_ptr(darr, index)); }

inline static uint16_t* darr_get_u16_ptr(DArrayU16T* darr, size_t index)
{
    return ((uint16_t*) darr_get_ptr(darr, index));
}

inline static int16_t* darr_get_i16_ptr(DArrayI16T* darr, size_t index)
{
    return ((int16_t*) darr_get_ptr(darr, index));
}

inline static int16_t darr_get_i16_safe(DArrayI16T* darr, size_t index)
{
    int16_t result = 0;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i16(darr, index); }
    return result;
}

inline static uint16_t* darr_get_u16_ptr_safe(DArrayU16T* darr, size_t index)
{
    uint16_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_u16_ptr(darr, index); }
    return result;
}

inline static int16_t* darr_get_i16_ptr_safe(DArrayI16T* darr, size_t index)
{
    int16_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i16_ptr(darr, index); }
    return result;
}

inline static uint8_t darr_get_u8(DArrayU8T* darr, size_t index) { return *((uint8_t*) darr_get_ptr(darr, index)); }

inline static int8_t darr_get_i8(DArrayI8T* darr, size_t index) { return *((int8_t*) darr_get_ptr(darr, index)); }

inline static uint8_t* darr_get_u8_ptr(DArrayU8T* darr, size_t index) { return ((uint8_t*) darr_get_ptr(darr, index)); }

inline static int8_t* darr_get_i8_ptr(DArrayI8T* darr, size_t index) { return ((int8_t*) darr_get_ptr(darr, index)); }

inline static uint8_t darr_get_u8_safe(DArrayU8T* darr, size_t index)
{
    uint8_t result = 0;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_u8(darr, index); }
    return result;
}

inline static int8_t darr_get_i8_safe(DArrayI8T* darr, size_t index)
{
    int8_t result = 0;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i8(darr, index); }
    return result;
}

inline static uint8_t* darr_get_u8_ptr_safe(DArrayU8T* darr, size_t index)
{
    uint8_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_u8_ptr(darr, index); }
    return result;
}

inline static int8_t* darr_get_i8_ptr_safe(DArrayI8T* darr, size_t index)
{
    int8_t* result = NULL;
    if (NULL == darr) {}
    else if (index < darr->length) { result = darr_get_i8_ptr(darr, index); }
    return result;
}

inline static void* darr_front_ptr(DArrayT* darr) { return darr_get_ptr(darr, 0); }

inline static void* darr_back_ptr(DArrayT* darr) { return darr_get_ptr(darr, darr->length - 1); }

inline static void* darr_front_ptr_safe(DArrayT* darr)
{
    void* result = NULL;
    if (NULL == darr) {}
    else if (darr->length > 0) { result = darr_get_ptr(darr, 0); }
    return result;
}

inline static void* darr_back_ptr_safe(DArrayT* darr)
{
    void* result = NULL;
    if (NULL == darr) {}
    else if (darr->length > 0) { result = darr_get_ptr(darr, darr->length - 1); }
    return result;
}

inline static void darr_push_u32(DArrayU32T* darr, uint32_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_i32(DArrayI32T* darr, int32_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_u16(DArrayU16T* darr, uint16_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_i16(DArrayI16T* darr, int16_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_u8(DArrayU8T* darr, uint8_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_i8(DArrayI8T* darr, int8_t value) { darr_push_generic(darr, &value); }

inline static void darr_push_generic(DArrayT* darr, void* value)
{
    darr_resize(darr, darr->length + 1);
    CMEMCPY(&darr->data[darr->length * darr->elementSize - darr->elementSize], value, darr->elementSize);
}

inline static void darr_push_ptr(DArrayT* darr, void* value)
{
    darr_resize(darr, darr->length + 1);
    CMEMCPY(&darr->data[darr->length * darr->elementSize - darr->elementSize], &value, darr->elementSize);
}

inline static BOOL darr_is_empty(DArrayT* darr) { return (0u == darr->length); }

inline static size_t darr_length(DArrayT* darr) { return darr->length; }

inline static size_t darr_capacity(DArrayT* darr) { return darr->capacity; }

inline static void darr_resize(DArrayT* darr, size_t newLength)
{
    if (newLength > darr->length)
    {
        if (newLength > darr->capacity)
        {
            int8_t* resultPtr;
            size_t newCapacity = newLength * DARRAY_RESIZE_FACTOR;

            if (NULL == darr->data) { resultPtr = (int8_t*) CMALLOC(newCapacity * (darr->elementSize)); }
            else { resultPtr = (int8_t*) CREALLOC(darr->data, newCapacity * (darr->elementSize)); }
            if (NULL == resultPtr) { LOG_ERROR("Can not allocate dynamic darray!\n"); }
            if (NULL != resultPtr)
            {
                darr->data = resultPtr;
                darr->length = newLength;
                darr->capacity = newCapacity;
            }
        }
        else { darr->length = newLength; }
    }
    else { darr->length = newLength; }
}

inline static void darr_destroy(DArrayT* darr)
{
    CFREE(darr->data, darr->length);
    CFREE(darr, sizeof(darr));
}

inline static DArrayU32T* darr_create_u32() { return darr_create_generic(sizeof(uint32_t)); }

inline static DArrayI32T* darr_create_i32() { return darr_create_generic(sizeof(int32_t)); }

inline static DArrayU16T* darr_create_u16() { return darr_create_generic(sizeof(uint16_t)); }

inline static DArrayI16T* darr_create_i16() { return darr_create_generic(sizeof(int16_t)); }

inline static DArrayU8T* darr_create_u8() { return darr_create_generic(sizeof(uint8_t)); }

inline static DArrayI8T* darr_create_i8() { return darr_create_generic(sizeof(int8_t)); }

inline static DArrayT* darr_create_generic(size_t typeSize)
{
    DArrayT* result = NULL;

    if (typeSize > 0) { result = (DArrayT*) CMALLOC(sizeof(DArrayT)); }
    if (NULL == result) { LOG_ERROR("Can not allocate dynamic darray!\n"); }
    else
    {
        result->length = 0;                        // set length to 0
        result->capacity = DARRAY_INITIAL_CAPACITY;// set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = typeSize;            // set element size to stride
        int8_t* dataPtr = (int8_t*) CMALLOC(typeSize);
        if (NULL == dataPtr) { LOG_ERROR("Can not allocate darray data buffer!\n"); }
        else { result->data = dataPtr; }
    }

    return result;
}

inline static void darr_erase(DArrayT* darr, size_t index)
{
    int8_t* resultPtr = NULL;
    if (NULL != darr->data)
    {
        void* dest = &(darr->data[index]);
        void* src = &(darr->data[index + darr->elementSize]);
        resultPtr = (int8_t*) CMEMCPY(dest, src, (darr->length - index));
        if (NULL == resultPtr) { LOG_ERROR("Can not copy darray darrfer!\n"); }
    }
    if (NULL != resultPtr) { darr->length -= 1; }
}

inline static void darr_erase_safe(DArrayT* darr, size_t index)
{
    if (NULL == darr) {}
    else if (index < darr->length) { darr_erase(darr, index); }
}

inline static void darr_shrink_to_fit(DArrayT* darr)
{
    if (darr->capacity > darr->length)
    {
        int8_t* resultPtr = NULL;
        if (NULL != darr->data) { resultPtr = (int8_t*) CREALLOC(darr->data, darr->length * darr->elementSize); }
        if (NULL == resultPtr) { LOG_ERROR("Can not reallocate darray darrfer!\n"); }
        if (NULL != resultPtr)
        {
            darr->capacity = darr->length;
            darr->data = resultPtr;
        }
    }
}

inline static void darr_reserve(DArrayT* darr, size_t newCapacity)
{
    if (newCapacity > darr->capacity)
    {
        int8_t* resultPtr;

        if (NULL == darr->data) { resultPtr = (int8_t*) CMALLOC(newCapacity * darr->elementSize); }
        else { resultPtr = (int8_t*) CREALLOC(darr->data, newCapacity * darr->elementSize); }

        if (NULL == resultPtr) { LOG_ERROR("Can not allocate darray darrfer!\n"); }
        if (NULL != resultPtr)
        {
            darr->data = resultPtr;
            darr->capacity = newCapacity;
        }
    }
}

inline static void* darr_pop(DArrayT* darr)
{
    void* valuePtr = NULL;
    valuePtr = darr_back_ptr(darr);
    darr->length -= 1;
    return valuePtr;
}

inline static void* darr_pop_safe(DArrayT* darr)
{
    void* valuePtr = NULL;
    if (NULL == darr) {}
    else if (darr->length > 0) { valuePtr = darr_pop(darr); }
    else { LOG_ERROR("Can not pop from darray with size < 0!\n"); }
    return valuePtr;
}
#endif// DARRAY_HEADER
