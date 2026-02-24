include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UrlParserTests UrlParserTests.cpp)

target_link_libraries(UrlParserTests PRIVATE
    UrlParserLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UrlParserTests)

add_custom_command(
    TARGET UrlParserTests
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)