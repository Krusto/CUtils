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

#define DSTRING_NULL_TERMINATION_LENGTH 1u
#define DSTRING_NULL_TERMINATOR '\0';

#define UNICODE_UTF8_ASCII_RANGE_MAX 0x7F
#define UNICODE_UTF8_BYTE1_MASK 0xC0
#define UNICODE_UTF8_BYTE2_MASK 0xE0
#define UNICODE_UTF8_BYTE3_MASK 0xF0
#define UNICODE_UTF8_BYTE4_MASK 0xF8

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/

typedef struct {
    size_t length;
    size_t capacity;
    int8_t* data;
} DStringT;

/***********************************************************************************************************************
Static functions declaration
***********************************************************************************************************************/
static void str_arr_push_back(DArrayT* arr, DStringT* str);
static DStringT* str_arr_get(DArrayT* arr, size_t index);
static int8_t str_get(DStringT* str, size_t index);
static int8_t* str_get_ptr(DStringT* str, size_t index);
static int8_t str_front(DStringT* str);
static int8_t* str_front_ptr(DStringT* str);
static int8_t str_back(DStringT* str);
static int8_t* str_back_ptr(DStringT* str);
static BOOL is_str_empty(DStringT* str);
static DStringT* str_create(const int8_t* str, size_t size);
static size_t cstr_length(const int8_t* str);
static size_t cstr_utf8_length(const int8_t* str);
static BOOL cstr_contains_utf8_bom(const int8_t* str);
static BOOL cstr_is_utf8(const int8_t* str);
static BOOL utf8_is_continuation_byte(int8_t byte);
static BOOL utf8_is_byte_ascii(int8_t byte);
static BOOL cstr_is_valid_utf8(const int8_t* input, size_t length);
static uint8_t utf8_get_char_length(int8_t byte);
static const void utf8_go_next_char(const int8_t* buffer, uint32_t length, uint32_t* currentIndexPtr);
static const void utf8_go_prev_char(const int8_t* buffer, uint32_t length, uint32_t* currentIndexPtr);
static wchar_t utf8_to_unicode(const int8_t* utf8_data);
static BOOL str_is_valid_utf8(DStringT* buf);
static void str_resize(DStringT* buf, size_t newLength);
static void str_destroy(DStringT* buf);
static void str_erase(DStringT* buf, size_t index);
static void str_insert(DStringT* buf, uint32_t index, int8_t* element);
static void str_shring_to_fit(DStringT* buf);
static void str_reserve(DStringT* buf, size_t newCapacity);
static void* str_arr_create(void);
static void str_arr_destroy(DArrayT* buf);
static DStringT* dstring_append_cstring(DStringT* str, const int8_t* cstr);
static DStringT* dstring_append_dstring(DStringT* str, DStringT* another);
static DStringT* dstring_insert_dstring(DStringT* str, DStringT* another, size_t index);

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/
static DStringT* str_arr_get(DArrayT* arr, size_t index) { return ((DStringT**) (arr->data))[index]; }

inline static void str_arr_push_back(DArrayT* arr, DStringT* str)
{
    darr_resize(arr, arr->length + 1);
    ((DStringT**) arr->data)[arr->length - 1] = str;
}

inline static int8_t str_get(DStringT* str, size_t index) { return str->data[index]; }

inline static int8_t* str_get_ptr(DStringT* str, size_t index) { return &(str->data[index]); }

inline static int8_t str_front(DStringT* str) { return str->data[0]; }

inline static int8_t* str_front_ptr(DStringT* str) { return &(str->data[0]); }

inline static int8_t str_back(DStringT* str) { return str->data[str->length - 1]; }

inline static int8_t* str_back_ptr(DStringT* str) { return &(str->data[str->length - 1]); }

inline static BOOL is_str_empty(DStringT* str) { return (0 == str->length); }

inline static DStringT* str_create(const int8_t* str, size_t size)
{
    DStringT* result = NULL;

    result = (DStringT*) CMALLOC(sizeof(DStringT));

    if (NULL == result) { LOG_ERROR("Can not allocate dynamic string!\n"); }
    else
    {
        result->length = 0;  // set length to 0
        result->capacity = 0;// set capacity to DARRAY_INITIAL_CAPACITY
        result->data = NULL;
    }
    if (size > 0)
    {
        int8_t* memory = (int8_t*) CMALLOC(size + 1);
        int8_t* resultPtr = NULL;
        resultPtr = (int8_t*) CMEMCPY(memory, str, size);
        if (NULL == resultPtr) { LOG_ERROR("Can not create string!\n"); }
        memory[size] = '\0';
        result->data = memory;
        result->length = size;
        result->capacity = size;
    }
    return result;
}

