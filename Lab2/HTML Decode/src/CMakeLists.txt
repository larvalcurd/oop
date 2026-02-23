# Библиотека с логикой
add_library(html_decode_lib
    html_decode.cpp
    html_decode.h
)
target_include_directories(html_decode_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл
add_executable(HtmlDecode main.cpp)
target_link_libraries(HtmlDecode PRIVATE html_decode_lib)