#include <stdio.h>
#include <stdlib.h>
#define CUTILS_VERBOSE
#include "CFilesystem.h"
#include "DString.h"

int main( void )
{
    DArrayT* myArray = DArray_Init( uint32_t );

    DArray_Push( myArray, 0xFF000000 );
    DArray_Push( myArray, 0xFFFF0000 );
    DArray_Push( myArray, 0xFFFFFF00 );
    DArray_Push( myArray, 0xFFFFFFFF );
    DArray_Push( myArray, 0xF0F0F0F0 );
    DArray_Push( myArray, 0x1F0F0F0F );
    printf( "Capacity: %d\n", DArray_Capacity( myArray ) );
    DArray_Shrink_To_Fit( myArray );
    printf( "Capacity: %d\n", DArray_Capacity( myArray ) );

    for ( size_t i = 0; i < DArray_Length( myArray ); i++ ) { printf( "%X ", DArray_GetU32( myArray, i ) ); }
    printf( "\n" );

    DArray_Insert( myArray, 0, 10 );
    DArray_Insert( myArray, 1, 30 );
    printf( "Capacity: %d\n", DArray_Capacity( myArray ) );

    uint32_t len = DArray_Length( myArray );
    for ( size_t i = 0; i < len; i++ ) { printf( "%X ", DArray_GetU32( myArray, i ) ); }

    DArray_Destroy( myArray );

    const char* example = "example string";

    DStringT* str = DString_Create( example, CString_Length( example ) );
    for ( size_t i = 0; i < strlen( str->data ); i++ ) { printf( "%c", DString_Get( str, i ) ); }
    DString_Destroy( str );
    LOG( "\n\n\n" );

    FolderContentsT f;
    list_directory_contents( "C:/Users", &f );

    for ( size_t i = 0; i < f.files->length; i++ )
    {
        const char* str = DStrArray_Get( f.files, i )->data;
        printf( "FILE: %s\n", str );
    }
    for ( size_t i = 0; i < f.directories->length; i++ )
    {
        const char* str = DStrArray_Get( f.directories, i )->data;
        printf( "DIRR: %s\n", str );
    }

    free_folder_contents_struct( &f );

    DStringT* helloStr = DString_Create( "Hello ", 6 );
    DStringT* worldStr = DString_Create( "World", 5 );

    CStringViewT helloView = string_view_create_d( helloStr );
    CStringViewT worldView = string_view_create_d( worldStr );
    LOG_INFO( "dynamic string: %s\n", helloStr->data );
    LOG_INFO( "string view   : %s\n", helloView.data );
    LOG_INFO( "length : %zu\n", helloStr->length );
    LOG_INFO( "dynamic string: %s\n", worldStr->data );
    LOG_INFO( "string view   : %s\n", worldView.data );

    str_append_string_view( helloStr, worldView );
    LOG_INFO( "result : %s\n", helloStr->data );
    LOG_INFO( "length : %zu\n", helloStr->length );

    DString_Destroy( helloStr );
    return 0;
}
