
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>
#include "app/AppRunner.h"
#include "app/ShapeManager.h"
#include "../canvas/TestCanvas.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"

namespace
{
constexpr double EPS = 1e-9;
}


TEST(ShapeManagerTests, IsEmptyAndCountOnNewManager)
{
	CShapeManager manager;
	EXPECT_TRUE(manager.IsEmpty());
	EXPECT_EQ(manager.GetCount(), 0u);
	EXPECT_EQ(manager.FindMaxAreaShape(), nullptr);
	EXPECT_EQ(manager.FindMinPerimeterShape(), nullptr);
}


TEST(ShapeManagerTests, AddShapeNullptrIsIgnored)
{
	CShapeManager manager;
	manager.AddShape(nullptr);
	EXPECT_TRUE(manager.IsEmpty());
	EXPECT_EQ(manager.GetCount(), 0u);
}

TEST(ShapeManagerTests, AddSameShapePointerMultipleTimes)
{
	CShapeManager manager;
	auto rect = std::make_shared<CRectangle>(CPoint{0,0}, 1, 1, 0x123456, 0x654321);
	manager.AddShape(rect);
	manager.AddShape(rect);
	EXPECT_EQ(manager.GetCount(), 2u);
	EXPECT_EQ(manager.GetShapes()[0], rect);
	EXPECT_EQ(manager.GetShapes()[1], rect);
}

TEST(ShapeManagerTests, DrawAllWithNullptrShape)
{
	CShapeManager manager;
	auto rect = std::make_shared<CRectangle>(CPoint{0,0}, 1, 1, 0x123456, 0x654321);
	manager.AddShape(nullptr);
	manager.AddShape(rect);
	CTestCanvas canvas;
	manager.DrawAll(canvas);
	ASSERT_EQ(canvas.GetEvents().size(), 1u);
}

TEST(ShapeManagerTests, GetShapesReturnsConstReference)
{
	CShapeManager manager;
	auto rect = std::make_shared<CRectangle>(CPoint{0,0}, 1, 1, 0x123456, 0x654321);
	manager.AddShape(rect);
	const auto& shapes = manager.GetShapes();
	EXPECT_EQ(shapes.size(), 1u);
	// Compilation test: shapes.push_back(nullptr); // should not compile
}


TEST(ShapeManagerTests, GetShapesPreservesInsertionOrder)
{
	CShapeManager manager;
	auto line = std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{3.0, 4.0}, 0xff0000);
	auto rectangle = std::make_shared<CRectangle>(CPoint{0.0, 0.0}, 10.0, 20.0, 0x000000, 0xffffff);
	manager.AddShape(line);
	manager.AddShape(rectangle);
	const auto& shapes = manager.GetShapes();
	ASSERT_EQ(shapes.size(), 2u);
	EXPECT_EQ(shapes[0], line);
	EXPECT_EQ(shapes[1], rectangle);
	EXPECT_FALSE(manager.IsEmpty());
	EXPECT_EQ(manager.GetCount(), 2u);
}


TEST(ShapeManagerTests, FindsShapeWithMaximumArea)
{
	CShapeManager manager;
	manager.AddShape(std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{3.0, 4.0}, 0xff0000));
	manager.AddShape(std::make_shared<CRectangle>(CPoint{0.0, 0.0}, 10.0, 20.0, 0x000000, 0xffffff));
	auto maxArea = manager.FindMaxAreaShape();
	ASSERT_NE(maxArea, nullptr);
	EXPECT_NEAR(maxArea->GetArea(), 200.0, EPS);
}


TEST(ShapeManagerTests, FindsShapeWithMinimumPerimeter)
{
	CShapeManager manager;
	manager.AddShape(std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{1.0, 0.0}, 0xff0000));
	manager.AddShape(std::make_shared<CRectangle>(CPoint{0.0, 0.0}, 10.0, 20.0, 0x000000, 0xffffff));
	auto minPerimeter = manager.FindMinPerimeterShape();
	ASSERT_NE(minPerimeter, nullptr);
	EXPECT_NEAR(minPerimeter->GetPerimeter(), 1.0, EPS);
}


