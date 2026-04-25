#pragma once

#include <memory>
#include <vector>

#include "../shapes/IShape.h"
#include "../canvas/ICanvas.h"

class  CShapeManager
{
public:
    using ShapePtr = std::shared_ptr<IShape>;

    void AddShape(ShapePtr shape);

    ShapePtr FindMaxAreaShape() const;
    ShapePtr FindMinPerimeterShape() const;

    void DrawAll(ICanvas& canvas) const;

    const std::vector<ShapePtr>& GetShapes() const;

    size_t GetCount() const;
    bool IsEmpty() const;

private:
    std::vector<ShapePtr> m_shapes;
};
