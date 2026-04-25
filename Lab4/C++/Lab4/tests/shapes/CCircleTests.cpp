#include <gtest/gtest.h>

#include <numbers>
#include <string>

#include "shapes/CCircle.h"

namespace
{
constexpr double EPS = 1e-9;
}

// Additional edge and invalid input tests

TEST(CCircleTests, ZeroRadius)
{
    CCircle circle({0.0, 0.0}, 0.0, 0x123456, 0x654321);
    EXPECT_DOUBLE_EQ(circle.GetArea(), 0.0);
    EXPECT_DOUBLE_EQ(circle.GetPerimeter(), 0.0);
}

TEST(CCircleTests, NegativeRadius)
{
    CCircle circle({0.0, 0.0}, -5.0, 0x123456, 0x654321);
    EXPECT_NEAR(circle.GetArea(), 25.0 * std::numbers::pi, EPS);
    EXPECT_NEAR(circle.GetPerimeter(), 10.0 * std::numbers::pi, EPS);
}

TEST(CCircleTests, InvalidColorValues)
{
    CCircle circle({0.0, 0.0}, 1.0, static_cast<uint32_t>(-1), static_cast<uint32_t>(-2));
    EXPECT_EQ(circle.GetOutlineColor(), 0xFFFFFFFFu);
    EXPECT_EQ(circle.GetFillColor(), 0xFFFFFFFEu);
}

TEST(CCircleTests, CalculatesArea)
{
    CCircle circle({0.0, 0.0}, 2.0, 0xff0000, 0x00ff00);
    EXPECT_NEAR(circle.GetArea(), std::numbers::pi * 4.0, EPS);
}

TEST(CCircleTests, CalculatesPerimeter)
{
    CCircle circle({0.0, 0.0}, 2.0, 0xff0000, 0x00ff00);
    EXPECT_NEAR(circle.GetPerimeter(), 2.0 * std::numbers::pi * 2.0, EPS);
}

TEST(CCircleTests, ReturnsCenterAndRadius)
{
    CCircle circle({1.25, -7.5}, 3.75, 0x111111, 0x222222);

    const auto center = circle.GetCenter();
    EXPECT_NEAR(center.x, 1.25, EPS);
    EXPECT_NEAR(center.y, -7.5, EPS);
    EXPECT_NEAR(circle.GetRadius(), 3.75, EPS);
}

TEST(CCircleTests, ReturnsColors)
{
    CCircle circle({0.0, 0.0}, 1.0, 0xa1b2c3, 0x0a0b0c);

    EXPECT_EQ(circle.GetOutlineColor(), 0xa1b2c3u);
    EXPECT_EQ(circle.GetFillColor(), 0x0a0b0cu);
}

TEST(ShapeToStringTests, CircleContainsRequiredFields)
{
    CCircle circle({5.0, 6.0}, 7.0, 0xaabbcc, 0x010203);
    const std::string text = circle.ToString();

    EXPECT_NE(text.find("Circle:"), std::string::npos);
    EXPECT_NE(text.find("Center:"), std::string::npos);
    EXPECT_NE(text.find("Radius:"), std::string::npos);
    EXPECT_NE(text.find("Area:"), std::string::npos);
    EXPECT_NE(text.find("Perimeter:"), std::string::npos);
    EXPECT_NE(text.find("Outline color:"), std::string::npos);
    EXPECT_NE(text.find("Fill color:"), std::string::npos);
}
