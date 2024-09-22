#ifndef CSTRINGVIEW_HEADER
#define CSTRINGVIEW_HEADER

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
 * CStringView Header
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "CMemory.h"
#include "DString.h"
#include "STDTypes.h"

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/
typedef struct {
    const int8_t* data;
    size_t length;
} CStringViewT;

/***********************************************************************************************************************
Function declarations
***********************************************************************************************************************/
static CStringViewT string_view_create(const int8_t* str);
static CStringViewT string_view_create_d(DStringT* str);
static BOOL string_view_cmp_d(CStringViewT sv1, DStringT* dstring);
static BOOL string_view_cmp(CStringViewT sv1, CStringViewT sv2);
static CStringViewT string_view_substr(CStringViewT* str, size_t index, size_t count);
static DStringT* string_view_to_string(CStringViewT* str);
static void str_append_string_view(DStringT* str, CStringViewT str_view);

/***********************************************************************************************************************
Function definitions
***********************************************************************************************************************/
inline static CStringViewT string_view_create(const int8_t* str)
{
    CStringViewT result = {str, cstr_length(str)};
    return result;
}

inline static CStringViewT string_view_create_d(DStringT* str)
{
    CStringViewT result = {str->data, str->length};
    return result;
}

inline static BOOL string_view_cmp_d(CStringViewT sv1, DStringT* dstring)
{
    return (sv1.data == (string_view_create_d(dstring).data));
}

inline static BOOL string_view_cmp(CStringViewT sv1, CStringViewT sv2) { return (sv1.data == sv2.data); }

inline static CStringViewT string_view_substr(CStringViewT* str, size_t index, size_t count)
{
    CStringViewT result = {NULL};
    if (count < str->length)
    {
        result.data = &str->data[index];
        result.length = str->length - count;
    }
    else { LOG_ERROR("Substring out of bounds!"); }
    return result;
}

inline static DStringT* string_view_to_string(CStringViewT* str) { return str_create(str->data, str->length); }

inline static void str_append_string_view(DStringT* str, CStringViewT str_view)
{
    size_t old_length = str->length;
    str_resize(str, str->length + str_view.length + DSTRING_NULL_TERMINATION_LENGTH);
    CMEMCPY(&str->data[old_length], str_view.data, str_view.length);

    str->data[str->length - 1] = '\0';
}


#endif//CSTRINGVIEW_HEADER