TEST(ShapeManagerTests, TieCaseReturnsFirstForMaxArea)
{
	CShapeManager manager;
	auto rectangle1 = std::make_shared<CRectangle>(CPoint{0.0, 0.0}, 10.0, 10.0, 0x111111, 0x222222);
	auto rectangle2 = std::make_shared<CRectangle>(CPoint{1.0, 1.0}, 10.0, 10.0, 0x333333, 0x444444);
	manager.AddShape(rectangle1);
	manager.AddShape(rectangle2);
	EXPECT_EQ(manager.FindMaxAreaShape(), rectangle1);
}


TEST(ShapeManagerTests, TieCaseReturnsFirstForMinPerimeter)
{
	CShapeManager manager;
	auto line1 = std::make_shared<CLineSegment>(CPoint{0.0, 0.0}, CPoint{1.0, 0.0}, 0x111111);
	auto line2 = std::make_shared<CLineSegment>(CPoint{2.0, 0.0}, CPoint{3.0, 0.0}, 0x222222);
	manager.AddShape(line1);
	manager.AddShape(line2);
	EXPECT_EQ(manager.FindMinPerimeterShape(), line1);
}


TEST(ShapeManagerTests, DrawAllOnEmptyManagerProducesNoEvents)
{
	CShapeManager manager;
	CTestCanvas canvas;
	manager.DrawAll(canvas);
	EXPECT_TRUE(canvas.GetEvents().empty());
}


TEST(ShapeManagerTests, DrawAllDrawsAllShapesInOrder)
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
}


TEST(AppIntegrationTests, ReadsUntilEOFAndPrintsMaxAreaAndMinPerimeter)
{
	std::istringstream input(
		"line 0 0 3 4 ff0000\n"
		"rectangle 0 0 10 20 ff0000 00ff00\n"
		"circle 0 0 3 ff00ff 0000ff\n"
	);
	std::ostringstream output;
	std::ostringstream errors;
	CTestCanvas canvas;
	const int code = RunApp(input, output, errors, canvas);
	EXPECT_EQ(code, 0);
	EXPECT_TRUE(errors.str().empty());
	const std::string text = output.str();
	EXPECT_NE(text.find("Max area:"), std::string::npos);
	EXPECT_NE(text.find("Rectangle:"), std::string::npos);
	EXPECT_NE(text.find("Min perimeter:"), std::string::npos);
	EXPECT_NE(text.find("LineSegment:"), std::string::npos);
	EXPECT_EQ(canvas.GetEvents().size(), 3u);
}


TEST(AppIntegrationTests, ContinuesAfterInvalidInputLineAndStillComputesResults)
{
	std::istringstream input(
		"line 0 0 3 4 ff0000\n"
		"triangle 0 0 1 1 2 2 ff0000 00ff00\n"
		"rectangle 0 0 2 3 000000 ffffff\n"
	);
	std::ostringstream output;
	std::ostringstream errors;
	CTestCanvas canvas;
	const int code = RunApp(input, output, errors, canvas);
	EXPECT_EQ(code, 0);
	EXPECT_FALSE(errors.str().empty());
	const std::string text = output.str();
	EXPECT_NE(text.find("Max area:"), std::string::npos);
	EXPECT_NE(text.find("Rectangle:"), std::string::npos);
	EXPECT_NE(text.find("Min perimeter:"), std::string::npos);
	EXPECT_NE(text.find("LineSegment:"), std::string::npos);
	EXPECT_EQ(canvas.GetEvents().size(), 2u);
}


TEST(AppIntegrationTests, EmptyInputProducesNoMaxMinOutput)
{
	std::istringstream input("");
	std::ostringstream output;
	std::ostringstream errors;
	CTestCanvas canvas;
	const int code = RunApp(input, output, errors, canvas);
	EXPECT_EQ(code, 0);
	EXPECT_TRUE(errors.str().empty());
	EXPECT_TRUE(output.str().empty());
	EXPECT_TRUE(canvas.GetEvents().empty());
}
