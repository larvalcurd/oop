add_executable(tests test_numbers.cpp)
target_link_libraries(tests PRIVATE numbers_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

add_custom_command(
    TARGET tests POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)