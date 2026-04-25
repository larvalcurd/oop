#include "CCircle.h"
#include "../canvas/ICanvas.h"

#include <sstream>
#include <iomanip>
#include <numbers>

CCircle::CCircle(
        CPoint center,
        double radius,
        uint32_t outlineColor,
        uint32_t fillColor
    )
        : m_center(center)
        , m_radius(radius)
        , m_outlineColor(outlineColor)
        , m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
    return std::numbers::pi * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * std::numbers::pi * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;

    oss << "Circle:\n";
    oss << "  Center: (" << m_center.x << ", " << m_center.y << ")\n";
    oss << "  Radius: " << m_radius << "\n";
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

void CCircle::Draw(ICanvas& canvas) const
{
    canvas.DrawCircle(m_center, m_radius, m_outlineColor, m_fillColor);
}