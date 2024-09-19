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
#include "DString.h"
#include "STDTypes.h"

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

#define DARRAY_INITIAL_CAPACITY 1u
#define DARRAY_RESIZE_FACTOR 2u
#define DARRAY_LENGTH_OFFSET 0u
#define DARRAY_LENGTH_SIZE sizeof( size_t )
#define DARRAY_CAPACITY_OFFSET DARRAY_LENGTH_OFFSET + DARRAY_LENGTH_SIZE
#define DARRAY_CAPACITY_SIZE sizeof( size_t )
#define DARRAY_ELEMENT_SIZE_OFFSET DARRAY_CAPACITY_OFFSET + DARRAY_CAPACITY_SIZE
#define DARRAY_ELEMENT_SIZE_SIZE sizeof( size_t )
#define DARRAY_DATA_OFFSET DARRAY_ELEMENT_SIZE_OFFSET + DARRAY_ELEMENT_SIZE_SIZE

#define DArray_t( t, name ) t* name

#define DArray_Init( type ) arr_create( sizeof( type ) )
#define DStrArray_Init() str_arr_create( sizeof( int8_t** ) )

#define DArray_Length( arr ) ( ( _DArrayType* ) arr )->length
#define DArray_Data( arr ) ( ( _DArrayType* ) arr )->data
#define DArray_Size( arr ) ( sizeof( _DArrayType ) + DArrayLength( arr ) * ( _DArrayType* ) arr->elementSize )
#define DArray_Capacity( arr ) ( ( _DArrayType* ) arr )->capacity
#define DArray_ElementSize( arr ) ( ( _DArrayType* ) arr )->elementSize

#define DArray_Reserve( arr, capacity ) arr_reserve( ( _DArrayType* ) &arr, capacity )

#define DArray_Resize( arr, newLength ) arr_resize( arr, newLength )

#define DArray_Push( arr, value )                                                                                      \
    DArray_Resize( arr, arr->length + 1 );                                                                             \
    DArray_Memset( arr, arr->length - 1, value )

#define DArray_PushStr( arr, ptr )                                                                                     \
    DArray_Resize( ( _DArrayType* ) arr, DArray_Length( ( _DArrayType* ) arr ) + 1 );                                  \
    ( ( int8_t** ) DArray_Data( arr ) )[ ( DArray_Length( arr ) - 1 ) ] = ptr;

#define DArray_Insert( arr, index, value )                                                                             \
    {                                                                                                                  \
        DArray_Resize( arr, arr->length + 1 );                                                                         \
        if ( index < arr->length )                                                                                     \
        {                                                                                                              \
            void* resultPtr = NULL;                                                                                    \
            if ( NULL != arr->data )                                                                                   \
            {                                                                                                          \
                size_t len = ( arr->length ) - ( index + 1 );                                                          \
                void* next = ( void* ) &arr->data[ index * arr->elementSize + arr->elementSize ];                      \
                void* current = &arr->data[ index * arr->elementSize ];                                                \
                resultPtr = CMEMCPY( next, current, len * arr->elementSize );                                          \
                if ( NULL != resultPtr ) { DArray_Memset( arr, index, value ); }                                       \
            }                                                                                                          \
        }                                                                                                              \
    }
#define DArray_Pop( arr ) arr_pop( arr )

#define DArray_Get( arr, index ) &( ( _DArrayType* ) arr )->data[ index * ( ( _DArrayType* ) arr )->elementSize ]
#define DArray_GetStr( arr, index ) ( ( int8_t** ) ( ( ( _DArrayType* ) arr )->data ) )[ ( index ) ]

#define DArray_Front( arr ) &( ( _DArrayType* ) arr )->data[ 0 ]
#define DArray_Back( arr ) DArray_Get( arr, ( ( ( _DArrayType* ) arr )->length - 1 ) )

#define DArray_Empty( arr ) ( 0 == arr->length )

#define DArray_Destroy( arr )                                                                                          \
    CFREE( arr->data, arr->length );                                                                                   \
    CFREE( arr, sizeof( arr ) )

#define DStrArray_Destroy( arr ) str_arr_destroy( ( _DArrayType* ) arr )

#define DArray_Shrink_To_Fit( arr ) arr_shring_to_fit( arr )

#define DArray_Erase( arr, index ) arr_erase( arr, index )

#define DARRAY_HEADER_SIZE sizeof( size_t ) * 3

#define DArray_Memset( arr, index, value )                                                                             \
    for ( size_t currElementIndex = 0; currElementIndex < arr->elementSize; currElementIndex++ )                       \
    {                                                                                                                  \
        CMEMSET( &arr->data[ ( index ) * arr->elementSize + currElementIndex ],                                        \
                 ( ( value >> ( currElementIndex * 8 ) ) & 0xFF ), 1 );                                                \
    }

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

