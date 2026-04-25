#include "CLineSegment.h"
#include "../canvas/ICanvas.h"

#include <cmath>
#include <sstream>
#include <iomanip>

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t outlineColor)
    : m_startPoint(start),
    m_endPoint(end),
    m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    double dx = m_endPoint.x - m_startPoint.x;
    double dy = m_endPoint.y - m_startPoint.y;

    return std::sqrt(dx * dx + dy * dy);
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;

    oss << "LineSegment:\n";
    oss << "  Start: (" << m_startPoint.x << ", " << m_startPoint.y << ")\n";
    oss << "  End: (" << m_endPoint.x << ", " << m_endPoint.y << ")\n";
    oss << "  Area: " << GetArea() << "\n";
    oss << "  Perimeter: " << GetPerimeter() << "\n";
    oss << "  Outline color: "
        << std::hex << std::setw(6) << std::setfill('0')
        << m_outlineColor << "\n";

    return oss.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
