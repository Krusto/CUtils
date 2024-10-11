#ifndef CFILESYSTEM_HEADER
#define CFILESYSTEM_HEADER
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
 * CFilesystem Header
 */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CLog.h"
#include "CMemory.h"
#include "CStringView.h"
#include "DArray.h"
#include "DString.h"
#include "STDTypes.h"

#ifndef NO_STD_MALLOC
#include <stdio.h>
#include <stdlib.h>
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/
/**
 * @def MAX_PATH_SIZE
 * @brief Maximum path size
 * @details
 *      Maximum size of a path to a file or directory. This is used to prevent buffer overflows.
 */
#define MAX_PATH_SIZE 2048u

/***********************************************************************************************************************
Type Definitions
***********************************************************************************************************************/
typedef enum
{
    FILE_RESULT_NONE = 0,
    FILE_READ_SUCCESFULLY,
    FILE_WROTE_SUCCESFULLY,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    FILE_OPEN_ERROR,
    FILE_NOT_FOUND_ERROR,
    FILE_DOES_NOT_EXIST,
    FILE_UNKNOWN_ERROR,
    FILE_OPERATION_SUCCESS,
    FILE_BUFFER_ALLOCATION_ERROR,
    FILE_CORRUPTED_OR_WRONG_ENCODING
} FileOpResultT;

typedef struct {
    CStringViewT path;
    DArrayT* files;
    DArrayT* directories;
} FolderContentsT;

typedef struct {
    CStringViewT path;
    uint32_t fileAttributes;
    size_t fileSize[2];
    size_t lastWriteTime[2];
    size_t lastAccessTime[2];
    size_t creationTime[2];
} FileInfoT;

/***********************************************************************************************************************
Static functions implementation
***********************************************************************************************************************/

/**
 * @brief Reads a file into a buffer
 * @param filename Path of the file 
 * @param filesize Size in Bytes of the file
 * @param buffer Read data from file
 * @return File Operation Result
 */
inline static FileOpResultT file_read_binary(const int8_t* filename, size_t* filesize, int8_t** buffer)
{
    FileOpResultT result = FILE_READ_SUCCESFULLY;
    // start processing
    FILE* fileIn = fopen(filename, "rb");// open input file (binary)

    if (fileIn == NULL)
    {
        LOG_ERROR("Can not open %s!\n", filename);
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO("Opened %s\n", filename);
        // obtain file size.
        fseek(fileIn, 0, SEEK_END);
        *filesize = ftell(fileIn);
        rewind(fileIn);
        LOG_INFO("Filesize %ld bytes.\n", *filesize);

        // allocate memory to contain the whole file.
        *buffer = (uint8_t*) CMALLOC(*filesize);
        if (buffer == NULL)
        {
            LOG_ERROR("Malloc for input file buffer failed(not enough memory?)\n");
            result = FILE_BUFFER_ALLOCATION_ERROR;
        }
        else
        {
            // copy the file into the buffer.
            fread(buffer, 1, *filesize, fileIn);
        }

        fclose(fileIn);
    }
    return result;
}

/**
 * @brief Reads all data from file as string
 * @param filename Path to the file
 * @param filesize Size of the file
 * @param buffer Read data from the file
 * @return File Operation Result
 */
inline static FileOpResultT file_read_string(const int8_t* filename, size_t* filesize, int8_t** buffer)
{
    FileOpResultT result = FILE_READ_SUCCESFULLY;

    // Open the input file in text mode
    FILE* fileIn = fopen(filename, "r");// "r" for reading ASCII files

    if (fileIn == NULL)
    {
        LOG_ERROR("Cannot open %s!\n", filename);
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO("Opened %s\n", filename);

        // Obtain file size
        fseek(fileIn, 0, SEEK_END);
        *filesize = ftell(fileIn);
        rewind(fileIn);
        LOG_INFO("Filesize %ld bytes.\n", *filesize);

        // Allocate memory for the file content
        *buffer = (uint8_t*) CMALLOC(*filesize + 1);// Extra byte for null-terminator for text
        if (*buffer == NULL)
        {
            LOG_ERROR("Memory allocation for input file buffer failed (not enough memory?)\n");
            result = FILE_BUFFER_ALLOCATION_ERROR;
        }
        else
        {
            // Read the file into the buffer
            fread(*buffer, 1, *filesize, fileIn);
            (*buffer)[*filesize] = '\0';// Null-terminate for safe string handling
        }

        fclose(fileIn);
    }

    return result;
}

