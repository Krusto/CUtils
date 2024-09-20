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
#include "CMemory.h"

#ifndef uint32_t
#include "STDTypes.h"
#endif

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

#define DARRAY_INITIAL_CAPACITY 1u
#define DARRAY_RESIZE_FACTOR 2u

#define DArray_Create(type) arr_create(sizeof(type))

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

typedef struct {
    size_t length;
    size_t capacity;
    size_t elementSize;
    int8_t* data;
} DArrayT;

/***********************************************************************************************************************
Static functions declaration
***********************************************************************************************************************/
static void arr_insert_generic(DArrayT* arr, size_t index, void* valuePtr);
static void arr_insert_u32(DArrayT* arr, size_t index, uint32_t value);
static void arr_insert_i32(DArrayT* arr, size_t index, int32_t value);
static void arr_insert_u16(DArrayT* arr, size_t index, uint16_t value);
static void arr_insert_i16(DArrayT* arr, size_t index, int16_t value);
static void arr_insert_u8(DArrayT* arr, size_t index, uint8_t value);
static void arr_insert_i8(DArrayT* arr, size_t index, int8_t value);
static void arr_resize(DArrayT* buf, size_t newLength);
static void* arr_get_ptr(DArrayT* arr, size_t index);
static uint32_t arr_get_u32(DArrayT* arr, size_t index);
static int32_t arr_get_i32(DArrayT* arr, size_t index);
static uint32_t* arr_get_u32_ptr(DArrayT* arr, size_t index);
static int32_t* arr_get_i32_ptr(DArrayT* arr, size_t index);
static uint16_t arr_get_u16(DArrayT* arr, size_t index);
static int16_t arr_get_i16(DArrayT* arr, size_t index);
static uint16_t* arr_get_u16_ptr(DArrayT* arr, size_t index);
static int16_t* arr_get_i16_ptr(DArrayT* arr, size_t index);
static uint8_t arr_get_u8(DArrayT* arr, size_t index);
static int8_t arr_get_i8(DArrayT* arr, size_t index);
static uint8_t* arr_get_u8_ptr(DArrayT* arr, size_t index);
static int8_t* arr_get_i8_ptr(DArrayT* arr, size_t index);
static void* arr_front_ptr(DArrayT* arr);
static void* arr_back_ptr(DArrayT* arr);
static void arr_push_u32(DArrayT* arr, uint32_t value);
static void arr_push_i32(DArrayT* arr, int32_t value);
static void arr_push_u16(DArrayT* arr, uint16_t value);
static void arr_push_i16(DArrayT* arr, int16_t value);
static void arr_push_u8(DArrayT* arr, uint8_t value);
static void arr_push_i8(DArrayT* arr, int8_t value);
static void arr_push_generic(DArrayT* arr, void* value);
static BOOL arr_is_empty(DArrayT* buf);
static size_t arr_length(DArrayT* buf);
static size_t arr_capacity(DArrayT* buf);
static void arr_resize(DArrayT* buf, size_t newLength);
static void arr_destroy(DArrayT* buf);
static void* arr_create(size_t stride);
static void arr_erase(DArrayT* buf, size_t index);
static void arr_insert(DArrayT* buf, uint32_t index, void* element);
static void arr_shrink_to_fit(DArrayT* buf);
static void arr_reserve(DArrayT* buf, size_t newCapacity);
static void* arr_pop(DArrayT* buf);

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

inline static void arr_insert_generic(DArrayT* arr, size_t index, void* valuePtr)
{
    arr_resize(arr, arr->length + 1);
    if (index < arr->length)
    {
        void* resultPtr = NULL;
        if (NULL != arr->data)
        {
            size_t len = (arr->length) - (index + 1);
            void* next = (void*) &arr->data[index * arr->elementSize + arr->elementSize];
            void* current = &arr->data[index * arr->elementSize];
            resultPtr = CMEMCPY(next, current, len * arr->elementSize);
            if (NULL != resultPtr) { CMEMCPY(&arr[index], valuePtr, arr->elementSize); }
        }
    }
}

