#include "CRectangle.h"
#include "../canvas/ICanvas.h"

#include <vector>
#include <sstream>
#include <iomanip>

CRectangle::CRectangle(
        CPoint leftTop,
        double width,
        double height,
        uint32_t outlineColor,
        uint32_t fillColor
    )
        : m_leftTop(leftTop)
        , m_width(width)
        , m_height(height)
        , m_outlineColor(outlineColor)
        , m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return (m_width + m_height) * 2;
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

std::string CRectangle::ToString() const
{
    std::ostringstream oss;

    oss << "Rectangle:\n";
    oss << "  Left top: (" << m_leftTop.x << ", " << m_leftTop.y << ")\n";
    oss << "  Width: " << m_width << "\n";
    oss << "  Height: " << m_height << "\n";
    oss << "  Area: " << GetArea() << "\n";
    oss << "  Perimeter: " << GetPerimeter() << "\n";
    oss << "  Outline color: "
        << std::hex << std::setw(6) << std::setfill('0')
        << m_outlineColor << "\n";
    oss << "  Fill color: "
        << std::hex << std::setw(6) << std::setfill('0')
        << m_fillColor << "\n";

    return oss.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
    const CPoint p1{ m_leftTop.x, m_leftTop.y };
    const CPoint p2{ m_leftTop.x + m_width, m_leftTop.y };
    const CPoint p3{ m_leftTop.x + m_width, m_leftTop.y + m_height };
    const CPoint p4{ m_leftTop.x, m_leftTop.y + m_height };

    canvas.DrawPolygon({ p1, p2, p3, p4 }, m_outlineColor, m_fillColor);
}
