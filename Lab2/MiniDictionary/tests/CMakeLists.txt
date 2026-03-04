add_executable(MiniDictionaryTests
    StringUtilsTests.cpp
    DictionaryTests.cpp
)

target_link_libraries(MiniDictionaryTests PRIVATE
    MiniDictionaryLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MiniDictionaryTests)

add_custom_command(
    TARGET MiniDictionaryTests
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)