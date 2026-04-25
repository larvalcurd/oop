#include <gtest/gtest.h>

#include <string>

#include "shapes/CLineSegment.h"

namespace
{
constexpr double EPS = 1e-9;
}

// Additional edge and invalid input tests

TEST(CLineSegmentTests, ZeroLengthSegment)
{
    CLineSegment line({1.0, 1.0}, {1.0, 1.0}, 0x123456);
    EXPECT_DOUBLE_EQ(line.GetPerimeter(), 0.0);
    EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);
}

TEST(CLineSegmentTests, NegativeColorValue)
{
    CLineSegment line({0.0, 0.0}, {1.0, 1.0}, static_cast<uint32_t>(-1));
    EXPECT_EQ(line.GetOutlineColor(), 0xFFFFFFFFu);
}

TEST(CLineSegmentTests, HasZeroArea)
{
    CLineSegment line({0.0, 0.0}, {3.0, 4.0}, 0xff0000);
    EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);
}

TEST(CLineSegmentTests, CalculatesPerimeterAsLength)
{
    CLineSegment line({0.0, 0.0}, {3.0, 4.0}, 0xff0000);
    EXPECT_NEAR(line.GetPerimeter(), 5.0, EPS);
}

TEST(CLineSegmentTests, ReturnsStartPointAndEndPoint)
{
    CLineSegment line({1.25, -2.5}, {3.75, 4.5}, 0x123abc);

    const auto start = line.GetStartPoint();
    const auto end = line.GetEndPoint();

    EXPECT_NEAR(start.x, 1.25, EPS);
    EXPECT_NEAR(start.y, -2.5, EPS);
    EXPECT_NEAR(end.x, 3.75, EPS);
    EXPECT_NEAR(end.y, 4.5, EPS);
}

TEST(CLineSegmentTests, ReturnsOutlineColor)
{
    CLineSegment line({0.0, 1.0}, {2.0, 3.0}, 0x00ff0a);
    EXPECT_EQ(line.GetOutlineColor(), 0x00ff0au);
}

TEST(CLineSegmentTests, CalculatesPerimeterForVerticalSegment)
{
    CLineSegment line({5.0, 1.0}, {5.0, 8.0}, 0x000000);
    EXPECT_NEAR(line.GetPerimeter(), 7.0, EPS);
}

TEST(ShapeToStringTests, LineContainsRequiredFields)
{
    CLineSegment line({1.0, 2.0}, {3.0, 4.0}, 0x112233);
    const std::string text = line.ToString();

    EXPECT_NE(text.find("LineSegment:"), std::string::npos);
    EXPECT_NE(text.find("Start:"), std::string::npos);
    EXPECT_NE(text.find("End:"), std::string::npos);
    EXPECT_NE(text.find("Area:"), std::string::npos);
    EXPECT_NE(text.find("Perimeter:"), std::string::npos);
    EXPECT_NE(text.find("Outline color:"), std::string::npos);
}
