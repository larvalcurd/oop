#include <iostream>

#include "app/AppRunner.h"
#include "../src/app/ShapeManager.h"
#include "../src/canvas/CCanvas.h"

int main()
{
    CShapeManager manager;
    CCanvas canvas(800, 600);

    const int exitCode = RunApp(std::cin, std::cout, std::cerr, manager);

    canvas.Run(manager.GetShapes());

    return exitCode;
}