#ifndef CMEMORY_HEADER
#define CMEMORY_HEADER
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
 * CMemory Header
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "STDTypes.h"
#ifndef NO_STD_MALLOC
#include <stdlib.h>
#include <string.h>
#endif
/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/**
 * @brief Defines for memory management functions
 * If NO_STD_MALLOC is defined, all these functions do nothing. Otherwise they
 * just call the standard library functions for memory management.
 * This is useful for testing purposes, allowing you to overwrite the memory
 * management functions with your own implementation.
 */
#ifndef NO_STD_MALLOC
#define CMEMCPY(dest, p, size) memcpy((void*) (dest), (void*) (p), size)
#define CMALLOC(size) malloc(size)
#define CCALLOC(num, size) calloc(num, size)
#define CREALLOC(p, new_size) realloc((void*) (p), new_size)
#define CFREE(p, size) free((void*) (p))
#define CMEMSET(p, value, size) memset((void*) (p), value, size)
#else
#define CMEMCPY(dest, p, size)
#define CMALLOC(size)
#define CCALLOC(size)
#define CREALLOC(p, new_size)
#define CFREE(p, size)
#define CMEMSET(p, value, size)
#endif
/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

#endif// CMEMORY_HEADER