#ifndef CSTRINGVIEW_HEADER
#define CSTRINGVIEW_HEADER

#include "CMemory.h"
#include "DString.h"
#include "STDTypes.h"

typedef struct {
    const int8_t* data;
    size_t length;
} CStringViewT;

CStringViewT string_view_create( const int8_t* str )
{
    CStringViewT result = { str, CString_Length( str ) };
    return result;
}

CStringViewT string_view_create_d( DStringT* str )
{
    CStringViewT result = { str->data, str->length };
    return result;
}

BOOL string_view_cmp_d( CStringViewT sv1, DStringT* dstring )
{
    return ( sv1.data == ( string_view_create_d( dstring ).data ) );
}

BOOL string_view_cmp( CStringViewT sv1, CStringViewT sv2 ) { return ( sv1.data == sv2.data ); }

CStringViewT string_view_substr( CStringViewT* str, size_t index, size_t count )
{
    CStringViewT result = { NULL };
    if ( count < str->length )
    {
        result.data = &str->data[ index ];
        result.length = str->length - count;
    }
    else { LOG_ERROR( "Substring out of bounds!" ); }
    return result;
}

DStringT* string_view_to_string( CStringViewT* str ) { return DString_Create( str->data, str->length ); }

inline static void str_append_string_view( DStringT* str, CStringViewT str_view )
{
    size_t old_length = str->length;
    DString_Resize( str, str->length + str_view.length + DSTRING_NULL_TERMINATION_LENGTH );
    CMEMCPY( &str->data[ old_length ], str_view.data, str_view.length );

    str->data[ str->length - 1 ] = '\0';
}


#endif//CSTRINGVIEW_HEADER