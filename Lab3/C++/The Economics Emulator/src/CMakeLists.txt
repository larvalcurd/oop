add_library(EconomicsLib STATIC
        Bank.h
        Bank.cpp
        Actor.h
        Actor.cpp
        Simulation.h
        Simulation.cpp
        Actors/Homer.h
        Actors/Homer.cpp
        Actors/Marge.h
        Actors/Marge.cpp
        Actors/Child.h
        Actors/Child.cpp
        Actors/Bart.h
        Actors/Bart.cpp
        Actors/Lisa.h
        Actors/Lisa.cpp
        Actors/Apu.h
        Actors/Apu.cpp
        Actors/Burns.h
        Actors/Burns.cpp
        Actors/Nelson.h
        Actors/Nelson.cpp
        Actors/Snake.h
        Actors/Snake.cpp
        Actors/Smithers.h
        Actors/Smithers.cpp
)

target_include_directories(EconomicsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(EconomicsEmulator main.cpp)
target_link_libraries(EconomicsEmulator PRIVATE EconomicsLib)