inline static void arr_insert_u32(DArrayT* arr, size_t index, uint32_t value)
{
    arr_insert_generic(arr, index, &value);
}

inline static void arr_insert_i32(DArrayT* arr, size_t index, int32_t value) { arr_insert_generic(arr, index, &value); }

inline static void arr_insert_u16(DArrayT* arr, size_t index, uint16_t value)
{
    arr_insert_generic(arr, index, &value);
}

inline static void arr_insert_i16(DArrayT* arr, size_t index, int16_t value) { arr_insert_generic(arr, index, &value); }

inline static void arr_insert_u8(DArrayT* arr, size_t index, uint8_t value) { arr_insert_generic(arr, index, &value); }

inline static void arr_insert_i8(DArrayT* arr, size_t index, int8_t value) { arr_insert_generic(arr, index, &value); }

inline static void* arr_get_ptr(DArrayT* arr, size_t index) { return &arr->data[index * arr->elementSize]; }

inline static uint32_t arr_get_u32(DArrayT* arr, size_t index) { return *((uint32_t*) arr_get_ptr(arr, index)); }

inline static int32_t arr_get_i32(DArrayT* arr, size_t index) { return *((int32_t*) arr_get_ptr(arr, index)); }

inline static uint32_t* arr_get_u32_ptr(DArrayT* arr, size_t index) { return ((uint32_t*) arr_get_ptr(arr, index)); }

inline static int32_t* arr_get_i32_ptr(DArrayT* arr, size_t index) { return ((int32_t*) arr_get_ptr(arr, index)); }

inline static uint16_t arr_get_u16(DArrayT* arr, size_t index) { return *((uint16_t*) arr_get_ptr(arr, index)); }

inline static int16_t arr_get_i16(DArrayT* arr, size_t index) { return *((int16_t*) arr_get_ptr(arr, index)); }

inline static uint16_t* arr_get_u16_ptr(DArrayT* arr, size_t index) { return ((uint16_t*) arr_get_ptr(arr, index)); }

inline static int16_t* arr_get_i16_ptr(DArrayT* arr, size_t index) { return ((int16_t*) arr_get_ptr(arr, index)); }

inline static uint8_t arr_get_u8(DArrayT* arr, size_t index) { return *((uint8_t*) arr_get_ptr(arr, index)); }

inline static int8_t arr_get_i8(DArrayT* arr, size_t index) { return *((int8_t*) arr_get_ptr(arr, index)); }

inline static uint8_t* arr_get_u8_ptr(DArrayT* arr, size_t index) { return ((uint8_t*) arr_get_ptr(arr, index)); }

inline static int8_t* arr_get_i8_ptr(DArrayT* arr, size_t index) { return ((int8_t*) arr_get_ptr(arr, index)); }

inline static void* arr_front_ptr(DArrayT* arr) { return arr_get_ptr(arr, 0); }

inline static void* arr_back_ptr(DArrayT* arr) { return arr_get_ptr(arr, arr->length - 1); }

