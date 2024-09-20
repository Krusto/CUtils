#ifndef DSTRING_HEADER
#define DSTRING_HEADER
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
 * C Dynamic String Header
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CLog.h"
#include "STDTypes.h"

#ifndef NO_STD_MALLOC
#include <stdlib.h>
#include <string.h>
#endif
#include "CMemory.h"
#include "DArray.h"


/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

#define DSTRING_INITIAL_CAPACITY 1u
#define DSTRING_RESIZE_FACTOR 2u
#define DSTRING_LENGTH_OFFSET 0u
#define DSTRING_LENGTH_SIZE sizeof( size_t )
#define DSTRING_CAPACITY_OFFSET DSTRING_LENGTH_OFFSET + DSTRING_LENGTH_SIZE
#define DSTRING_CAPACITY_SIZE sizeof( size_t )
#define DSTRING_ELEMENT_SIZE_OFFSET DSTRING_CAPACITY_OFFSET + DSTRING_CAPACITY_SIZE
#define DSTRING_ELEMENT_SIZE_SIZE sizeof( size_t )
#define DSTRING_DATA_OFFSET DSTRING_ELEMENT_SIZE_OFFSET + DSTRING_ELEMENT_SIZE_SIZE
#define DSTRING_NULL_TERMINATION_LENGTH 1u
#define DSTRING_NULL_TERMINATOR '\0';

#define DString_Create( str, size ) str_create( str, size )

#define DString_Length( str ) ( ( DStringT* ) str )->length
#define DString_Data( str ) ( ( DStringT* ) str )->data
#define DString_Size( str ) ( sizeof( DStringT ) + DString_Length( str ) + DSTRING_NULL_TERMINATION_LENGTH )
#define DString_Capacity( str ) ( ( DStringT* ) str )->capacity

#define DString_Reserve( str, capacity ) str_reserve( ( DStringT* ) &str, capacity )
#define DString_Resize( str, newLength ) str_resize( str, newLength )

#define DString_Get( str, index ) ( ( ( ( DStringT* ) str )->data )[ ( index ) ] )
#define DString_GetP( str, index ) &( ( ( ( DStringT* ) str )->data )[ ( index ) ] )

#define DString_Front( str ) DString_Get( str, 0 )
#define DString_FrontP( str ) DString_GetP( str, 0 )
#define DString_Back( str ) DString_Get( str, DString_Length( str ) - 1 )
#define DString_BackP( str ) DString_GetP( str, DString_Length( str ) - 1 )

#define DString_IsEmpty( str ) str_is_empty( str )

#define DString_Destroy( str ) str_destroy( str )

#define DString_Shrink_To_Fit( str ) str_shring_to_fit( str )

#define DString_Erase( str, index ) str_erase( str, index )

#define DStrArray_Init() str_arr_create()

#define DArray_PushStr( arr, ptr )                                                                                     \
    DArray_Resize( ( DArrayT* ) arr, DArray_Length( ( DArrayT* ) arr ) + 1 );                                          \
    ( ( int8_t** ) DArray_Data( arr ) )[ ( DArray_Length( arr ) - 1 ) ] = ptr;

#define DArray_GetStr( arr, index ) ( ( int8_t** ) ( ( ( DArrayT* ) arr )->data ) )[ ( index ) ]

#define DStrArray_Destroy( arr ) str_arr_destroy( ( DArrayT* ) arr )

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

typedef struct {
    size_t length;
    size_t capacity;
    int8_t* data;
} DStringT;

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

inline static BOOL is_str_empty( DStringT* str ) { return ( 0 == str->length ); }

