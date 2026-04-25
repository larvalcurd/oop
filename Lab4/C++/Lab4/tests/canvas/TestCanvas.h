#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "../../src/canvas/ICanvas.h"

enum class EPrimitiveType
{
    Line,
    Circle,
    Polygon
};

struct SLineCall
{
    CPoint from;
    CPoint to;
    uint32_t color = 0;
};

struct SCircleCall
{
    CPoint center;
    double radius = 0.0;
    uint32_t lineColor = 0;
    uint32_t fillColor = 0;
};

struct SPolygonCall
{
    std::vector<CPoint> points;
    uint32_t lineColor = 0;
    uint32_t fillColor = 0;
};

struct SDrawEvent
{
    EPrimitiveType type;
    std::size_t index = 0;
};

class CTestCanvas final : public ICanvas
{
public:
    void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override
    {
        m_events.push_back({ EPrimitiveType::Line, m_lines.size() });
        m_lines.push_back({ from, to, lineColor });
    }

    void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor) override
    {
        m_events.push_back({ EPrimitiveType::Circle, m_circles.size() });
        m_circles.push_back({ center, radius, lineColor, fillColor });
    }

    void DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor, uint32_t fillColor) override
    {
        m_events.push_back({ EPrimitiveType::Polygon, m_polygons.size() });
        m_polygons.push_back({ points, lineColor, fillColor });
    }

    const std::vector<SLineCall>& GetLines() const { return m_lines; }
    const std::vector<SCircleCall>& GetCircles() const { return m_circles; }
    const std::vector<SPolygonCall>& GetPolygons() const { return m_polygons; }
    const std::vector<SDrawEvent>& GetEvents() const { return m_events; }

private:
    std::vector<SLineCall> m_lines;
    std::vector<SCircleCall> m_circles;
    std::vector<SPolygonCall> m_polygons;
    std::vector<SDrawEvent> m_events;
};
