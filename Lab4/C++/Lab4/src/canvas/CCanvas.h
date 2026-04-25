#pragma once

#include "ICanvas.h"
#include "../shapes/IShape.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace sf
{
    class RenderWindow;
}

class CCanvas final : public ICanvas
{
public:
    CCanvas(double width, double height);

    void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
    void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor) override;
    void DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor, uint32_t fillColor) override;

    void Run(const std::vector<std::shared_ptr<IShape>>& shapes);

    [[nodiscard]] size_t GetDrawCommandCount() const;
    [[nodiscard]] double GetWidth() const;
    [[nodiscard]] double GetHeight() const;

private:
    // Efficient draw command counter for testing
    size_t m_drawCommandCount = 0;

    // struct SLineCommand
    // {
    //     CPoint from{};
    //     CPoint to{};
    //     uint32_t color = 0;
    // };

    // struct SCircleCommand
    // {
    //     CPoint center{};
    //     double radius = 0.0;
    //     uint32_t lineColor = 0;
    //     uint32_t fillColor = 0;
    // };

    // struct SPolygonCommand
    // {
    //     std::vector<CPoint> points;
    //     uint32_t lineColor = 0;
    //     uint32_t fillColor = 0;
    // };

    // struct SDrawCommand
    // {
    //     enum class EType
    //     {
    //         Line,
    //         Circle,
    //         Polygon
    //     };

    //     EType type = EType::Line;
    //     SLineCommand line{};
    //     SCircleCommand circle{};
    //     SPolygonCommand polygon{};
    // };

    double m_width = 0.0;
    double m_height = 0.0;
    // std::vector<SDrawCommand> m_commands;

    sf::RenderWindow* m_window = nullptr;
};
