add_library(MiniDictionaryLib STATIC
    StringUtils.h
    StringUtils.cpp
    Dictionary.h
    Dictionary.cpp
)

if(MSVC)
    target_compile_options(MiniDictionaryLib PRIVATE /utf-8)
endif()

add_executable(MiniDictionary main.cpp)
target_link_libraries(MiniDictionary PRIVATE MiniDictionaryLib)

if(MSVC)
    target_compile_options(MiniDictionary PRIVATE /utf-8)
endif()

target_include_directories(MiniDictionaryLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})