FileOpResultT file_read_utf8(const int8_t* filename, size_t* filesize, int8_t** buffer)
{

    FileOpResultT result = FILE_READ_SUCCESFULLY;
    // start processing
    FILE* fileIn = fopen(filename, "rb");// open input file (binary)

    if (fileIn == NULL)
    {
        LOG_ERROR("Can not open %s!\n", filename);
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO("Opened %s\n", filename);
        // obtain file size.
        fseek(fileIn, 0, SEEK_END);
        *filesize = ftell(fileIn);
        rewind(fileIn);
        LOG_INFO("Filesize %ld bytes.\n", *filesize);

        // allocate memory to contain the whole file.
        *buffer = (uint8_t*) CMALLOC(*filesize + 1);
        if (buffer == NULL)
        {
            LOG_ERROR("Malloc for input file buffer failed(not enough memory?)\n");
            result = FILE_BUFFER_ALLOCATION_ERROR;
        }
        else
        {
            // copy the file into the buffer.
            size_t readBytesCount = fread(*buffer, 1, *filesize, fileIn);
            if (readBytesCount != *filesize)
            {
                LOG_ERROR("Error reading file %s! Expected %ld bytes, read %ld bytes.\n", filename, *filesize,
                          readBytesCount);
                result = FILE_READ_ERROR;
            }
        }
        fclose(fileIn);
    }
    if (FILE_READ_SUCCESFULLY == result)
    {
        if (cstr_contains_utf8_bom(*buffer) == FALSE) { LOG_INFO("File does not contain utf-8 BOM\n"); }
        if (cstr_is_valid_utf8(*buffer, *filesize) == FALSE)
        {
            LOG_ERROR("File is corrupted or does not use utf-8 encoding!\n");
            result = FILE_CORRUPTED_OR_WRONG_ENCODING;
        }
    }
    return result;
}

inline static FileOpResultT file_write_string(const int8_t* filename, const int8_t* buffer)
{
    FileOpResultT result = FILE_WROTE_SUCCESFULLY;

    // Open the output file in write mode ("w" for ASCII text files)
    FILE* fileOut = fopen(filename, "w");

    if (fileOut == NULL)
    {
        LOG_ERROR("Cannot open %s for writing!\n", filename);
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO("Writing to %s\n", filename);

        // Write the buffer to the file

        size_t written_size = fprintf(fileOut, "%s", (const char*) buffer);

        if (written_size == 0)
        {
            LOG_ERROR("Error writing to file %s!Wrote %ld bytes.\n", filename, written_size);
            result = FILE_WRITE_ERROR;
        }
        else { LOG_INFO("Successfully wrote %ld bytes to %s.\n", written_size, filename); }

        fclose(fileOut);
    }

    return result;
}

inline static FileOpResultT file_write_binary(const int8_t* filename, const int8_t* buffer, size_t filesize)
{
    FileOpResultT result = FILE_WROTE_SUCCESFULLY;

    // Open the output file in binary write mode ("wb" for binary files)
    FILE* fileOut = fopen(filename, "wb");

    if (fileOut == NULL)
    {
        LOG_ERROR("Cannot open %s for writing!\n", filename);
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO("Writing to %s\n", filename);

        // Write the buffer to the file in binary mode
        size_t written_size = fwrite(buffer, 1, filesize, fileOut);

        if (written_size != filesize)
        {
            LOG_ERROR("Error writing to file %s! Expected %ld bytes, wrote %ld bytes.\n", filename, filesize,
                      written_size);
            result = FILE_WRITE_ERROR;
        }
        else { LOG_INFO("Successfully wrote %ld bytes to %s.\n", written_size, filename); }

        fclose(fileOut);
    }

    return result;
}

