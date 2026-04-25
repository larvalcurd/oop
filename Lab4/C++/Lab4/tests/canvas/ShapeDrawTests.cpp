#include <gtest/gtest.h>

#include "TestCanvas.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"

namespace
{
constexpr double EPS = 1e-9;
}

TEST(ShapeDrawTests, LineDrawsOneLinePrimitive)
{
    CLineSegment line({1.0, 2.0}, {3.0, 4.0}, 0x112233);
    CTestCanvas canvas;

    line.Draw(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 1u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Line);
    EXPECT_EQ(canvas.GetEvents()[0].index, 0u);

    ASSERT_EQ(canvas.GetLines().size(), 1u);
    EXPECT_EQ(canvas.GetCircles().size(), 0u);
    EXPECT_EQ(canvas.GetPolygons().size(), 0u);

    const auto& call = canvas.GetLines()[0];
    EXPECT_NEAR(call.from.x, 1.0, EPS);
    EXPECT_NEAR(call.from.y, 2.0, EPS);
    EXPECT_NEAR(call.to.x, 3.0, EPS);
    EXPECT_NEAR(call.to.y, 4.0, EPS);
    EXPECT_EQ(call.color, 0x112233u);
}

TEST(ShapeDrawTests, CircleDrawsOneCirclePrimitive)
{
    CCircle circle({5.0, 6.0}, 7.5, 0xaabbcc, 0x010203);
    CTestCanvas canvas;

    circle.Draw(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 1u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Circle);
    EXPECT_EQ(canvas.GetEvents()[0].index, 0u);

    ASSERT_EQ(canvas.GetCircles().size(), 1u);
    EXPECT_EQ(canvas.GetLines().size(), 0u);
    EXPECT_EQ(canvas.GetPolygons().size(), 0u);

    const auto& call = canvas.GetCircles()[0];
    EXPECT_NEAR(call.center.x, 5.0, EPS);
    EXPECT_NEAR(call.center.y, 6.0, EPS);
    EXPECT_NEAR(call.radius, 7.5, EPS);
    EXPECT_EQ(call.lineColor, 0xaabbccu);
    EXPECT_EQ(call.fillColor, 0x010203u);
}

TEST(ShapeDrawTests, TriangleDrawsOnePolygonPrimitive)
{
    CTriangle triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}, 0x123456, 0x654321);
    CTestCanvas canvas;

    triangle.Draw(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 1u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Polygon);
    EXPECT_EQ(canvas.GetEvents()[0].index, 0u);

    ASSERT_EQ(canvas.GetPolygons().size(), 1u);
    EXPECT_EQ(canvas.GetLines().size(), 0u);
    EXPECT_EQ(canvas.GetCircles().size(), 0u);

    const auto& call = canvas.GetPolygons()[0];
    ASSERT_EQ(call.points.size(), 3u);
    EXPECT_NEAR(call.points[0].x, 0.0, EPS);
    EXPECT_NEAR(call.points[0].y, 0.0, EPS);
    EXPECT_NEAR(call.points[1].x, 4.0, EPS);
    EXPECT_NEAR(call.points[1].y, 0.0, EPS);
    EXPECT_NEAR(call.points[2].x, 0.0, EPS);
    EXPECT_NEAR(call.points[2].y, 3.0, EPS);
    EXPECT_EQ(call.lineColor, 0x123456u);
    EXPECT_EQ(call.fillColor, 0x654321u);
}

TEST(ShapeDrawTests, RectangleDrawsPolygonWithExpectedVertexOrder)
{
    CRectangle rectangle({10.0, 20.0}, 30.0, 40.0, 0xff0000, 0x00ff00);
    CTestCanvas canvas;

    rectangle.Draw(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 1u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Polygon);
    EXPECT_EQ(canvas.GetEvents()[0].index, 0u);

    ASSERT_EQ(canvas.GetPolygons().size(), 1u);
    const auto& call = canvas.GetPolygons()[0];

    ASSERT_EQ(call.points.size(), 4u);
    EXPECT_NEAR(call.points[0].x, 10.0, EPS);
    EXPECT_NEAR(call.points[0].y, 20.0, EPS);
    EXPECT_NEAR(call.points[1].x, 40.0, EPS);
    EXPECT_NEAR(call.points[1].y, 20.0, EPS);
    EXPECT_NEAR(call.points[2].x, 40.0, EPS);
    EXPECT_NEAR(call.points[2].y, 60.0, EPS);
    EXPECT_NEAR(call.points[3].x, 10.0, EPS);
    EXPECT_NEAR(call.points[3].y, 60.0, EPS);

    EXPECT_EQ(call.lineColor, 0xff0000u);
    EXPECT_EQ(call.fillColor, 0x00ff00u);
}
