#ifndef CARRAY_HEADER
#define CARRAY_HEADER
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
#include "STDTypes.h"

/***********************************************************************************************************************
Type Definitions
***********************************************************************************************************************/


#define DArray_t( t, name )                                                                                            \
    typedef struct {                                                                                                   \
        t* data;                                                                                                       \
        size_t length;                                                                                                 \
        size_t capacity;                                                                                               \
        size_t elementSize;                                                                                            \
    } DArray_##t##_t;                                                                                                  \
    DArray_##t##_t name;                                                                                               \
    name.elementSize = sizeof( t );                                                                                    \
    name.length = 0;                                                                                                   \
    name.data = NULL;                                                                                                  \
    name.capacity = 0

#define DArray_Init( arr )                                                                                             \
    arr.length = 0;                                                                                                    \
    arr.data = NULL;                                                                                                   \
    arr.capacity = 0;

#define DArray_Length( arr ) arr.length
#define DArray_Data( arr ) arr.data
#define DArray_Size( arr ) arr.length* arr.elementSize
#define DArray_Capacity( arr ) arr.capacity

#define DArray_Resize( arr, newLength )                                                                                \
    Arr_Resize( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, newLength )

#define DArray_Push( arr, value )                                                                                      \
    DArray_Resize( arr, arr.length + 1 );                                                                              \
    arr.data[ arr.length - 1 ] = value

#define DArray_Pop( arr )                                                                                              \
    arr.data[ arr.length - 1 ];                                                                                        \
    Arr_Resize( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, arr.length - 1 )

#define DArray_Get( arr, index ) arr.data[ index ]

#define DArray_Destroy( arr )                                                                                          \
    free( arr.data );                                                                                                  \
    arr.length = 0;                                                                                                    \
    arr.capacity = 0;                                                                                                  \
    arr.data = NULL

#define DArray_Shrink_To_Fit( arr ) Arr_ShrinkToFit( (void**)&arr.data, &arr.length, arr.elementSize, &arr.capacity )

inline static void Arr_ShrinkToFit( void** buf, size_t* length, const size_t elementSize, size_t* capacity )
{
    if ( *capacity > *length )
    {
        void* resultPtr = NULL;
        if ( NULL != *buf ) { resultPtr = realloc( *buf, *length * elementSize ); }
        if ( NULL != resultPtr )
        {
            *capacity = *length;
            *buf = resultPtr;
        }
    }
}

inline static void Arr_Resize( void** buf, size_t* length, const size_t elementSize, size_t* capacity,
                               size_t newLength )
{
    if ( newLength > *length )
    {
        if ( newLength > *capacity )
        {
            void* resultPtr;
            size_t newCapacity = newLength * 2;

            if ( NULL == *buf ) { resultPtr = malloc( newCapacity * elementSize ); }
            else { resultPtr = realloc( *buf, newCapacity * elementSize ); }

            if ( NULL != resultPtr )
            {
                *buf = resultPtr;
                *length = newLength;
                *capacity = newCapacity;
            }
        }
        else { *length = newLength; }
    }
    else { *length = newLength; }
}
#endif// CARRAY_HEADER