inline static DStringT* str_create( const int8_t* str, size_t size )
{
    DStringT* result = NULL;

    result = ( DStringT* ) CMALLOC( sizeof( DStringT ) );

    if ( NULL == result ) { LOG_ERROR( "Can not allocate dynamic string!\n" ); }
    else
    {
        result->length = 0;  // set length to 0
        result->capacity = 0;// set capacity to DARRAY_INITIAL_CAPACITY
        result->data = NULL;
    }
    if ( size > 0 )
    {
        int8_t* memory = ( int8_t* ) CMALLOC( size + 1 );
        int8_t* resultPtr = NULL;
        resultPtr = ( int8_t* ) CMEMCPY( memory, str, size );
        if ( NULL == resultPtr ) { LOG_ERROR( "Can not create string!\n" ); }
        memory[ size ] = '\0';
        result->data = memory;
        result->length = size;
        result->capacity = size;
    }
    return result;
}

inline static void str_resize( DStringT* buf, size_t newLength )
{
    if ( newLength > buf->length )
    {
        if ( newLength > buf->capacity )
        {
            void* resultPtr;
            size_t newCapacity = newLength * 2;

            if ( NULL == buf->data ) { resultPtr = CMALLOC( newCapacity ); }
            else { resultPtr = CREALLOC( buf->data, newCapacity ); }
            if ( NULL == resultPtr ) { LOG_ERROR( "Can not allocate dynamic string!\n" ); }

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

inline static void str_destroy( DStringT* buf )
{
    if ( NULL != buf )
    {
        if ( buf->data ) { CFREE( buf->data, buf->length ); }
        CFREE( ( void* ) buf, sizeof( DStringT* ) );
    }
}

inline static void str_erase( DStringT* buf, size_t index )
{
    if ( index < buf->length )
    {
        void* resultPtr = NULL;
        if ( NULL != buf->data )
        {
            void* dest = &( buf->data[ index ] );
            void* src = &( buf->data[ index + 1 ] );
            resultPtr = CMEMCPY( dest, src, ( buf->length - index ) );
            if ( NULL == resultPtr ) { LOG_ERROR( "Can not copy string array!\n" ); }
        }
        if ( NULL != resultPtr ) { buf->length -= 1; }
    }
}

inline static void str_insert( DStringT* buf, uint32_t index, void* element )
{
    void* src = &( buf->data[ index ] );
    void* dest = &( buf->data[ index + 1 ] );
    void* resultPtr = NULL;

    resultPtr = CMEMCPY( dest, src, ( buf->length - index - 1 ) );

    if ( NULL == resultPtr ) { LOG_ERROR( "Can not copy string array!\n" ); }
    if ( NULL != resultPtr ) { resultPtr = CMEMCPY( src, element, 1 ); }
}

inline static void str_shring_to_fit( DStringT* buf )
{
    if ( buf->capacity > buf->length )
    {
        void* resultPtr = NULL;
        if ( NULL != buf->data ) { resultPtr = CREALLOC( buf->data, buf->length ); }
        if ( NULL == resultPtr ) { LOG_ERROR( "Can not reallocate string array!\n" ); }
        if ( NULL != resultPtr )
        {
            buf->capacity = buf->length;
            buf->data = resultPtr;
        }
    }
}

inline static void str_reserve( DStringT* buf, size_t newCapacity )
{
    if ( newCapacity > buf->capacity )
    {
        void* resultPtr;

        if ( NULL == buf->data ) { resultPtr = CMALLOC( newCapacity ); }
        else { resultPtr = CREALLOC( buf->data, newCapacity ); }

        if ( NULL == resultPtr ) { LOG_ERROR( "Can not allocate string array!\n" ); }
        if ( NULL != resultPtr )
        {
            buf->data = resultPtr;
            buf->capacity = newCapacity;
        }
    }
}

inline static void* str_arr_create( void )
{
    DArrayT* result = NULL;

    result = ( DArrayT* ) CMALLOC( sizeof( DArrayT ) );

    if ( NULL == result ) { LOG_ERROR( "Can not allocate dynamic array!\n" ); }
    else
    {
        result->length = 0;                    // set length to 0
        result->capacity = 0;                  // set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = sizeof( char** );// set element size to stride
        result->data = NULL;
    }

    return ( void* ) result;
}

inline static void str_arr_destroy( DArrayT* buf )
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

#endif// DSTRING_HEADER