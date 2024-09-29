#include <stdio.h>
#include <stdlib.h>

#define CUTILS_VERBOSE
#include "CFilesystem.h"

int main(void)
{
    DArrayT* myArray = darr_create_u32();

    darr_push_u32(myArray, 0xFF000000);

    LOG_INFO("%d\n", darr_get_u32(myArray, 0));

    darr_destroy(myArray);

    return 0;
}
