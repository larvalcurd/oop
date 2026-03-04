add_library(numbers_lib
    numbers.cpp
    numbers.h
)

target_include_directories(numbers_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Task1 main.cpp)
target_link_libraries(Task1 PRIVATE numbers_lib)