inline static void arr_push_u32(DArrayT* arr, uint32_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_i32(DArrayT* arr, int32_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_u16(DArrayT* arr, uint16_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_i16(DArrayT* arr, int16_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_u8(DArrayT* arr, uint8_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_i8(DArrayT* arr, int8_t value) { arr_push_generic(arr, &value); }

inline static void arr_push_generic(DArrayT* arr, void* value)
{
    arr_resize(arr, arr->length + 1);
    CMEMCPY(&arr->data[arr->length - 1], &value, arr->elementSize);
}

inline static BOOL arr_is_empty(DArrayT* buf) { return (0u == buf->length); }

inline static size_t arr_length(DArrayT* buf) { return buf->length; }

inline static size_t arr_capacity(DArrayT* buf) { return buf->capacity; }

inline static void arr_resize(DArrayT* buf, size_t newLength)
{
    if (newLength > buf->length)
    {
        if (newLength > buf->capacity)
        {
            void* resultPtr;
            size_t newCapacity = newLength * DARRAY_RESIZE_FACTOR;

            if (NULL == buf->data) { resultPtr = CMALLOC(newCapacity * (buf->elementSize)); }
            else { resultPtr = CREALLOC(buf->data, newCapacity * (buf->elementSize)); }
            if (NULL == resultPtr) { LOG_ERROR("Can not allocate dynamic array!\n"); }
            if (NULL != resultPtr)
            {
                buf->data = resultPtr;
                buf->length = newLength;
                buf->capacity = newCapacity;
            }
        }
        else { buf->length = newLength; }
    }
    else { buf->length = newLength; }
}

inline static void arr_destroy(DArrayT* buf)
{
    CFREE(buf->data, buf->length);
    CFREE(buf, sizeof(buf));
}

inline static void* arr_create(size_t stride)
{
    DArrayT* result = NULL;

    result = (DArrayT*) CMALLOC(sizeof(DArrayT));

    if (NULL == result) { LOG_ERROR("Can not allocate dynamic array!\n"); }
    else
    {
        result->length = 0;                        // set length to 0
        result->capacity = DARRAY_INITIAL_CAPACITY;// set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = stride;              // set element size to stride
    }
    uint8_t* dataPtr = (uint8_t*) CMALLOC(stride);
    if (NULL == result) { LOG_ERROR("Can not allocate array buffer!\n"); }
    else { result->data = dataPtr; }

    return (void*) result;
}

inline static void arr_erase(DArrayT* buf, size_t index)
{
    if (index < buf->length)
    {
        void* resultPtr = NULL;
        if (NULL != buf->data)
        {
            void* dest = &(buf->data[index]);
            void* src = &(buf->data[index + buf->elementSize]);
            resultPtr = CMEMCPY(dest, src, (buf->length - index));
            if (NULL == resultPtr) { LOG_ERROR("Can not copy array buffer!\n"); }
        }
        if (NULL != resultPtr) { buf->length -= 1; }
    }
}

inline static void arr_insert(DArrayT* buf, uint32_t index, void* element)
{
    void* src = &(buf->data[index]);
    void* dest = &(buf->data[index + buf->elementSize]);
    void* resultPtr = NULL;

    resultPtr = CMEMCPY(dest, src, (buf->length - index - 1));

    if (NULL == resultPtr) { LOG_ERROR("Can not copy array buffer!\n"); }
    if (NULL != resultPtr) { resultPtr = CMEMCPY(src, element, buf->elementSize); }
}

inline static void arr_shrink_to_fit(DArrayT* buf)
{
    if (buf->capacity > buf->length)
    {
        void* resultPtr = NULL;
        if (NULL != buf->data) { resultPtr = CREALLOC(buf->data, buf->length * buf->elementSize); }
        if (NULL == resultPtr) { LOG_ERROR("Can not reallocate array buffer!\n"); }
        if (NULL != resultPtr)
        {
            buf->capacity = buf->length;
            buf->data = resultPtr;
        }
    }
}

inline static void arr_reserve(DArrayT* buf, size_t newCapacity)
{
    if (newCapacity > buf->capacity)
    {
        void* resultPtr;

        if (NULL == buf->data) { resultPtr = CMALLOC(newCapacity * buf->elementSize); }
        else { resultPtr = CREALLOC(buf->data, newCapacity * buf->elementSize); }

        if (NULL == resultPtr) { LOG_ERROR("Can not allocate array buffer!\n"); }
        if (NULL != resultPtr)
        {
            buf->data = resultPtr;
            buf->capacity = newCapacity;
        }
    }
}

inline static void* arr_pop(DArrayT* buf)
{
    void* valuePtr = NULL;
    if (buf->length > 0)
    {
        valuePtr = arr_back_ptr(buf);
        buf->length -= 1;
    }
    else { LOG_ERROR("Can not pop from array with size < 0!\n"); }
    return valuePtr;
}
#endif// DARRAY_HEADER
