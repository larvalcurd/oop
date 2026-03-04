add_library(html_decode_lib
    HtmlDecode.cpp
    HtmlDecode.h
)

target_include_directories(html_decode_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(HtmlDecode main.cpp)
target_link_libraries(HtmlDecode PRIVATE html_decode_lib)