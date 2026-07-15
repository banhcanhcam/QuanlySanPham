#ifndef DERIVED_FURNITURE_H
#define DERIVED_FURNITURE_H

#include "FurnitureBase.h"

class WoodFurniture : public FurnitureBase {
public:
    WoodFurniture(std::string id, double w, double h, double d, std::string color)
        : FurnitureBase(id, MaterialType::WOOD, w, h, d, color) {}
    
    // Ghi đè hàm để trả về giá của Gỗ (Ví dụ: 150.0 VND/cm2)
    double getMaterialRate() const override { return 150.0; } 
};

class MetalFurniture : public FurnitureBase {
public:
    MetalFurniture(std::string id, double w, double h, double d, std::string color)
        : FurnitureBase(id, MaterialType::METAL, w, h, d, color) {}
    
    // Ghi đè hàm để trả về giá của Kim loại
    double getMaterialRate() const override { return 250.0; } 
};

class PlasticFurniture : public FurnitureBase {
public:
    PlasticFurniture(std::string id, double w, double h, double d, std::string color)
        : FurnitureBase(id, MaterialType::ALUMINUM, w, h, d, color) {}
    
    // Ghi đè hàm để trả về giá của Nhựa
    double getMaterialRate() const override { return 50.0; } 
};

#endif // DERIVED_FURNITURE_H