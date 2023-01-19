cmake_minimum_required(VERSION 3.16)
project(DynamicArray C)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_C_STANDARD 11)
enable_testing()

add_executable(tests tests.c da_tests.c)

add_test(test_create ./tests test_create)
add_test(test_destroy ./tests test_destroy)
add_test(test_clear ./tests test_clear)