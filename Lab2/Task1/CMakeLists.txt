cmake_minimum_required(VERSION 3.10)

project("Task1" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(external/googletest/googletest-1.14.0)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)