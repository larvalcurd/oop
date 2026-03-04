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