add_executable(Lab4Tests
        shapes/CLineSegmentTests.cpp
        shapes/CRectangleTests.cpp
        shapes/CTriangleTests.cpp
        shapes/CCircleTests.cpp
        app/CShapeFactoryTests.cpp
        app/ShapeManagerTests.cpp
        canvas/ShapeDrawTests.cpp
        canvas/ShapeManagerDrawOrderTests.cpp
        canvas/CCanvasTests.cpp
)

target_link_libraries(Lab4Tests PRIVATE
        Lab4Core
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Lab4Tests)

add_custom_command(
        TARGET Lab4Tests
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --build-config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests..."
)
