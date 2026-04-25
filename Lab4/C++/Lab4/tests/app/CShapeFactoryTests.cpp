#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

#include "app/CShapeFactory.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"

namespace
{
constexpr double EPS = 1e-9;
}

TEST(CShapeFactoryTests, CreatesLineFromValidInput)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("line 0 0 3 4 ff0000");

    ASSERT_NE(shape, nullptr);
    auto line = std::dynamic_pointer_cast<CLineSegment>(shape);
    ASSERT_NE(line, nullptr);

    EXPECT_NEAR(line->GetPerimeter(), 5.0, EPS);
    EXPECT_EQ(line->GetOutlineColor(), 0xff0000u);
}

TEST(CShapeFactoryTests, CreatesRectangleFromValidInput)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("rectangle 10 20 30 40 ff0000 00ff00");

    ASSERT_NE(shape, nullptr);
    auto rectangle = std::dynamic_pointer_cast<CRectangle>(shape);
    ASSERT_NE(rectangle, nullptr);

    EXPECT_NEAR(rectangle->GetArea(), 1200.0, EPS);
    EXPECT_NEAR(rectangle->GetPerimeter(), 140.0, EPS);
    EXPECT_EQ(rectangle->GetOutlineColor(), 0xff0000u);
    EXPECT_EQ(rectangle->GetFillColor(), 0x00ff00u);
}

TEST(CShapeFactoryTests, CreatesTriangleFromValidInput)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("triangle 0 0 4 0 0 3 ff0000 00ff00");

    ASSERT_NE(shape, nullptr);
    auto triangle = std::dynamic_pointer_cast<CTriangle>(shape);
    ASSERT_NE(triangle, nullptr);

    EXPECT_NEAR(triangle->GetArea(), 6.0, EPS);
    EXPECT_NEAR(triangle->GetPerimeter(), 12.0, EPS);
    EXPECT_EQ(triangle->GetOutlineColor(), 0xff0000u);
    EXPECT_EQ(triangle->GetFillColor(), 0x00ff00u);
}

TEST(CShapeFactoryTests, CreatesCircleFromValidInput)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("circle 10 20 15 ff0000 00ff00");

    ASSERT_NE(shape, nullptr);
    auto circle = std::dynamic_pointer_cast<CCircle>(shape);
    ASSERT_NE(circle, nullptr);

    EXPECT_NEAR(circle->GetRadius(), 15.0, EPS);
    EXPECT_EQ(circle->GetOutlineColor(), 0xff0000u);
    EXPECT_EQ(circle->GetFillColor(), 0x00ff00u);
}

TEST(CShapeFactoryTests, AcceptsUppercaseHexColor)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("line 0 0 1 0 ABCDEF");

    auto line = std::dynamic_pointer_cast<CLineSegment>(shape);
    ASSERT_NE(line, nullptr);
    EXPECT_EQ(line->GetOutlineColor(), 0xabcdefu);
}

TEST(CShapeFactoryTests, AcceptsLowercaseAndMixedCaseHexColor)
{
    CShapeFactory factory;
    auto shape1 = factory.CreateShape("line 0 0 1 0 abcdef");
    auto shape2 = factory.CreateShape("line 0 0 1 0 aBcDeF");
    auto line1 = std::dynamic_pointer_cast<CLineSegment>(shape1);
    auto line2 = std::dynamic_pointer_cast<CLineSegment>(shape2);
    ASSERT_NE(line1, nullptr);
    ASSERT_NE(line2, nullptr);
    EXPECT_EQ(line1->GetOutlineColor(), 0xabcdefu);
    EXPECT_EQ(line2->GetOutlineColor(), 0xabcdefu);
}

TEST(CShapeFactoryTests, ThrowsOnColorWithWhitespace)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 0 ab cd ef"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnColorWithInvalidCharAtStart)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 0 zbcdef"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnColorWithInvalidCharAtEnd)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 0 abcdez"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnScientificNotationNegativeOrZero)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("rectangle 1e1 2e1 -3e1 4e1 ff0000 00ff00"), std::invalid_argument);
    EXPECT_THROW(factory.CreateShape("circle 0 0 -1e1 ff0000 00ff00"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnEmptyInput)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape(""), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnUnknownShape)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("hexagon 0 0 10 ff0000 00ff00"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnMissingLineParameters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 ff0000"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnExtraLineParameters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 1 ff0000 extra"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnZeroLengthLine)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 1 1 1 1 ff0000"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnRectangleWithNonPositiveDimensions)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("rectangle 0 0 0 10 ff0000 00ff00"), std::invalid_argument);
    EXPECT_THROW(factory.CreateShape("rectangle 0 0 10 -1 ff0000 00ff00"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnExtraRectangleParameters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("rectangle 0 0 10 10 ff0000 00ff00 extra"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnTriangleWithCollinearPoints)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("triangle 0 0 1 1 2 2 ff0000 00ff00"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnExtraTriangleParameters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("triangle 0 0 1 0 0 1 ff0000 00ff00 extra"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnCircleWithNonPositiveRadius)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("circle 0 0 0 ff0000 00ff00"), std::invalid_argument);
    EXPECT_THROW(factory.CreateShape("circle 0 0 -1 ff0000 00ff00"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnExtraCircleParameters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("circle 0 0 5 ff0000 00ff00 extra"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnInvalidColorLength)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 1 fff"), std::invalid_argument);
}

TEST(CShapeFactoryTests, ThrowsOnInvalidColorCharacters)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line 0 0 1 1 zzzzzz"), std::invalid_argument);
}

TEST(CShapeFactoryTests, AcceptsLeadingAndTrailingWhitespace)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("   circle 0 0 2 ff0000 00ff00   ");

    auto circle = std::dynamic_pointer_cast<CCircle>(shape);
    ASSERT_NE(circle, nullptr);
    EXPECT_NEAR(circle->GetRadius(), 2.0, EPS);
}

TEST(CShapeFactoryTests, AcceptsScientificNotation)
{
    CShapeFactory factory;
    auto shape = factory.CreateShape("rectangle 1e1 2e1 3e1 4e1 ff0000 00ff00");

    auto rectangle = std::dynamic_pointer_cast<CRectangle>(shape);
    ASSERT_NE(rectangle, nullptr);
    EXPECT_NEAR(rectangle->GetLeftTop().x, 10.0, EPS);
    EXPECT_NEAR(rectangle->GetLeftTop().y, 20.0, EPS);
    EXPECT_NEAR(rectangle->GetWidth(), 30.0, EPS);
    EXPECT_NEAR(rectangle->GetHeight(), 40.0, EPS);
}

TEST(CShapeFactoryTests, RejectsNaNCoordinates)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("line nan 0 1 1 ff0000"), std::invalid_argument);
}

TEST(CShapeFactoryTests, RejectsInfRadius)
{
    CShapeFactory factory;
    EXPECT_THROW(factory.CreateShape("circle 0 0 inf ff0000 00ff00"), std::invalid_argument);
}
