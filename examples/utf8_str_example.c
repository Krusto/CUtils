#include <stdio.h>
#include <stdlib.h>

#define CUTILS_VERBOSE
#include "DString.h"
#include <locale.h>

int main(void)
{

    const uint8_t valid_utf8[] = {0xE2, 0x82, 0xAC};        // "€" (Euro sign)
    const uint8_t invalid_utf8[] = {0xF0, 0x28, 0x8C, 0xBC};// Invalid sequence

    LOG_INFO("Valid UTF-8: %s\n", cstr_is_valid_utf8(valid_utf8, sizeof(valid_utf8)) ? "True" : "False");
    LOG_INFO("Invalid UTF-8: %s\n", cstr_is_valid_utf8(invalid_utf8, sizeof(invalid_utf8)) ? "True" : "False");

    uint8_t length = utf8_get_char_length(valid_utf8[0]);
    LOG_INFO("Byte Length %d\n", length);
    LOG_INFO("decoded 0x%X\n", utf8_to_unicode(valid_utf8));
    return 0;
}
