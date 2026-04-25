#include <gtest/gtest.h>

#include <memory>

#include "TestCanvas.h"
#include "app/ShapeManager.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"

TEST(ShapeManagerDrawOrderTests, DrawAllKeepsInputOrder)
{
    CShapeManager manager;

    manager.AddShape(std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{1.0, 1.0}, 0x111111));
    manager.AddShape(std::make_shared<CCircle>(CPoint{5.0, 5.0}, 2.0, 0x222222, 0x333333));
    manager.AddShape(std::make_shared<CRectangle>(CPoint{10.0, 10.0}, 4.0, 3.0, 0x444444, 0x555555));

    CTestCanvas canvas;
    manager.DrawAll(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 3u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Line);
    EXPECT_EQ(canvas.GetEvents()[1].type, EPrimitiveType::Circle);
    EXPECT_EQ(canvas.GetEvents()[2].type, EPrimitiveType::Polygon);

    EXPECT_EQ(canvas.GetEvents()[0].index, 0u);
    EXPECT_EQ(canvas.GetEvents()[1].index, 0u);
    EXPECT_EQ(canvas.GetEvents()[2].index, 0u);

    ASSERT_EQ(canvas.GetLines().size(), 1u);
    ASSERT_EQ(canvas.GetCircles().size(), 1u);
    ASSERT_EQ(canvas.GetPolygons().size(), 1u);
}

TEST(ShapeManagerDrawOrderTests, DrawAllSkipsNullShapeBecauseItIsNotAdded)
{
    CShapeManager manager;
    manager.AddShape(nullptr);
    manager.AddShape(std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{2.0, 0.0}, 0x111111));

    CTestCanvas canvas;
    manager.DrawAll(canvas);

    ASSERT_EQ(canvas.GetEvents().size(), 1u);
    EXPECT_EQ(canvas.GetEvents()[0].type, EPrimitiveType::Line);
}
