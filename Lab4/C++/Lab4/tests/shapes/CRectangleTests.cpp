#include <gtest/gtest.h>

#include <string>

#include "shapes/CRectangle.h"

namespace
{
constexpr double EPS = 1e-9;
}

// Additional edge and invalid input tests

TEST(CRectangleTests, ZeroWidthOrHeight)
{
    CRectangle rect1({0.0, 0.0}, 0.0, 10.0, 0x123456, 0x654321);
    EXPECT_DOUBLE_EQ(rect1.GetArea(), 0.0);
    EXPECT_DOUBLE_EQ(rect1.GetPerimeter(), 20.0);
    CRectangle rect2({0.0, 0.0}, 10.0, 0.0, 0x123456, 0x654321);
    EXPECT_DOUBLE_EQ(rect2.GetArea(), 0.0);
    EXPECT_DOUBLE_EQ(rect2.GetPerimeter(), 20.0);
}

TEST(CRectangleTests, NegativeWidthOrHeight)
{
    CRectangle rect1({0.0, 0.0}, -5.0, 10.0, 0x123456, 0x654321);
    EXPECT_NEAR(rect1.GetArea(), -50.0, EPS);
    EXPECT_NEAR(rect1.GetPerimeter(), 10.0, EPS);
    CRectangle rect2({0.0, 0.0}, 10.0, -5.0, 0x123456, 0x654321);
    EXPECT_NEAR(rect2.GetArea(), -50.0, EPS);
    EXPECT_NEAR(rect2.GetPerimeter(), 10.0, EPS);
}

TEST(CRectangleTests, InvalidColorValues)
{
    CRectangle rect({0.0, 0.0}, 1.0, 1.0, static_cast<uint32_t>(-1), static_cast<uint32_t>(-2));
    EXPECT_EQ(rect.GetOutlineColor(), 0xFFFFFFFFu);
    EXPECT_EQ(rect.GetFillColor(), 0xFFFFFFFEu);
}

TEST(CRectangleTests, CalculatesArea)
{
    CRectangle rectangle({10.0, 20.0}, 30.0, 40.0, 0xff0000, 0x00ff00);
    EXPECT_NEAR(rectangle.GetArea(), 1200.0, EPS);
}

TEST(CRectangleTests, CalculatesPerimeter)
{
    CRectangle rectangle({10.0, 20.0}, 30.0, 40.0, 0xff0000, 0x00ff00);
    EXPECT_NEAR(rectangle.GetPerimeter(), 140.0, EPS);
}

TEST(CRectangleTests, ReturnsGeometryGetters)
{
    CRectangle rectangle({-3.5, 2.25}, 7.75, 9.5, 0xabcd01, 0x102030);

    const auto leftTop = rectangle.GetLeftTop();
    EXPECT_NEAR(leftTop.x, -3.5, EPS);
    EXPECT_NEAR(leftTop.y, 2.25, EPS);
    EXPECT_NEAR(rectangle.GetWidth(), 7.75, EPS);
    EXPECT_NEAR(rectangle.GetHeight(), 9.5, EPS);
}

TEST(CRectangleTests, ReturnsColors)
{
    CRectangle rectangle({0.0, 0.0}, 1.0, 2.0, 0xabcd01, 0x102030);

    EXPECT_EQ(rectangle.GetOutlineColor(), 0xabcd01u);
    EXPECT_EQ(rectangle.GetFillColor(), 0x102030u);
}

TEST(ShapeToStringTests, RectangleContainsRequiredFields)
{
    CRectangle rectangle({10.0, 20.0}, 30.0, 40.0, 0xff0000, 0x00ff00);
    const std::string text = rectangle.ToString();

    EXPECT_NE(text.find("Rectangle:"), std::string::npos);
    EXPECT_NE(text.find("Left top:"), std::string::npos);
    EXPECT_NE(text.find("Width:"), std::string::npos);
    EXPECT_NE(text.find("Height:"), std::string::npos);
    EXPECT_NE(text.find("Area:"), std::string::npos);
    EXPECT_NE(text.find("Perimeter:"), std::string::npos);
    EXPECT_NE(text.find("Outline color:"), std::string::npos);
    EXPECT_NE(text.find("Fill color:"), std::string::npos);
}
