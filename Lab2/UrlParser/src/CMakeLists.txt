add_library(UrlParserLib STATIC
    UrlParser.h
    UrlParser.cpp
)

target_include_directories(UrlParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(UrlParser main.cpp)
target_link_libraries(UrlParser PRIVATE UrlParserLib)