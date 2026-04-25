add_library(Lab4Core STATIC
    shapes/CLineSegment.cpp
    shapes/CRectangle.cpp
    shapes/CTriangle.cpp
    shapes/CCircle.cpp
    app/CShapeFactory.cpp
    app/ShapeManager.cpp
    canvas/CCanvas.cpp
)

target_include_directories(Lab4Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lab4Core PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(Lab4 main.cpp)
target_link_libraries(Lab4 PRIVATE Lab4Core)
