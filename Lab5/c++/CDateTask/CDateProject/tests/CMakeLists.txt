add_executable(cdate_tests
        CDateDefaultCtorTests.cpp
        CDateTimestampCtorTests.cpp
        CDateGettersTests.cpp
        CDateYmdCtorTests.cpp
        CDateCtorEquivalenceTests.cpp
        CDateYmdCtorValidationTests.cpp
        CDateWeekDayTests.cpp
        CDatePrefixTests.cpp
        CDatePostfixTests.cpp
        CDateAdditionTests.cpp
        CDateFreeAdditionTests.cpp
        CDateSubtractionTests.cpp
        CDateDifferenceTests.cpp
        CDateCompoundAssignmentTests.cpp
        CDateComparisonTests.cpp
        CDateInputTests.cpp
        CDateOutputTests.cpp
        CDateBoundaryTests.cpp)

target_link_libraries(cdate_tests PRIVATE
        cdate_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cdate_tests)