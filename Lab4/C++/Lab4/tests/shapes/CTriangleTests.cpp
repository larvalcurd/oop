#include <gtest/gtest.h>

#include <string>

#include "shapes/CTriangle.h"

namespace
{
constexpr double EPS = 1e-9;
}

// Additional edge and invalid input tests

TEST(CTriangleTests, CollinearPointsAreaZero)
{
    CTriangle triangle({0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, 0x123456, 0x654321);
    EXPECT_NEAR(triangle.GetArea(), 0.0, EPS);
}

TEST(CTriangleTests, DegenerateTrianglePerimeter)
{
    CTriangle triangle({0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, 0x123456, 0x654321);
    EXPECT_NEAR(triangle.GetArea(), 0.0, EPS);
    EXPECT_NEAR(triangle.GetPerimeter(), 0.0, EPS);
}

TEST(CTriangleTests, InvalidColorValues)
{
    CTriangle triangle({0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}, static_cast<uint32_t>(-1), static_cast<uint32_t>(-2));
    EXPECT_EQ(triangle.GetOutlineColor(), 0xFFFFFFFFu);
    EXPECT_EQ(triangle.GetFillColor(), 0xFFFFFFFEu);
}

TEST(CTriangleTests, CalculatesArea)
{
    CTriangle triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}, 0xff0000, 0x00ff00);
    EXPECT_NEAR(triangle.GetArea(), 6.0, EPS);
}

TEST(CTriangleTests, CalculatesPerimeter)
{
    CTriangle triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}, 0xff0000, 0x00ff00);
    EXPECT_NEAR(triangle.GetPerimeter(), 12.0, EPS);
}

TEST(CTriangleTests, CalculatesAreaAndPerimeterForNonIntegerCoordinates)
{
    CTriangle triangle({0.5, 1.0}, {2.0, 1.0}, {0.5, 3.0}, 0x123456, 0x654321);

    EXPECT_NEAR(triangle.GetArea(), 1.5, EPS);
    EXPECT_NEAR(triangle.GetPerimeter(), 1.5 + 2.0 + 2.5, EPS);
}

TEST(CTriangleTests, ReturnsVertices)
{
    CTriangle triangle({1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, 0x123456, 0x654321);

    const auto v1 = triangle.GetVertex1();
    const auto v2 = triangle.GetVertex2();
    const auto v3 = triangle.GetVertex3();

    EXPECT_NEAR(v1.x, 1.0, EPS);
    EXPECT_NEAR(v1.y, 2.0, EPS);
    EXPECT_NEAR(v2.x, 3.0, EPS);
    EXPECT_NEAR(v2.y, 4.0, EPS);
    EXPECT_NEAR(v3.x, 5.0, EPS);
    EXPECT_NEAR(v3.y, 6.0, EPS);
}

TEST(CTriangleTests, ReturnsColors)
{
    CTriangle triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}, 0xabcdef, 0x012345);

    EXPECT_EQ(triangle.GetOutlineColor(), 0xabcdefu);
    EXPECT_EQ(triangle.GetFillColor(), 0x012345u);
}

TEST(ShapeToStringTests, TriangleContainsRequiredFields)
{
    CTriangle triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}, 0x123456, 0x654321);
    const std::string text = triangle.ToString();

    EXPECT_NE(text.find("Triangle:"), std::string::npos);
    EXPECT_NE(text.find("Vertex1:"), std::string::npos);
    EXPECT_NE(text.find("Vertex2:"), std::string::npos);
    EXPECT_NE(text.find("Vertex3:"), std::string::npos);
    EXPECT_NE(text.find("Area:"), std::string::npos);
    EXPECT_NE(text.find("Perimeter:"), std::string::npos);
    EXPECT_NE(text.find("Outline color:"), std::string::npos);
    EXPECT_NE(text.find("Fill color:"), std::string::npos);
}
