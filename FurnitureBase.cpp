#include "FurnitureBase.h"
#include "Validation.h"

FurnitureBase::FurnitureBase(std::string id, MaterialType type, double w, double h, double d, std::string color)
    : furnitureID(id), materialType(type), width(w), height(h), depth(d), baseColor(color) {
    if (w <= 0) throw InvalidDimensionException("width");
    if (h <= 0) throw InvalidDimensionException("height");
    if (d <= 0) throw InvalidDimensionException("depth");
}

std::string FurnitureBase::getFurnitureID() const { return furnitureID; }
MaterialType FurnitureBase::getMaterialType() const { return materialType; }
double FurnitureBase::getWidth() const { return width; }
double FurnitureBase::getHeight() const { return height; }
double FurnitureBase::getDepth() const { return depth; }
std::string FurnitureBase::getBaseColor() const { return baseColor; }

void FurnitureBase::setDimensions(double w, double h, double d) {
    if (w <= 0) throw InvalidDimensionException("width");
    if (h <= 0) throw InvalidDimensionException("height");
    if (d <= 0) throw InvalidDimensionException("depth");
    width = w; 
    height = h; 
    depth = d;
}

void FurnitureBase::setBaseColor(const std::string& color) {
    baseColor = color;
}
