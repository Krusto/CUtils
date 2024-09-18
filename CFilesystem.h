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
#include "DArray.h"
#include "STDTypes.h"

#ifndef NO_STD_MALLOC
#include <stdio.h>
#include <stdlib.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

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
    FILE_UNKNOWN_ERROR,
    FILE_BUFFER_ALLOCATION_ERROR
} FileOpResultType;

typedef struct {
    const int8_t* path;
    DArray_t( int8_t*, files );
} FolderContentsType;

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
FileOpResultType file_read_binary( const int8_t* filename, size_t* filesize, uint8_t** buffer )
{
    FileOpResultType result = FILE_READ_SUCCESFULLY;
    // start processing
    FILE* fileIn = fopen( filename, "rb" );// open input file (binary)

    if ( fileIn == NULL )
    {
        LOG_ERROR( "Can not open %s!\n", filename );
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO( "Opened %s\n", filename );
        // obtain file size.
        fseek( fileIn, 0, SEEK_END );
        *filesize = ftell( fileIn );
        rewind( fileIn );
        LOG_INFO( "Filesize %d bytes.\n", *filesize );

        // allocate memory to contain the whole file.
        *buffer = ( uint8_t* ) CMALLOC( *filesize );
        if ( buffer == NULL )
        {
            LOG_ERROR( "Malloc for input file buffer failed(not enough memory?)\n" );
            result = FILE_BUFFER_ALLOCATION_ERROR;
        }
        else
        {
            // copy the file into the buffer.
            fread( buffer, 1, *filesize, fileIn );
        }

        fclose( fileIn );
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
FileOpResultType file_read_string( const int8_t* filename, size_t* filesize, uint8_t** buffer )
{
    FileOpResultType result = FILE_READ_SUCCESFULLY;

    // Open the input file in text mode
    FILE* fileIn = fopen( filename, "r" );// "r" for reading ASCII files

    if ( fileIn == NULL )
    {
        LOG_ERROR( "Cannot open %s!\n", filename );
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO( "Opened %s\n", filename );

        // Obtain file size
        fseek( fileIn, 0, SEEK_END );
        *filesize = ftell( fileIn );
        rewind( fileIn );
        LOG_INFO( "Filesize %d bytes.\n", *filesize );

        // Allocate memory for the file content
        *buffer = ( uint8_t* ) CMALLOC( *filesize + 1 );// Extra byte for null-terminator for text
        if ( *buffer == NULL )
        {
            LOG_ERROR( "Memory allocation for input file buffer failed (not enough memory?)\n" );
            result = FILE_BUFFER_ALLOCATION_ERROR;
        }
        else
        {
            // Read the file into the buffer
            fread( *buffer, 1, *filesize, fileIn );
            ( *buffer )[ *filesize ] = '\0';// Null-terminate for safe string handling
        }

        fclose( fileIn );
    }

    return result;
}

/**
 * @brief Writes string to a file
 * @param filename Path to the file
 * @param buffer String to write
 * @return File Operation Result
 */
FileOpResultType file_write_string( const int8_t* filename, const int8_t* buffer )
{
    FileOpResultType result = FILE_WROTE_SUCCESFULLY;

    // Open the output file in write mode ("w" for ASCII text files)
    FILE* fileOut = fopen( filename, "w" );

    if ( fileOut == NULL )
    {
        LOG_ERROR( "Cannot open %s for writing!\n", filename );
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO( "Writing to %s\n", filename );

        // Write the buffer to the file

        size_t written_size = fprintf( fileOut, buffer );

        if ( written_size == 0 )
        {
            LOG_ERROR( "Error writing to file %s!Wrote %d bytes.\n", filename, written_size );
            result = FILE_WRITE_ERROR;
        }
        else { LOG_INFO( "Successfully wrote %d bytes to %s.\n", written_size, filename ); }

        fclose( fileOut );
    }

    return result;
}

/**
 * @brief Writes binary buffer to file
 * @param filename Path to the file
 * @param buffer Buffer to write
 * @param filesize Size of the buffer to write
 * @return File Operation Result
 */
FileOpResultType file_write_binary( const int8_t* filename, const uint8_t* buffer, size_t filesize )
{
    FileOpResultType result = FILE_WROTE_SUCCESFULLY;

    // Open the output file in binary write mode ("wb" for binary files)
    FILE* fileOut = fopen( filename, "wb" );

    if ( fileOut == NULL )
    {
        LOG_ERROR( "Cannot open %s for writing!\n", filename );
        result = FILE_OPEN_ERROR;
    }
    else
    {
        LOG_INFO( "Writing to %s\n", filename );

        // Write the buffer to the file in binary mode
        size_t written_size = fwrite( buffer, 1, filesize, fileOut );

        if ( written_size != filesize )
        {
            LOG_ERROR( "Error writing to file %s! Expected %d bytes, wrote %d bytes.\n", filename, filesize,
                       written_size );
            result = FILE_WRITE_ERROR;
        }
        else { LOG_INFO( "Successfully wrote %d bytes to %s.\n", written_size, filename ); }

        fclose( fileOut );
    }

    return result;
}

#ifdef _WIN32
BOOL list_directory_contents( const int8_t* dir )
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    int8_t sPath[ 2048 ];

    //Specify a file mask. *.* = We want everything!
    sprintf( sPath, "%s\\*.*", dir );

    if ( ( hFind = FindFirstFile( sPath, &fdFile ) ) == INVALID_HANDLE_VALUE )
    {
        LOG_ERROR( "Path not found: [%s]\n", dir );
        return FALSE;
    }

    do {
        if ( strcmp( fdFile.cFileName, "." ) != 0 && strcmp( fdFile.cFileName, ".." ) != 0 )
        {
            sprintf( sPath, "%s\\%s", dir, fdFile.cFileName );

            if ( fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { LOG_INFO( "Directory: %s\n", sPath ); }
            else { LOG_INFO( "File: %s\n", sPath ); }
        }
    } while ( FindNextFile( hFind, &fdFile ) );//Find the next file.

    FindClose( hFind );//Always, Always, clean things up!

    return TRUE;
}
#endif

#endif// CFILESYSTEM_HEADER