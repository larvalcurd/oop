add_library(cdate_lib STATIC
    CDate.cpp
    CDate.h
)

target_include_directories(cdate_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cdate_app main.cpp)

target_link_libraries(cdate_app PRIVATE cdate_lib)
