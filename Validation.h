#ifndef VALIDATION_H
#define VALIDATION_H

#include <exception>
#include <string>

// Lỗi khi kích thước <= 0
class InvalidDimensionException : public std::exception {
    std::string msg;
public:
    InvalidDimensionException(const std::string& field) {
        msg = "Invalid dimension: " + field + " must be > 0";
    }
    const char* what() const noexcept override { 
        return msg.c_str(); 
    }
};

// Lỗi khi ID sản phẩm bị trùng
class DuplicateIdException : public std::exception {
    std::string msg;
public:
    DuplicateIdException(const std::string& id) {
        msg = "Duplicate ID: Furniture " + id + " already exists.";
    }
    const char* what() const noexcept override { 
        return msg.c_str(); 
    }
};

// Lỗi khi không nhập tên thợ mộc
class MissingCarpenterException : public std::exception {
public:
    const char* what() const noexcept override { 
        return "Carpenter name cannot be empty."; 
    }
};

#endif // VALIDATION_H