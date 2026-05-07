add_executable(MyTests
        CDateTests.cpp
)

target_link_libraries(MyTests PRIVATE
        cdate_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cdate_tests)