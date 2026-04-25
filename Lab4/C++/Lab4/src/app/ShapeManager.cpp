#include "ShapeManager.h"

#include <algorithm>

void CShapeManager::AddShape(ShapePtr shape)
{
    if (!shape)
    {
        return;
    }
    m_shapes.push_back(std::move(shape));
}

CShapeManager::ShapePtr CShapeManager::FindMaxAreaShape() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    return *std::ranges::max_element(m_shapes,
        [](const ShapePtr& a, const ShapePtr& b)
        {
            return a->GetArea() < b->GetArea();
        });
}

CShapeManager::ShapePtr CShapeManager::FindMinPerimeterShape() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    return *std::ranges::min_element(m_shapes,
        [](const ShapePtr& a, const ShapePtr& b)
        {
            return a->GetPerimeter() < b->GetPerimeter();
        });
}

const std::vector<CShapeManager::ShapePtr>& CShapeManager::GetShapes() const
{
    return m_shapes;
}

size_t CShapeManager::GetCount() const
{
    return m_shapes.size();
}

bool CShapeManager::IsEmpty() const
{
    return m_shapes.empty();
}

void CShapeManager::DrawAll(ICanvas& canvas) const
{
    for (const auto& shape : m_shapes)
    {
        if (shape)
        {
            shape->Draw(canvas);
        }
    }
}