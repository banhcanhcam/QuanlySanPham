#ifndef FURNITURE_BASE_H
#define FURNITURE_BASE_H

#include <string>

enum class MaterialType { WOOD, METAL, ALUMINUM };

class FurnitureBase {
protected:
    std::string furnitureID;
    MaterialType materialType;
    double width;
    double height;
    double depth;
    std::string baseColor;

public:
    FurnitureBase(std::string id, MaterialType type, double w, double h, double d, std::string color);
    virtual ~FurnitureBase() = default;

    // Hàm thuần ảo (Pure virtual function) yêu cầu các class con phải ghi đè
    virtual double getMaterialRate() const = 0;

    // Getters
    std::string getFurnitureID() const;
    MaterialType getMaterialType() const;
    double getWidth() const;
    double getHeight() const;
    double getDepth() const;
    std::string getBaseColor() const;

    // Setters
    void setDimensions(double w, double h, double d);
    void setBaseColor(const std::string& color);
};

#endif // FURNITURE_BASE_H