inline static void free_folder_contents_struct(FolderContentsT* contents)
{
    if (NULL != contents->files) { str_arr_destroy(contents->files); }
    if (NULL != contents->directories) { str_arr_destroy(contents->directories); }
}

inline static BOOL file_exists(const int8_t* path)
{
    FILE* filePtr = fopen(path, "r");
    BOOL result = FALSE;
    if (NULL != filePtr)
    {
        result = TRUE;
        fclose(filePtr);
    }
    return result;
}
#ifdef _WIN32
inline static FileOpResultT get_file_info(const int8_t* path, FileInfoT* fileInfoPtr)
{
    BOOL fileExists = file_exists(path);
    FileOpResultT result = FILE_DOES_NOT_EXIST;
    if (TRUE == fileExists)
    {
        result = FILE_OPERATION_SUCCESS;
        WIN32_FILE_ATTRIBUTE_DATA fInfo;
        GetFileAttributesEx(path, GetFileExInfoStandard, &fInfo);
        fileInfoPtr->path.data = path;
        fileInfoPtr->path.length = cstr_length(path);
        fileInfoPtr->fileAttributes = fInfo.dwFileAttributes;
        fileInfoPtr->fileSize[0] = fInfo.nFileSizeLow;
        fileInfoPtr->fileSize[1] = fInfo.nFileSizeHigh;
        fileInfoPtr->creationTime[0] = fInfo.ftCreationTime.dwLowDateTime;
        fileInfoPtr->creationTime[1] = fInfo.ftCreationTime.dwHighDateTime;
        fileInfoPtr->lastAccessTime[0] = fInfo.ftLastAccessTime.dwLowDateTime;
        fileInfoPtr->lastAccessTime[1] = fInfo.ftLastAccessTime.dwHighDateTime;
        fileInfoPtr->lastWriteTime[0] = fInfo.ftLastWriteTime.dwLowDateTime;
        fileInfoPtr->lastWriteTime[1] = fInfo.ftLastWriteTime.dwHighDateTime;
    }
    else { LOG_ERROR("File %s does not exit!\n", path); }
    return result;
}
#else
#include <sys/stat.h>

inline static FileOpResultT get_file_info(const int8_t* path, FileInfoT* fileInfoPtr)
{
    char* absolute_path = realpath(path, NULL);
    BOOL fileExists = file_exists(absolute_path);
    FileOpResultT result = FILE_DOES_NOT_EXIST;
    if (TRUE == fileExists)
    {
        struct stat fileStat;
        int32_t statResult = stat(absolute_path, &fileStat);
        if (statResult == 0)
        {
            CFREE(absolute_path, cstr_length(absolute_path));
            fileInfoPtr->path.data = path;
            fileInfoPtr->path.length = cstr_length(path);
            if (sizeof(fileStat.st_size) > 4u)
            {
                fileInfoPtr->fileSize[0] = (fileStat.st_size & ((uint32_t) (~0)));
                fileInfoPtr->fileSize[1] = ((fileStat.st_size >> 32) & ((uint32_t) (~0)));
            }
            else { fileInfoPtr->fileSize[0] = fileStat.st_size; }
            if (sizeof(fileStat.st_ctime) > 4u)
            {
                fileInfoPtr->creationTime[0] = (fileStat.st_ctime & ((uint32_t) (~0)));
                fileInfoPtr->creationTime[1] = ((fileStat.st_ctime >> 32) & ((uint32_t) (~0)));
            }
            else { fileInfoPtr->creationTime[0] = fileStat.st_ctime; }

            if (sizeof(fileStat.st_atime) > 4u)
            {
                fileInfoPtr->lastAccessTime[0] = (fileStat.st_atime & ((uint32_t) (~0)));
                fileInfoPtr->lastAccessTime[1] = ((fileStat.st_atime >> 32) & ((uint32_t) (~0)));
            }
            else { fileInfoPtr->lastAccessTime[0] = fileStat.st_atime; }

            if (sizeof(fileStat.st_mtime) > 4u)
            {
                fileInfoPtr->lastWriteTime[0] = (fileStat.st_mtime & ((uint32_t) (~0)));
                fileInfoPtr->lastWriteTime[1] = ((fileStat.st_mtime >> 32) & ((uint32_t) (~0)));
            }
            else { fileInfoPtr->lastWriteTime[0] = fileStat.st_mtime; }
            result = FILE_OPERATION_SUCCESS;
        }
        else { LOG_ERROR("Can not get file stat! \n%s\n", path); }
    }
    else { LOG_ERROR("File %s does not exit!\n", path); }
    return result;
}
#endif
#ifdef _WIN32

