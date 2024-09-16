#include <stdio.h>
#include <stdlib.h>

#include "CArray.h"

int main( void )
{
    DArray_t( uint32_t, myArray );

    for ( size_t i = 0; i < 10; i++ )
    {
        DArray_Resize( myArray, myArray.length + 1 );
        myArray.data[ myArray.length - 1 ] = i;
        uint32_t val = DArray_Pop( myArray );
        printf( "%d\n", val );
    }
    DArray_Destroy( myArray );

    DArray_Push( myArray, 0 );
    DArray_Push( myArray, 1 );
    DArray_Push( myArray, 2 );
    DArray_Push( myArray, 3 );
    DArray_Push( myArray, 4 );
    DArray_Push( myArray, 5 );
    printf( "Capacity: %d\n", DArray_Capacity( myArray ) );
    DArray_Shrink_To_Fit( myArray );
    printf( "Capacity: %d\n", DArray_Capacity( myArray ) );

    return 0;
}