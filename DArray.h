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
#include "STDTypes.h"

/***********************************************************************************************************************
Macro Definitions
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

#define DArray_Reserve( arr, capacity )                                                                                \
    arr_reserve( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, capacity )

#define DArray_Resize( arr, newLength )                                                                                \
    arr_resize( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, newLength )

#define DArray_Push( arr, value )                                                                                      \
    DArray_Resize( arr, arr.length + 1 );                                                                              \
    arr.data[ arr.length - 1 ] = value

#define DArray_Insert( arr, index, value )                                                                             \
    DArray_Resize( arr, arr.length + 1 );                                                                              \
    if ( index < arr.length )                                                                                          \
    {                                                                                                                  \
        void* resultPtr = NULL;                                                                                        \
        if ( NULL != arr.data )                                                                                        \
        {                                                                                                              \
            size_t len = ( arr.length ) - ( index + 1 );                                                               \
            void* next = &arr.data[ index + 1 ];                                                                       \
            void* current = &arr.data[ index ];                                                                        \
            resultPtr = CMEMCPY( next, current, len * arr.elementSize );                                               \
            if ( NULL != resultPtr ) { arr.data[ index ] = value; }                                                    \
        }                                                                                                              \
    }

#define DArray_Pop( arr )                                                                                              \
    arr.data[ arr.length - 1 ];                                                                                        \
    arr_resize( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, arr.length - 1 )

#define DArray_Get( arr, index ) arr.data[ index ]
#define DArray_Front( arr ) arr.data[ 0 ]
#define DArray_Back( arr ) arr.data[ arr.length - 1 ]

#define DArray_Empty( arr ) ( 0 == arr.length )

#define DArray_Destroy( arr )                                                                                          \
    CFREE( arr.data, arr.capacity );                                                                                   \
    arr.length = 0;                                                                                                    \
    arr.capacity = 0;                                                                                                  \
    arr.data = NULL

#define DArray_Shrink_To_Fit( arr ) arr_shrinkToFit( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity )

#define DArray_Erase( arr, index ) arr_erase( ( void** ) &arr.data, &arr.length, arr.elementSize, &arr.capacity, index )

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

inline static void arr_erase( void** buf, size_t* length, const size_t elementSize, size_t* capacity, size_t index )
{
    if ( index < *length )
    {
        void* resultPtr = NULL;
        if ( NULL != *buf )
        {
            void* dest = &( ( *buf )[ index ] );
            void* src = &( ( *buf )[ index + elementSize ] );
            resultPtr = CMEMCPY( dest, src, ( *length - index ) );
        }
        if ( NULL != resultPtr ) { *length -= 1; }
    }
}

inline static void arr_insert( void** buf, size_t* length, const size_t elementSize, size_t* capacity, uint32_t index,
                               void* element )
{
    void* src = &( ( *buf )[ index ] );
    void* dest = &( ( *buf )[ index + elementSize ] );
    void* resultPtr = NULL;

    resultPtr = CMEMCPY( dest, src, ( *length - index - 1 ) );

    if ( NULL != resultPtr ) { resultPtr = CMEMCPY( src, element, elementSize ); }
}

inline static void arr_shrinkToFit( void** buf, size_t* length, const size_t elementSize, size_t* capacity )
{
    if ( *capacity > *length )
    {
        void* resultPtr = NULL;
        if ( NULL != *buf ) { resultPtr = CREALLOC( *buf, *length * elementSize ); }
        if ( NULL != resultPtr )
        {
            *capacity = *length;
            *buf = resultPtr;
        }
    }
}

inline static void arr_reserve( void** buf, size_t* length, const size_t elementSize, size_t* capacity,
                                size_t newCapacity )
{
    if ( newCapacity > *capacity )
    {
        void* resultPtr;

        if ( NULL == *buf ) { resultPtr = CMALLOC( newCapacity * elementSize ); }
        else { resultPtr = CREALLOC( *buf, newCapacity * elementSize ); }

        if ( NULL != resultPtr )
        {
            *buf = resultPtr;
            *capacity = newCapacity;
        }
    }
}

inline static void arr_resize( void** buf, size_t* length, const size_t elementSize, size_t* capacity,
                               size_t newLength )
{
    if ( newLength > *length )
    {
        if ( newLength > *capacity )
        {
            void* resultPtr;
            size_t newCapacity = newLength * 2;

            if ( NULL == *buf ) { resultPtr = CMALLOC( newCapacity * elementSize ); }
            else { resultPtr = CREALLOC( *buf, newCapacity * elementSize ); }

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
#endif// DARRAY_HEADER