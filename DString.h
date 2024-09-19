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

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

/**
 * @brief Creates dynamic string from a string allocated on the stack
 * @param buff 
 * @param size 
 * @return 
 */
inline static int8_t* DString_Create( int8_t* buff, size_t size )
{
    LOG_INFO( "Allocating String\n" );
    int8_t* memory = ( int8_t* ) CMALLOC( size + 1 );
    int8_t* resultPtr = NULL;
    resultPtr = ( int8_t* ) CMEMCPY( memory, buff, size );
    if ( NULL == resultPtr ) { LOG_ERROR( "Can not create string!\n" ); }
    memory[ size ] = '\0';
    return resultPtr;
}

/**
 * @brief Returns the length between the null termination and start of the string
 * @param str 
 * @return 
 */
inline static size_t DString_Length( const int8_t* str )
{
    const int8_t* s;

    for ( s = str; *s; ++s )
        ;
    return ( s - str );
}
#endif// DSTRING_HEADER