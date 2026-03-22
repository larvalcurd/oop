add_executable(EconomicsTests
    BankTests.cpp
    BankEdgeTests.cpp
    ActorTests.cpp
    SimulationTests.cpp
)

target_link_libraries(EconomicsTests PRIVATE
    EconomicsLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(EconomicsTests)

add_custom_command(
    TARGET EconomicsTests
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests..."
)
