#include "FurnitureManager.h"
#include "Validation.h"
#include <iostream>

void FurnitureManager::addFurniture(std::shared_ptr<FurnitureBase> furniture) {
    // Kiem tra trung lap ID truoc khi them
    if (searchById(furniture->getFurnitureID()) != nullptr) {
        throw DuplicateIdException(furniture->getFurnitureID());
    }
    
    // Them vao map theo dung loai vat lieu
    inventory[furniture->getMaterialType()].push_back(furniture);
}

std::shared_ptr<FurnitureBase> FurnitureManager::searchById(const std::string& id) const {
    for (const auto& pair : inventory) {
        for (const auto& item : pair.second) {
            if (item->getFurnitureID() == id) {
                return item;
            }
        }
    }
    return nullptr; // Khong tim thay
}

void FurnitureManager::displayAll() const {
    for (const auto& pair : inventory) {
        for (const auto& item : pair.second) {
            std::cout << "ID: " << item->getFurnitureID() 
                      << " | Color: " << item->getBaseColor() 
                      << " | WxHxD: " << item->getWidth() << "x" 
                      << item->getHeight() << "x" << item->getDepth() << "\n";
        }
    }
}

// Logic File I/O se duoc viet chi tiet trong Phan 3 (Phan tich Du lieu & I/O)
bool FurnitureManager::loadFromFile(const std::string& filename) { return true; }
bool FurnitureManager::saveToFile(const std::string& filename) const { return true; }
//xóa sản phẩm theo ID.
bool FurnitureManager::deleteProduct(const std::string& id) {
    for (auto& pair : inventory) {
        auto& vec = pair.second;
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if ((*it)->getFurnitureID() == id) {
                vec.erase(it);
                return true;
            }
        }
    }
    return false;
}