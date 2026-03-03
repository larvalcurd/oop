cmake_minimum_required (VERSION 3.14)

project(MiniDictionary LANGUAGES CXX)

if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(MINIDICTIONARY_BUILD_TESTS "Build MiniDictionary tests" ON)

add_subdirectory(src)

if(MINIDICTIONARY_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()