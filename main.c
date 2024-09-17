#include <stdio.h>
#include <stdlib.h>

#include "CFilesystem.h"

int main( void )
{
    const int8_t data[] = { 0x41, 0x2, 0x3, 0x4, 0x5, 0x5 };
    file_write_binary( "example.bin", data, 6 );

    return 0;
}