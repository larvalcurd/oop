#pragma once

#include <exception>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "CShapeFactory.h"
#include "ShapeManager.h"

inline int RunApp(
    std::istream& input,
    std::ostream& output,
    std::ostream& errors,
    CShapeManager& manager
)
{
    CShapeFactory factory;

    std::string line;
    while (std::getline(input, line))
    {
        try
        {
            manager.AddShape(factory.CreateShape(line));
        }
        catch (const std::exception& e)
        {
            errors << e.what() << std::endl;
        }
    }

    const auto maxArea = manager.FindMaxAreaShape();
    const auto minPerimeter = manager.FindMinPerimeterShape();

    if (maxArea)
    {
        output << "Max area:\n" << maxArea->ToString() << std::endl;
    }

    if (minPerimeter)
    {
        output << "Min perimeter:\n" << minPerimeter->ToString() << std::endl;
    }

    return 0;
}
