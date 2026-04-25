#include "CTriangle.h"
#include "../canvas/ICanvas.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

CTriangle::CTriangle(
    CPoint vertex1,
    CPoint vertex2,
    CPoint vertex3,
    uint32_t outlineColor,
    uint32_t fillColor
)
    : m_vertex1(vertex1)
    , m_vertex2(vertex2)
    , m_vertex3(vertex3)
    , m_outlineColor(outlineColor)
    , m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
    double a = GetSideLength(m_vertex1, m_vertex2);
    double b = GetSideLength(m_vertex2, m_vertex3);
    double c = GetSideLength(m_vertex3, m_vertex1);

    double p = (a + b + c) / 2.0;

    double value = p * (p - a) * (p - b) * (p - c);
    return std::sqrt(std::max(0.0, value));
}

double CTriangle::GetPerimeter() const
{
    double a = GetSideLength(m_vertex1, m_vertex2);
    double b = GetSideLength(m_vertex2, m_vertex3);
    double c = GetSideLength(m_vertex3, m_vertex1);

    return a + b + c;
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const { return m_vertex1; }
CPoint CTriangle::GetVertex2() const { return m_vertex2; }
CPoint CTriangle::GetVertex3() const { return m_vertex3; }

double CTriangle::GetSideLength(CPoint a, CPoint b) const
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string CTriangle::ToString() const
{
    std::ostringstream ss;

    ss << "Triangle:\n";
    ss << "  Vertex1: (" << m_vertex1.x << ", " << m_vertex1.y << ")\n";
    ss << "  Vertex2: (" << m_vertex2.x << ", " << m_vertex2.y << ")\n";
    ss << "  Vertex3: (" << m_vertex3.x << ", " << m_vertex3.y << ")\n";

    ss << "  Area: " << GetArea() << "\n";
    ss << "  Perimeter: " << GetPerimeter() << "\n";

    ss << "  Outline color: "
       << std::hex << std::setw(6) << std::setfill('0')
       << m_outlineColor << "\n";

    ss << "  Fill color: "
       << std::hex << std::setw(6) << std::setfill('0')
       << m_fillColor << "\n";

    return ss.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
    canvas.DrawPolygon({ m_vertex1, m_vertex2, m_vertex3 }, m_outlineColor, m_fillColor);
}