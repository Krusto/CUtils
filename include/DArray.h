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

#define DARRAY_INITIAL_CAPACITY 1u
#define DARRAY_RESIZE_FACTOR 2u

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

typedef struct {
    size_t length;
    size_t capacity;
    size_t elementSize;
    int8_t* data;
} DArrayT;

typedef DArrayT DArrayU32T;
typedef DArrayT DArrayI32T;
typedef DArrayT DArrayU16T;
typedef DArrayT DArrayI16T;
typedef DArrayT DArrayU8T;
typedef DArrayT DArrayI8T;

/***********************************************************************************************************************
Static functions declaration
***********************************************************************************************************************/
static void darr_destroy(DArrayT* darr);
static DArrayU32T* darr_create_u32();
static DArrayI32T* darr_create_i32();
static DArrayU16T* darr_create_u16();
static DArrayI16T* darr_create_i16();
static DArrayU8T* darr_create_u8();
static DArrayI8T* darr_create_i8();
static DArrayT* darr_create_generic(size_t typeSize);
static void darr_push_u32(DArrayU32T* darr, uint32_t value);
static void darr_push_i32(DArrayI32T* darr, int32_t value);
static void darr_push_u16(DArrayU16T* darr, uint16_t value);
static void darr_push_i16(DArrayI16T* darr, int16_t value);
static void darr_push_u8(DArrayU8T* darr, uint8_t value);
static void darr_push_i8(DArrayI8T* darr, int8_t value);
static void darr_push_generic(DArrayT* darr, void* value);
static void darr_insert_u32(DArrayU32T* darr, size_t index, uint32_t value);
static void darr_insert_i32(DArrayI32T* darr, size_t index, int32_t value);
static void darr_insert_u16(DArrayU16T* darr, size_t index, uint16_t value);
static void darr_insert_i16(DArrayI16T* darr, size_t index, int16_t value);
static void darr_insert_u8(DArrayU8T* darr, size_t index, uint8_t value);
static void darr_insert_i8(DArrayI8T* darr, size_t index, int8_t value);
static void darr_insert_generic(DArrayT* darr, size_t index, void* valuePtr);
static uint32_t darr_get_u32(DArrayU32T* darr, size_t index);
static int32_t darr_get_i32(DArrayI32T* darr, size_t index);
static uint32_t* darr_get_u32_ptr(DArrayU32T* darr, size_t index);
static int32_t* darr_get_i32_ptr(DArrayI32T* darr, size_t index);
static uint16_t darr_get_u16(DArrayU16T* darr, size_t index);
static int16_t darr_get_i16(DArrayI16T* darr, size_t index);
static uint16_t* darr_get_u16_ptr(DArrayU16T* darr, size_t index);
static int16_t* darr_get_i16_ptr(DArrayI16T* darr, size_t index);
static uint8_t darr_get_u8(DArrayU8T* darr, size_t index);
static int8_t darr_get_i8(DArrayI8T* darr, size_t index);
static uint8_t* darr_get_u8_ptr(DArrayU8T* darr, size_t index);
static int8_t* darr_get_i8_ptr(DArrayI8T* darr, size_t index);
static void* darr_get_ptr(DArrayT* darr, size_t index);
static void darr_resize(DArrayT* darr, size_t newLength);
static void* darr_front_ptr(DArrayT* darr);
static void* darr_back_ptr(DArrayT* darr);
static BOOL darr_is_empty(DArrayT* darr);
static size_t darr_length(DArrayT* darr);
static size_t darr_capacity(DArrayT* darr);
static void darr_erase(DArrayT* darr, size_t index);
static void darr_shrink_to_fit(DArrayT* darr);
static void darr_reserve(DArrayT* darr, size_t newCapacity);
static void* darr_pop(DArrayT* darr);

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

inline static uint32_t darr_get_u32(DArrayU32T* darr, size_t index) { return *((uint32_t*) darr_get_ptr(darr, index)); }

inline static int32_t darr_get_i32(DArrayI32T* darr, size_t index) { return *((int32_t*) darr_get_ptr(darr, index)); }

inline static uint32_t* darr_get_u32_ptr(DArrayU32T* darr, size_t index)
{
    return ((uint32_t*) darr_get_ptr(darr, index));
}

inline static int32_t* darr_get_i32_ptr(DArrayI32T* darr, size_t index)
{
    return ((int32_t*) darr_get_ptr(darr, index));
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

inline static uint8_t darr_get_u8(DArrayU8T* darr, size_t index) { return *((uint8_t*) darr_get_ptr(darr, index)); }

inline static int8_t darr_get_i8(DArrayI8T* darr, size_t index) { return *((int8_t*) darr_get_ptr(darr, index)); }

inline static uint8_t* darr_get_u8_ptr(DArrayU8T* darr, size_t index) { return ((uint8_t*) darr_get_ptr(darr, index)); }

inline static int8_t* darr_get_i8_ptr(DArrayI8T* darr, size_t index) { return ((int8_t*) darr_get_ptr(darr, index)); }

inline static void* darr_front_ptr(DArrayT* darr) { return darr_get_ptr(darr, 0); }

inline static void* darr_back_ptr(DArrayT* darr) { return darr_get_ptr(darr, darr->length - 1); }

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
    if (index < darr->length)
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
    if (darr->length > 0)
    {
        valuePtr = darr_back_ptr(darr);
        darr->length -= 1;
    }
    else { LOG_ERROR("Can not pop from darray with size < 0!\n"); }
    return valuePtr;
}
#endif// DARRAY_HEADER
