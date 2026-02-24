add_library(PrimeNumberGeneratorLib STATIC
    "PrimeGenerator.h"
    "PrimeGenerator.cpp"
    "ArgsParser.h"
    "ArgsParser.cpp"
)

target_include_directories(PrimeNumberGeneratorLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PrimeNumberGenerator "main.cpp")

target_link_libraries(PrimeNumberGenerator PRIVATE PrimeNumberGeneratorLib)