inline static size_t cstr_length(const int8_t* str)
{
    const int8_t* int8_t_ptr;
    const uint32_t* longword_ptr;
    uint32_t longword, himagic, lomagic;

    /* Handle the first few characters by reading one character at a time.
     Do this until CHAR_PTR is aligned on a longword boundary.  */
    for (int8_t_ptr = str; ((size_t) int8_t_ptr & (sizeof(longword) - 1)) != 0; ++int8_t_ptr)
        if (*int8_t_ptr == '\0') return int8_t_ptr - str;

    /* All these elucidatory comments refer to 4-byte longwords,
     but the theory applies equally well to 8-byte longwords.  */

    longword_ptr = (uint32_t*) int8_t_ptr;

    /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
     the "holes."  Note that there is a hole just to the left of
     each byte, with an extra at the end:

     bits:  01111110 11111110 11111110 11111111
     bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

     The 1-bits make sure that carries propagate to the next 0-bit.
     The 0-bits provide holes for carries to fall into.  */
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof(longword) > 4)
    {
        /* 64-bit version of the magic.  */
        /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof(longword) > 8) abort();

    /* Instead of the traditional loop which tests each character,
     we will test a longword at a time.  The tricky part is testing
     if *any of the four* bytes in the longword in question are zero.  */
    for (;;)
    {
        longword = *longword_ptr++;

        if (((longword - lomagic) & ~longword & himagic) != 0)
        {
            /* Which of the bytes was the zero?  If none of them were, it was
         a misfire; continue the search.  */

            const int8_t* cp = (const int8_t*) (longword_ptr - 1);

            if (cp[0] == 0) return cp - str;
            if (cp[1] == 0) return cp - str + 1;
            if (cp[2] == 0) return cp - str + 2;
            if (cp[3] == 0) return cp - str + 3;
            if (sizeof(longword) > 4)
            {
                if (cp[4] == 0) return cp - str + 4;
                if (cp[5] == 0) return cp - str + 5;
                if (cp[6] == 0) return cp - str + 6;
                if (cp[7] == 0) return cp - str + 7;
            }
        }
    }
}

inline static size_t cstr_utf8_length(const int8_t* str)
{
    size_t count = 0;
    while (*str) { count += !utf8_is_continuation_byte(*str++); }
    return count;
}

inline static BOOL cstr_contains_utf8_bom(const int8_t* str)
{
    BOOL result = TRUE;
    const int8_t utf8_bom[3] = {0xEF, 0xBB, 0xBF};
    for (size_t i = 0; i < 3; i++)
    {
        if (str[i] != utf8_bom[i]) { result = FALSE; }
    }
    return result;
}

inline static BOOL cstr_is_utf8(const int8_t* str)
{
    BOOL result = FALSE;
    if (cstr_contains_utf8_bom(str)) { result = TRUE; }
    else
    {
        do {
            result = utf8_is_byte_ascii(*str++);
        } while (*str && result == FALSE);
    }
    return result;
}

inline static BOOL utf8_is_continuation_byte(int8_t byte) { return (byte & UNICODE_UTF8_BYTE1_MASK) == 0x80; }

inline static BOOL utf8_is_continuation_byte2(int8_t byte) { return (byte & UNICODE_UTF8_BYTE2_MASK) == 0x80; }

inline static BOOL utf8_is_continuation_byte3(int8_t byte) { return (byte & UNICODE_UTF8_BYTE3_MASK) == 0x80; }

inline static BOOL utf8_is_byte_ascii(int8_t byte) { return byte <= UNICODE_UTF8_ASCII_RANGE_MAX; }

