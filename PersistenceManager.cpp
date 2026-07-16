#include "PersistenceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "DerivedFurniture.h"

bool PersistenceManager::saveAllData(const std::string& furnitureFile, const std::string& accountFile, 
                                    const FurnitureManager& fManager, const AccountManager& aManager) {
    // 1. Lưu Furniture
    std::ofstream fOut(furnitureFile);
    if (!fOut.is_open()) return false;
    
    // Duyệt map inventory của FurnitureManager
    for (const auto& [type, list] : fManager.getInventory()) {
        for (const auto& f : list) {
            fOut << f->getFurnitureID() << "," << f->getName() << "," << f->getPrice() << "," 
                 << f->getQuantity() << "," << (int)type << "," << f->getWidth() << "," 
                 << f->getHeight() << "," << f->getDepth() << "," << f->getBaseColor() << "\n";
        }
    }
    fOut.close();

    // 2. Lưu Accounts
    std::ofstream aOut(accountFile);
    if (!aOut.is_open()) return false;
    
    for (const auto& [username, acc] : aManager.getAccounts()) {
        aOut << acc.username << "," << acc.password << "," << (int)acc.role << "\n";
    }
    aOut.close();

    std::cout << ">>> Data has been successful saved! <<<\n";
    return true;
}

bool PersistenceManager::loadAllData(const std::string& furnitureFile, const std::string& accountFile, 
                                    FurnitureManager& fManager, AccountManager& aManager) {
    // 1. Load Accounts (giữ nguyên logic cũ của bạn)
    std::ifstream aIn(accountFile);
    std::string line;
    if (aIn.is_open()) {
        while (std::getline(aIn, line)) {
            std::stringstream ss(line);
            std::string u, p, rStr;
            if (std::getline(ss, u, ',') && std::getline(ss, p, ',') && std::getline(ss, rStr)) {
                aManager.addAccount(u, p, (UserRole)std::stoi(rStr));
            }
        }
        aIn.close();
    }

    // 2. Load Furniture - Đây là phần quan trọng
    std::ifstream fIn(furnitureFile);
    if (fIn.is_open()) {
        while (std::getline(fIn, line)) {
            std::stringstream ss(line);
            std::string id, name, priceStr, qtyStr, typeStr, wStr, hStr, dStr, color;
            
            // Đọc đúng thứ tự đã lưu: ID,Name,Price,Quantity,Type,Width,Height,Depth,Color
            if (std::getline(ss, id, ',') && std::getline(ss, name, ',') && 
                std::getline(ss, priceStr, ',') && std::getline(ss, qtyStr, ',') &&
                std::getline(ss, typeStr, ',') && std::getline(ss, wStr, ',') &&
                std::getline(ss, hStr, ',') && std::getline(ss, dStr, ',') && std::getline(ss, color)) {
                
                int type = std::stoi(typeStr);
                double price = std::stod(priceStr);
                int qty = std::stoi(qtyStr);
                double w = std::stod(wStr);
                double h = std::stod(hStr);
                double d = std::stod(dStr);

                // Tạo đối tượng dựa trên type
                std::shared_ptr<FurnitureBase> f;
                if (type == 0) f = std::make_shared<WoodFurniture>(id, name, w, h, d, price, qty, color);
                else if (type == 1) f = std::make_shared<MetalFurniture>(id, name, w, h, d, price, qty, color);
                else f = std::make_shared<AluminumFurniture>(id, name, w, h, d, price, qty, color);
                
                fManager.addFurniture(f);
            }
        }
        fIn.close();
        std::cout << ">>> Du lieu da duoc tai len thanh cong! <<<\n";
    }
    return true;
}