cmake_minimum_required(VERSION 3.16)
project(DynamicArray C)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_C_STANDARD 11)

add_executable(test da_tests.c)