inline static BOOL cstr_is_valid_utf8(const int8_t* input, size_t length)
{
    BOOL is_valid = TRUE;// Accumulates result
    size_t index = 0;

    while (index < length)
    {
        uint8_t byte = input[index];

        // Check for 1-byte sequence (ASCII, 0xxxxxxx)
        if (utf8_is_byte_ascii(byte))
        {
            index++;
            continue;
        }

        // Check for 2-byte sequence (110xxxxx 10xxxxxx)
        if ((byte & UNICODE_UTF8_BYTE2_MASK) == UNICODE_UTF8_BYTE1_MASK)
        {
            if (index + 1 >= length || !utf8_is_continuation_byte(input[index + 1]))
            {
                is_valid = FALSE;
                break;
            }
            // Overlong encoding: code points that should be in 1 byte
            if (byte <= 0xC1)
            {
                is_valid = FALSE;
                break;
            }
            index += 2;
            continue;
        }

        // Check for 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        if ((byte & UNICODE_UTF8_BYTE3_MASK) == UNICODE_UTF8_BYTE2_MASK)
        {
            if (index + 2 >= length || !utf8_is_continuation_byte(input[index + 1]) ||
                !utf8_is_continuation_byte(input[index + 2]))
            {
                is_valid = FALSE;
                break;
            }
            // Overlong encoding: code points that should be in 2 bytes
            if (byte == UNICODE_UTF8_BYTE2_MASK && utf8_is_continuation_byte2(input[index + 1]))
            {
                is_valid = FALSE;
                break;
            }
            // Invalid surrogates (U+D800 to U+DFFF)
            if (byte == 0xED && (input[index + 1] & 0xE0) == 0xA0)
            {
                is_valid = FALSE;
                break;
            }
            index += 3;
            continue;
        }

        // Check for 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        if ((byte & UNICODE_UTF8_BYTE4_MASK) == UNICODE_UTF8_BYTE3_MASK)
        {
            if (index + 3 >= length || !utf8_is_continuation_byte(input[index + 1]) ||
                !utf8_is_continuation_byte(input[index + 2]) || !utf8_is_continuation_byte(input[index + 3]))
            {
                is_valid = FALSE;
                break;
            }
            // Overlong encoding: code points that should be in 3 bytes
            if (byte == UNICODE_UTF8_BYTE3_MASK && utf8_is_continuation_byte3(input[index + 1]))
            {
                is_valid = FALSE;
                break;
            }
            // Code points greater than U+10FFFF
            if (byte > 0xF4 || (byte == 0xF4 && (input[index + 1] & 0xF0) > 0x8F))
            {
                is_valid = FALSE;
                break;
            }
            index += 4;
            continue;
        }

        // Any other byte patterns are invalid
        is_valid = FALSE;
        break;
    }

    return is_valid;// Single return point
}

inline static uint8_t utf8_get_char_length(int8_t byte)
{
    uint8_t count = 0;
    if ((byte & (UNICODE_UTF8_ASCII_RANGE_MAX + 1)) == 0) { count = 1; }
    else if ((byte & UNICODE_UTF8_BYTE2_MASK) == UNICODE_UTF8_BYTE1_MASK) { count = 2; }
    else if ((byte & UNICODE_UTF8_BYTE3_MASK) == UNICODE_UTF8_BYTE2_MASK) { count = 3; }
    else if ((byte & UNICODE_UTF8_BYTE4_MASK) == UNICODE_UTF8_BYTE3_MASK) { count = 4; }

    return count;
}

inline static const void utf8_go_next_char(const int8_t* buffer, uint32_t length, uint32_t* currentIndexPtr)
{
    uint32_t currentIndex = *currentIndexPtr;

    uint32_t newOffset = currentIndex + utf8_get_char_length(buffer[currentIndex]);
    if (newOffset < length) { (*currentIndexPtr) = newOffset; };
}

inline static const void utf8_go_prev_char(const int8_t* buffer, uint32_t length, uint32_t* currentIndexPtr) {}

inline static wchar_t utf8_to_unicode(const int8_t* utf8_data)
{
    wchar_t unicode = 0;
    uint8_t length = utf8_get_char_length(utf8_data[0]);

    switch (length)
    {
        case 1:
            unicode = utf8_data[0];
            break;
        case 2:
            unicode = ((utf8_data[0] & 0x1F) << 6) | (utf8_data[1] & 0x3F);
            break;
        case 3:
            unicode = ((utf8_data[0] & 0x0F) << 12) | ((utf8_data[1] & 0x3F) << 6) | (utf8_data[2] & 0x3F);
            break;
        case 4:
            unicode = ((utf8_data[0] & 0x07) << 18) | ((utf8_data[1] & 0x3F) << 12) | ((utf8_data[2] & 0x3F) << 6) |
                      (utf8_data[3] & 0x3F);
            break;
        default:
            break;
    }

    return unicode;
}

inline static BOOL str_is_valid_utf8(DStringT* buf) { return cstr_is_valid_utf8(buf->data, buf->length); }

