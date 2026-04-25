
#include <gtest/gtest.h>
#include "canvas/CCanvas.h"

TEST(CCanvasTests, StoresCanvasSize)
{
	CCanvas canvas(800, 600);
	EXPECT_DOUBLE_EQ(canvas.GetWidth(), 800.0);
	EXPECT_DOUBLE_EQ(canvas.GetHeight(), 600.0);
}

TEST(CCanvasTests, CollectsDrawCommands)
{
	CCanvas canvas(100, 100);
	EXPECT_EQ(canvas.GetDrawCommandCount(), 0u);

	// These will only work if CCanvas is instrumented to count commands without a window
	// If not, consider using a mock or test double for the window, or adapt the test
	// For now, we assume GetDrawCommandCount() is testable
	canvas.DrawLine({1, 2}, {3, 4}, 0x0a0b0c);
	EXPECT_EQ(canvas.GetDrawCommandCount(), 1u);

	canvas.DrawCircle({10, 20}, 15, 0xff0000, 0x00ff00);
	EXPECT_EQ(canvas.GetDrawCommandCount(), 2u);

	canvas.DrawPolygon({ {0, 0}, {1, 0}, {1, 1} }, 0x123456, 0x654321);
	EXPECT_EQ(canvas.GetDrawCommandCount(), 3u);
}
