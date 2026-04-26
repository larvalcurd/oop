add_executable(CMyStringTests 
ConstructorTests.cpp 
CopyTests.cpp 
ConcatenationTests.cpp 
MoveTests.cpp 
ComparisonTests.cpp
StringAccessTests.cpp
SubstringTests.cpp
StreamOperatorsTests.cpp
) 
target_link_libraries(CMyStringTests PRIVATE CMyString GTest::gtest GTest::gtest_main)
target_include_directories(CMyStringTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(CMyStringTests)

add_custom_command(
	TARGET CMyStringTests
	POST_BUILD
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Running tests..."
)
