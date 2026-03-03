include(FetchContent)

option(MINIDICTIONARY_USE_BUNDLED_GTEST "Download GoogleTest with FetchContent" ON)

if(MINIDICTIONARY_USE_BUNDLED_GTEST)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
else()
    find_package(GTest REQUIRED)
endif()

add_executable(MiniDictionaryTests
    StringUtilsTests.cpp
    DictionaryTests.cpp
)

target_link_libraries(MiniDictionaryTests PRIVATE
    MiniDictionaryLib
    GTest::gtest_main
)

if(MSVC)
    target_compile_options(MiniDictionaryTests PRIVATE /utf-8)
endif()

include(GoogleTest)
gtest_discover_tests(MiniDictionaryTests)