inline static BOOL list_directory_contents(const int8_t* dir, FolderContentsT* contents)
{
    contents->path = string_view_create(dir);
    contents->files = str_arr_create();
    contents->directories = str_arr_create();

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    int8_t sPath[MAX_PATH_SIZE];

    //Specify a file mask. *.*
    sprintf(sPath, "%s\\*.*", dir);

    if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        LOG_ERROR("Path not found: [%s]\n", dir);
        return FALSE;
    }

    do {
        BOOL skip = FALSE;
        //skip path/. and path/..
        if (fdFile.cFileName[0] == '.') { skip = TRUE; }

        if ((FALSE == skip) && (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            sprintf(sPath, "%s\\%s", dir, fdFile.cFileName);

            DStringT* str = str_create(&sPath[0], strlen(sPath));
            str_arr_push_back(contents->directories, str);
        }
        else if ((FALSE == skip))
        {
            sprintf(sPath, "%s\\%s", dir, fdFile.cFileName);

            DStringT* str = str_create(&sPath[0], strlen(sPath));
            str_arr_push_back(contents->files, str);
        }

    } while (FindNextFile(hFind, &fdFile));//Find the next file.

    FindClose(hFind);

    return TRUE;
}
#else

#include <errno.h>
#ifdef _DEFAULT_SOURCE
#undef _DEFAULT_SOURCE
#endif
#define _DEFAULT_SOURCE

inline static BOOL list_directory_contents(const int8_t* dir, FolderContentsT* contents)
{
    contents->files = str_arr_create();
    contents->directories = str_arr_create();

    BOOL result = FALSE;

    struct dirent** namelist;
    int32_t n;

    char* absolute_path = realpath(dir, NULL);

    n = scandir(absolute_path, &namelist, NULL, alphasort);
    if (n < 0) { LOG_ERROR("Scanning dir %s\nError: %s\n", absolute_path, strerror(errno)); }
    else
    {
        int32_t tempN = n;
        while (tempN--)
        {
            BOOL skip = FALSE;

            if (namelist[tempN]->d_name[0] == '.') { skip = TRUE; }

            if ((namelist[tempN]->d_type == DT_DIR) && (FALSE == skip))
            {
                DStringT* str = str_create(&namelist[tempN]->d_name[0], strlen(namelist[tempN]->d_name));
                str_arr_push_back(contents->directories, str);
            }
            else if (FALSE == skip)
            {
                DStringT* str = str_create(&namelist[tempN]->d_name[0], strlen(namelist[tempN]->d_name));
                str_arr_push_back(contents->files, str);
            }
            CFREE(namelist[tempN], sizeof(struct dirent));
        }
        CFREE(namelist, n);
        result = TRUE;
    }
    CFREE(absolute_path, cstr_length(absolute_path));
    return result;
}
#endif

#endif// CFILESYSTEM_HEADER
