#pragma once

#include "../shapes/IShape.h"
#include <memory>
#include <string>

class CShapeFactory
{
public:
    std::shared_ptr<IShape> CreateShape(const std::string& description) const;

private:
    std::shared_ptr<IShape> CreateLine(std::istringstream& iss) const;
    std::shared_ptr<IShape> CreateRectangle(std::istringstream& iss) const;
    std::shared_ptr<IShape> CreateTriangle(std::istringstream& iss) const;
    std::shared_ptr<IShape> CreateCircle(std::istringstream& iss) const;

    static uint32_t ParseColor(const std::string& str) ;
};


