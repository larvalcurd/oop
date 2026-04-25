#include "CShapeFactory.h"
#include <sstream>
#include <cmath>
#include <initializer_list>

#include "../shapes/CLineSegment.h"
#include "../shapes/CRectangle.h"
#include "../shapes/CTriangle.h"
#include "../shapes/CCircle.h"

template <typename Func>
std::shared_ptr<IShape> Wrap(const std::string& description, Func func, const std::string& type)
{
    try
    {
        return func();
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("Invalid " + type + ": " + description + " | " + e.what());
    }
}

void EnsureFinite(const std::initializer_list<double>& values, const char* context)
{
    for (const double value : values)
    {
        if (!std::isfinite(value))
        {
            throw std::invalid_argument(std::string(context) + " contains non-finite values");
        }
    }
}

std::shared_ptr<IShape> CShapeFactory::CreateShape(const std::string &description) const
{
    std::istringstream iss(description);

    std::string type;
    if (!(iss >> type))
    {
        throw std::invalid_argument("Empty input");
    }

    if (type == "line")
    {
        return Wrap(description, [&]() { return CreateLine(iss); }, "line"); 
    }
    else if (type == "rectangle")
    {
        return Wrap(description, [&]() { return CreateRectangle(iss); }, "rectangle");
    }
    else if (type == "triangle")
    {
        return Wrap(description, [&]() { return CreateTriangle(iss); }, "triangle");
    }
    else if (type == "circle")
    {
        return Wrap(description, [&]() { return CreateCircle(iss); }, "circle");
    }

    throw std::invalid_argument("Unknown shape type: " + type);
}

std::shared_ptr<IShape> CShapeFactory::CreateLine(std::istringstream &iss) const
{
    double x1, y1, x2, y2;
    std::string outlineColorString;

    if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorString) || (iss >> std::ws && !iss.eof()))
    {
        throw std::invalid_argument("Invalid line parameters");
    }
    EnsureFinite({ x1, y1, x2, y2 }, "Line");

    if (std::abs(x1 - x2) < 1e-9 && std::abs(y1 - y2) < 1e-9)
    {
        throw std::invalid_argument("Line cannot have zero length");
    }

    uint32_t outlineColor = ParseColor(outlineColorString);

    return std::make_shared<CLineSegment>(
        CPoint{x1, y1},
        CPoint{x2, y2},
        outlineColor
    );
}

std::shared_ptr<IShape> CShapeFactory::CreateRectangle(std::istringstream &iss) const
{
    double x, y, width, height;
    std::string outlineColorString, fillColorString;

    if (!(iss >> x >> y >> width >> height >> outlineColorString >> fillColorString))
    {
        throw std::invalid_argument("Invalid rectangle parameters");
    }
    EnsureFinite({ x, y, width, height }, "Rectangle");

    if (iss >> std::ws && !iss.eof())
    {
        throw std::invalid_argument("Too many parameters for rectangle");
    }

    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }

    uint32_t outlineColor = ParseColor(outlineColorString);
    uint32_t fillColor = ParseColor(fillColorString);

    return std::make_shared<CRectangle>(
        CPoint{x, y},
        width,
        height,
        outlineColor,
        fillColor
    );
}

std::shared_ptr<IShape> CShapeFactory::CreateTriangle(std::istringstream &iss) const
{
    double x1, y1, x2, y2, x3, y3;
    std::string outlineColorString, fillColorString;

    if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorString >> fillColorString))
    {
        throw std::invalid_argument("Invalid triangle parameters");
    }
    EnsureFinite({ x1, y1, x2, y2, x3, y3 }, "Triangle");

    if (iss >> std::ws && !iss.eof())
    {
        throw std::invalid_argument("Too many parameters for triangle");
    }

    double area = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if (std::abs(area) < 1e-9)
    {
        throw std::invalid_argument("Triangle points are collinear");
    }

    uint32_t outlineColor = ParseColor(outlineColorString);
    uint32_t fillColor = ParseColor(fillColorString);

    return std::make_shared<CTriangle>(
        CPoint{x1, y1},
        CPoint{x2, y2},
        CPoint{x3, y3},
        outlineColor,
        fillColor
    );
}

std::shared_ptr<IShape> CShapeFactory::CreateCircle(std::istringstream &iss) const
{
    double cx, cy, radius;
    std::string outlineColorString, fillColorString;

    if (!(iss >> cx >> cy >> radius >> outlineColorString >> fillColorString))
    {
        throw std::invalid_argument("Invalid circle parameters");
    }
    EnsureFinite({ cx, cy, radius }, "Circle");

    if (iss >> std::ws && !iss.eof())
    {
        throw std::invalid_argument("Too many parameters for circle");
    }

    if (radius <= 0)
    {
        throw std::invalid_argument("Radius must be positive");
    }

    uint32_t outlineColor = ParseColor(outlineColorString);
    uint32_t fillColor = ParseColor(fillColorString);

    return std::make_shared<CCircle>(
        CPoint{cx, cy},
        radius,
        outlineColor,
        fillColor
    );
}

uint32_t CShapeFactory::ParseColor(const std::string &str)
{
    if (str.length() != 6)
    {
        throw std::invalid_argument("Color must be 6 hex digits: " + str);
    }

    for (char c : str)
    {
        if (!std::isxdigit(static_cast<unsigned char>(c)))
        {
            throw std::invalid_argument("Invalid color: " + str);
        }
    }

    uint32_t color;
    std::istringstream iss(str);
    iss >> std::hex >> color;

    if (iss.fail() || (iss >> std::ws && !iss.eof()))
    {
        throw std::invalid_argument("Invalid color: " + str);
    }

    return color;
}
