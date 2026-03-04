add_library(MiniDictionaryLib STATIC
    StringUtils.h
    StringUtils.cpp
    Dictionary.h
    Dictionary.cpp
)

target_include_directories(MiniDictionaryLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(MiniDictionary main.cpp)
target_link_libraries(MiniDictionary PRIVATE MiniDictionaryLib)