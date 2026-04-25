#include "CCanvas.h"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <stdexcept>

namespace
{
constexpr float OUTLINE_THICKNESS = 1.f;

uint8_t ExtractColorComponent(uint32_t color, unsigned shift)
{
    return static_cast<uint8_t>((color >> shift) & 0xffu);
}

sf::Color ToSfColor(uint32_t color)
{
    return sf::Color(
        ExtractColorComponent(color, 16),
        ExtractColorComponent(color, 8),
        ExtractColorComponent(color, 0)
    );
}
}

CCanvas::CCanvas(double width, double height)
    : m_width(width)
    , m_height(height)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{    
    if (!m_window)
    {
        throw std::logic_error("Canvas has no active render window");
    }

    sf::Vertex vertices[] = {
        sf::Vertex(
            sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)),
            ToSfColor(lineColor)
        ),
        sf::Vertex(
            sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)),
            ToSfColor(lineColor)
        )
    };

    m_window->draw(vertices, 2, sf::Lines);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor)
{
    if (!m_window)
    {
        throw std::logic_error("Canvas has no active render window");
    }

    sf::CircleShape shape(static_cast<float>(radius));
    shape.setPosition(
        static_cast<float>(center.x - radius),
        static_cast<float>(center.y - radius)
    );
    shape.setOutlineThickness(OUTLINE_THICKNESS);
    shape.setOutlineColor(ToSfColor(lineColor));
    shape.setFillColor(ToSfColor(fillColor));
    m_window->draw(shape);
}

void CCanvas::DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor, uint32_t fillColor)
{
    if (!m_window)
    {
        throw std::logic_error("Canvas has no active render window");
    }

    if (points.empty())
    {
        return;
    }

    sf::ConvexShape shape;
    shape.setPointCount(points.size());

    for (size_t i = 0; i < points.size(); ++i)
    {
        shape.setPoint(i, sf::Vector2f(
            static_cast<float>(points[i].x),
            static_cast<float>(points[i].y)
        ));
    }

    shape.setOutlineThickness(OUTLINE_THICKNESS);
    shape.setOutlineColor(ToSfColor(lineColor));
    shape.setFillColor(ToSfColor(fillColor));

    m_window->draw(shape);
}

void CCanvas::Run(const std::vector<std::shared_ptr<IShape>>& shapes)
{
    const unsigned width = static_cast<unsigned>(std::max(1.0, m_width));
    const unsigned height = static_cast<unsigned>(std::max(1.0, m_height));

    sf::RenderWindow window(sf::VideoMode(width, height), "Lab4");
    window.setVerticalSyncEnabled(true);

    m_window = &window;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (const auto& shape : shapes)
        {
            if (shape)
            {
                shape->Draw(*this);
            }
        }

        window.display();
    }

    m_window = nullptr;
}


double CCanvas::GetWidth() const
{
    return m_width;
}

double CCanvas::GetHeight() const
{
    return m_height;
}
