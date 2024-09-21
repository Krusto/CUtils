#include <stdio.h>
#include <stdlib.h>
#define CUTILS_VERBOSE
#include "CFilesystem.h"
#include "DString.h"

int main(void)
{
    DArrayT* myArray = arr_create_u32();

    arr_push_u32(myArray, 0xFF000000);
    arr_push_u32(myArray, 0xFFFF0000);
    arr_push_u32(myArray, 0xFFFFFF00);
    arr_push_u32(myArray, 0xFFFFFFFF);
    arr_push_u32(myArray, 0xF0F0F0F0);
    arr_push_u32(myArray, 0x1F0F0F0F) ;
    printf("Capacity: %d\n", arr_capacity(myArray));
    arr_shrink_to_fit(myArray);
    printf("Capacity: %d\n", arr_capacity(myArray));

    for (size_t i = 0; i < arr_length(myArray); i++) { printf("%X ", arr_get_u32(myArray, i)); }
    printf("\n");

    arr_insert_u32(myArray, 0, 10);
    arr_insert_u32(myArray, 1, 30);

    printf("Capacity: %d\n", arr_capacity(myArray));

    uint32_t len = arr_length(myArray);
    for (size_t i = 0; i < len; i++) { printf("%X ", arr_get_u32(myArray, i)); }

    arr_destroy(myArray);

    const char* example = "example string";

    DStringT* str = str_create(example, cstr_length(example));
    for (size_t i = 0; i < strlen(str->data); i++) { printf("%c", str_get(str, i)); }
    str_destroy(str);
    LOG("\n\n\n");

    FolderContentsT f;
    list_directory_contents("C:/Users", &f);

    for (size_t i = 0; i < f.files->length; i++)
    {
        const char* str = str_arr_get(f.files, i)->data;
        printf("FILE: %s\n", str);
    }
    for (size_t i = 0; i < f.directories->length; i++)
    {
        const char* str = str_arr_get(f.directories, i)->data;
        printf("DIRR: %s\n", str);
    }

    free_folder_contents_struct(&f);

    DStringT* helloStr = str_create("Hello ", 6);
    DStringT* worldStr = str_create("World", 5);

    CStringViewT helloView = string_view_create_d(helloStr);
    CStringViewT worldView = string_view_create_d(worldStr);
    LOG_INFO("dynamic string: %s\n", helloStr->data);
    LOG_INFO("string view   : %s\n", helloView.data);
    LOG_INFO("length : %zu\n", helloStr->length);
    LOG_INFO("dynamic string: %s\n", worldStr->data);
    LOG_INFO("string view   : %s\n", worldView.data);

    str_append_string_view(helloStr, worldView);
    LOG_INFO("result : %s\n", helloStr->data);
    LOG_INFO("length : %zu\n", helloStr->length);

    str_destroy(helloStr);
    str_destroy(worldStr);

    helloStr = str_create("ampl", 5);
    worldStr = str_create("ex", 2);
    DStringT* eStr = str_create("e", 1);
    DStringT* mStr = str_create("m", 1);

    dstring_insert_dstring(helloStr, worldStr, 0);
    dstring_insert_dstring(helloStr, eStr, 6);
    dstring_insert_dstring(helloStr, mStr, 3);
    LOG_INFO("result : %s\n", helloStr->data);
    str_destroy(helloStr);
    str_destroy(worldStr);
    str_destroy(eStr);
    str_destroy(mStr);
    return 0;
}