inline static void str_resize(DStringT* buf, size_t newLength)
{
    if (newLength > buf->length)
    {
        if (newLength > buf->capacity)
        {
            void* resultPtr;
            size_t newCapacity = newLength * 2;

            if (NULL == buf->data) { resultPtr = CMALLOC(newCapacity); }
            else { resultPtr = CREALLOC(buf->data, newCapacity); }
            if (NULL == resultPtr) { LOG_ERROR("Can not allocate dynamic string!\n"); }

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

inline static void str_destroy(DStringT* buf)
{
    if (NULL != buf)
    {
        if (buf->data) { CFREE(buf->data, buf->length); }
        CFREE((void*) buf, sizeof(DStringT*));
    }
}

inline static void str_erase(DStringT* buf, size_t index)
{
    if (index < buf->length)
    {
        void* resultPtr = NULL;
        if (NULL != buf->data)
        {
            void* dest = &(buf->data[index]);
            void* src = &(buf->data[index + 1]);
            resultPtr = CMEMCPY(dest, src, (buf->length - index));
            if (NULL == resultPtr) { LOG_ERROR("Can not copy string array!\n"); }
        }
        if (NULL != resultPtr) { buf->length -= 1; }
    }
}

inline static void str_insert(DStringT* buf, uint32_t index, int8_t* element)
{
    void* src = &(buf->data[index]);
    void* dest = &(buf->data[index + 1]);
    void* resultPtr = NULL;

    resultPtr = CMEMCPY(dest, src, (buf->length - index - 1));

    if (NULL == resultPtr) { LOG_ERROR("Can not copy string array!\n"); }
    if (NULL != resultPtr) { resultPtr = CMEMCPY(src, element, 1); }
}

inline static void str_shring_to_fit(DStringT* buf)
{
    if (buf->capacity > buf->length)
    {
        void* resultPtr = NULL;
        if (NULL != buf->data) { resultPtr = CREALLOC(buf->data, buf->length); }
        if (NULL == resultPtr) { LOG_ERROR("Can not reallocate string array!\n"); }
        if (NULL != resultPtr)
        {
            buf->capacity = buf->length;
            buf->data = resultPtr;
        }
    }
}

inline static void str_reserve(DStringT* buf, size_t newCapacity)
{
    if (newCapacity > buf->capacity)
    {
        void* resultPtr;

        if (NULL == buf->data) { resultPtr = CMALLOC(newCapacity); }
        else { resultPtr = CREALLOC(buf->data, newCapacity); }

        if (NULL == resultPtr) { LOG_ERROR("Can not allocate string array!\n"); }
        if (NULL != resultPtr)
        {
            buf->data = resultPtr;
            buf->capacity = newCapacity;
        }
    }
}

inline static void* str_arr_create(void)
{
    DArrayT* result = NULL;

    result = (DArrayT*) CMALLOC(sizeof(DArrayT));

    if (NULL == result) { LOG_ERROR("Can not allocate dynamic array!\n"); }
    else
    {
        result->length = 0;                    // set length to 0
        result->capacity = 0;                  // set capacity to DARRAY_INITIAL_CAPACITY
        result->elementSize = sizeof(int8_t**);// set element size to stride
        result->data = NULL;
    }

    return (void*) result;
}

inline static void str_arr_destroy(DArrayT* buf)
{
    if (NULL != buf)
    {
        for (size_t i = 0; i < darr_length(buf); i++) { str_destroy(str_arr_get(buf, i)); }
        if (buf->data) { CFREE(buf->data, buf->length); }
        CFREE((void*) buf, DARRAY_HEADER_SIZE + sizeof(int8_t*));
    }
}

inline static DStringT* dstring_append_cstring(DStringT* str, const int8_t* cstr)
{

    size_t old_length = str->length;
    size_t cstrLength = cstr_length(cstr);
    str_resize(str, str->length + cstrLength + DSTRING_NULL_TERMINATION_LENGTH);

    DStringT* resultData = CMEMCPY(&str->data[old_length], cstr, cstrLength);
    if (NULL == resultData) { LOG_ERROR("Can not resize string!\n"); }
    else
    {
        resultData = str;
        str->data[str->length - 1] = '\0';
        str->length -= DSTRING_NULL_TERMINATION_LENGTH;
    }

    return resultData;
}

inline static DStringT* dstring_append_dstring(DStringT* str, DStringT* another)
{
    size_t destPtrIndex = str->length;
    size_t insertDataLength = another->length;
    str_resize(str, destPtrIndex + insertDataLength + DSTRING_NULL_TERMINATION_LENGTH);

    int8_t* resultData = CMEMCPY(&str->data[destPtrIndex], another->data, insertDataLength);
    if (NULL != resultData)
    {
        resultData = (int8_t*) str;
        str->data[str->length - 1] = '\0';
        str->length -= DSTRING_NULL_TERMINATION_LENGTH;
    }
    else { LOG_ERROR("Can not append string!\n"); }

    return (DStringT*) resultData;
}

inline static DStringT* dstring_insert_dstring(DStringT* str, DStringT* another, size_t index)
{
    size_t oldLength = str->length;
    str_resize(str, str->length + another->length + DSTRING_NULL_TERMINATION_LENGTH);

    int8_t* resultData = CMEMCPY(&str->data[index + another->length], &str->data[index], oldLength - index);
    if (NULL != resultData) { resultData = CMEMCPY(&str->data[index], another->data, another->length); }
    if (NULL != resultData)
    {
        resultData = (int8_t*) str;
        str->data[str->length - 1] = '\0';             // add null termination after the end of string
        str->length -= DSTRING_NULL_TERMINATION_LENGTH;// fix string length (null termination doesn't count in strlen())
    }
    else { LOG_ERROR("Can not insert string string!\n"); }

    return (DStringT*) resultData;
}
#endif// DSTRING_HEADER