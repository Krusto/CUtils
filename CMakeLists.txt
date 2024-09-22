
set(ZLIB_USE_STATIC_LIBS "ON")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

cmake_minimum_required(VERSION 3.5.0)
project(CUtil VERSION 0.1.0)

add_executable(CUtil main.c)

add_subdirectory(tests)