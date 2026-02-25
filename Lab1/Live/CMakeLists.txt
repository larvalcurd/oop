cmake_minimum_required(VERSION 3.14)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Основная библиотека (без main) ---
add_library(life_lib STATIC src/life.cpp)
target_include_directories(life_lib PUBLIC src)

# --- Исполняемый файл ---
add_executable(live src/main.cpp)
target_link_libraries(live PRIVATE life_lib)

# --- Google Test ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(life_tests tests/test_life.cpp)
target_link_libraries(life_tests PRIVATE life_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(life_tests)

add_custom_command(
    TARGET life_tests
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)