typedef struct {
    size_t length;
    size_t capacity;
    size_t elementSize;
    void* data;
} _DArrayType;

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/
inline static void arr_resize( _DArrayType* buf, size_t newLength )
{
    if ( newLength > buf->length )
    {
        if ( newLength > buf->capacity )
        {
            void* resultPtr;
            size_t newCapacity = newLength * 2;

            if ( NULL == buf->data ) { resultPtr = CMALLOC( newCapacity * ( buf->elementSize ) ); }
            else { resultPtr = CREALLOC( buf->data, newCapacity * ( buf->elementSize ) ); }
            if ( NULL == resultPtr ) { LOG_ERROR( "Can not allocate dynamic array!\n" ); }

            if ( NULL != resultPtr )
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

inline static void str_arr_destroy( _DArrayType* buf )
{
    if ( NULL != buf )
    {
        for ( size_t i = 0; i < DArray_Length( buf ); i++ )
        {
            int8_t* str = DArray_GetStr( buf, i );
            printf( "%s\n", str );
            CFREE( str, strlen( str ) + 1 );
        }
        if ( buf->data ) { CFREE( buf->data, buf->length ); }
        CFREE( ( void* ) buf, DARRAY_HEADER_SIZE + sizeof( int8_t* ) );
    }
}

inline static void* str_arr_create( size_t stride )
{
    _DArrayType* result = NULL;

    result = ( _DArrayType* ) CMALLOC( sizeof( _DArrayType ) );

    if ( NULL == result ) { LOG_ERROR( "Can not allocate dynamic array!\n" ); }
    else
    {
        result->length = 0;          // set length to 0
        result->capacity = 0;        // set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = stride;// set element size to stride
        result->data = NULL;
    }

    return ( void* ) result;
}

inline static void* arr_create( size_t stride )
{
    _DArrayType* result = NULL;

    result = ( _DArrayType* ) CMALLOC( sizeof( _DArrayType ) );

    if ( NULL == result ) { LOG_ERROR( "Can not allocate dynamic array!\n" ); }
    else
    {
        result->length = 0;                        // set length to 0
        result->capacity = DARRAY_INITIAL_CAPACITY;// set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = stride;              // set element size to stride
    }
    uint8_t* dataPtr = ( uint8_t* ) CMALLOC( stride );
    if ( NULL == result ) { LOG_ERROR( "Can not allocate array buffer!\n" ); }
    else { result->data = dataPtr; }

    return ( void* ) result;
}

inline static void arr_erase( _DArrayType* buf, size_t index )
{
    if ( index < buf->length )
    {
        void* resultPtr = NULL;
        if ( NULL != buf->data )
        {
            void* dest = &( buf->data[ index ] );
            void* src = &( buf->data[ index + buf->elementSize ] );
            resultPtr = CMEMCPY( dest, src, ( buf->length - index ) );
            if ( NULL == resultPtr ) { LOG_ERROR( "Can not copy array buffer!\n" ); }
        }
        if ( NULL != resultPtr ) { buf->length -= 1; }
    }
}

inline static void arr_insert( _DArrayType* buf, uint32_t index, void* element )
{
    void* src = &( buf->data[ index ] );
    void* dest = &( buf->data[ index + buf->elementSize ] );
    void* resultPtr = NULL;

    resultPtr = CMEMCPY( dest, src, ( buf->length - index - 1 ) );

    if ( NULL == resultPtr ) { LOG_ERROR( "Can not copy array buffer!\n" ); }
    if ( NULL != resultPtr ) { resultPtr = CMEMCPY( src, element, buf->elementSize ); }
}

inline static void arr_shring_to_fit( _DArrayType* buf )
{
    if ( buf->capacity > buf->length )
    {
        void* resultPtr = NULL;
        if ( NULL != buf->data ) { resultPtr = CREALLOC( buf->data, buf->length * buf->elementSize ); }
        if ( NULL == resultPtr ) { LOG_ERROR( "Can not reallocate array buffer!\n" ); }
        if ( NULL != resultPtr )
        {
            buf->capacity = buf->length;
            buf->data = resultPtr;
        }
    }
}

inline static void arr_reserve( _DArrayType* buf, size_t newCapacity )
{
    if ( newCapacity > buf->capacity )
    {
        void* resultPtr;

        if ( NULL == buf->data ) { resultPtr = CMALLOC( newCapacity * buf->elementSize ); }
        else { resultPtr = CREALLOC( buf->data, newCapacity * buf->elementSize ); }

        if ( NULL == resultPtr ) { LOG_ERROR( "Can not allocate array buffer!\n" ); }
        if ( NULL != resultPtr )
        {
            buf->data = resultPtr;
            buf->capacity = newCapacity;
        }
    }
}

inline static void* arr_pop( _DArrayType* buf )
{
    void* valuePtr = NULL;
    if ( buf->length > 0 )
    {
        valuePtr = DArray_Back( buf );
        buf->length -= 1;
    }
    else { LOG_ERROR( "Can not pop from array with size < 0!\n" ); }
    return valuePtr;
}
#endif// DARRAY_HEADER
