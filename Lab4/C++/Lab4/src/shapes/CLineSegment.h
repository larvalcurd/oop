#pragma once

#include "IShape.h"
#include "CPoint.h"

#include <string>

class CLineSegment : public IShape
{
public:
    CLineSegment(CPoint start, CPoint end, uint32_t outlineColor);

    double GetArea() const override;
    double GetPerimeter() const override;

    uint32_t GetOutlineColor() const override;

    std::string ToString() const override;
    void Draw(ICanvas &canvas) const override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

private:
    CPoint m_startPoint;
    CPoint m_endPoint;
    uint32_t m_outlineColor;
};