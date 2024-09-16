#include <stdio.h>
#include <stdlib.h>

#include "CFilesystem.h"

int main( void )
{
    const char* text = "Example text";
    file_write_binary( "example.bin", text, 12 );
    
    return 0;
}