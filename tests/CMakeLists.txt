project(CUtil_Tests)
set(CMAKE_CXX_FLAGS --coverage)
add_compile_options(-fpermissive) # add because we are using c++ test library for c
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(CUtil_Test mainTest.cpp)

target_link_libraries(CUtil_Test PUBLIC GTest::gtest_main)

set_target_properties(CUtil_Test PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CUtil_Test PRIVATE ../include)

target_include_directories(CUtil_Test PRIVATE ${CMAKE_SOURCE_DIR}/vendor/gmock-global-1.0.2/include)

add_test(CUtil_Tests CUtil_Test)

include(GoogleTest)
gtest_discover_tests(CUtil_Test)