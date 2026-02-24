add_executable(PrimeNumberGeneratorTests
    "PrimeGeneratorTests.cpp"
    "ArgsParserTests.cpp"
)

target_link_libraries(PrimeNumberGeneratorTests PRIVATE
    PrimeNumberGeneratorLib
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(PrimeNumberGeneratorTests)

add_custom_command(
    TARGET PrimeNumberGeneratorTests
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)