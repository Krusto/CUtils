
set(ZLIB_USE_STATIC_LIBS "ON")
cmake_minimum_required(VERSION 3.5.0)
project(CUtil VERSION 0.1.0 LANGUAGES C)

add_executable(CUtil main.c)

add_executable(CUtilTests ./tests/mainTest.c ./vendor/munit/munit.c)
target_include_directories(CUtilTests PRIVATE ./vendor/munit)