#include <stdio.h>
#include <stdlib.h>
#define CUTILS_VERBOSE
#include "CFilesystem.h"

int main( void )
{
    // _DArrayType* myArray = DArray_Init( uint32_t );

    // DArray_Push( myArray, 0xFF000000 );
    // DArray_Push( myArray, 0xFFFF0000 );
    // DArray_Push( myArray, 0xFFFFFF00 );
    // DArray_Push( myArray, 0xFFFFFFFF );
    // DArray_Push( myArray, 0xF0F0F0F0 );
    // DArray_Push( myArray, 0x1F0F0F0F );
    // printf( "Capacity: %d\n", DArray_Capacity( myArray ) );
    // DArray_Shrink_To_Fit( myArray );
    // printf( "Capacity: %d\n", DArray_Capacity( myArray ) );

    // for ( size_t i = 0; i < DArray_Length( myArray ); i++ )
    // {
    //     printf( "%X ", *( unsigned int* ) DArray_Get( myArray, i ) );
    // }
    // printf( "\n" );

    // DArray_Insert( myArray, 0, 10 );
    // DArray_Insert( myArray, 1, 30 );
    // printf( "Capacity: %d\n", DArray_Capacity( myArray ) );

    // uint32_t len = DArray_Length( myArray );
    // for ( size_t i = 0; i < len; i++ ) { printf( "%X ", *( unsigned int* ) DArray_Get( myArray, i ) ); }

    // DArray_Destroy( myArray );
    FolderContentsType f;
    list_directory_contents( "C:\\Users\\Krusto", &f );

    return 0;
}