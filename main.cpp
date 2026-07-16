#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include "AccountManager.h"
#include "Validation.h"
#include "DerivedFurniture.h"
#include "FurnitureManager.h"
#include "OrderManager.h"
#include "Product.h"
#include <cctype>

using namespace std;

// --- CÁC HÀM HỖ TRỢ NHẬP LIỆU ---
static int readNumber(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // KIỂM TRA: Nếu là số âm hoặc bằng 0 thì bắt nhập lại
            if (value < 0) {
                cout << "Error: Value must be greater than 0. Please try again.\n";
                continue;
			}
			return value;
		}
	}
}
static int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // KIỂM TRA: Nếu là số âm hoặc bằng 0 thì bắt nhập lại
            if (value < 0) {
                cout << "Error: Value must be greater than 0. Please try again.\n";
                continue;
			}
            else if (value > 2){ 
                cout << "Error: Value must be smaller than 3. Please try again.\n";
                continue; 
			}
            }
            return value;
        }
        cout << "Invalid! Please enter a valid integer number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

static double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // KIỂM TRA: Chặn kích thước âm hoặc bằng 0
            if (value <= 0) {
                cout << "Error: Dimension must be greater than 0. Please try again.\n";
                continue; 
            }
            return value;
        }
        cout << "Invalid! Please enter a valid decimal number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static string readLineAlpha(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        
        bool allLetters = true;
        // Kiểm tra từng ký tự trong chuỗi người dùng nhập
        for (char c : line) {
            // !isalpha(c) nghĩa là "không phải chữ"
            // !isspace(c) nghĩa là "không phải khoảng trắng"
            // Nếu không phải chữ và không phải khoảng trắng -> Báo lỗi
            if (!isalpha(c) && !isspace(c)) { 
                allLetters = false;
                break;
            }
        }
        
        // Nếu tất cả đều là chữ và chuỗi không bị rỗng thì trả về
        if (allLetters && !line.empty()) {
            return line;
        }
        cout << "Invalid input, please enter letters only (no numbers).\n";
    }
}

// --- MENU CŨ CỦA BẠN (Đã tích hợp) ---
static void showAdminMenu() {
    cout << "\n================= ADMIN MENU =================\n"
            "1. Add new Furniture Item\n"
            "2. Search Furniture by ID\n"
            "3. Display all Furniture Items\n"
            "4. Create Manufacturing Order\n"
            "5. Track Orders by Status\n"
            "8. Delete a Furniture Item\n"
            "9. Delete a Manufacturing Order\n"
            "0. Logout\n"
            "==============================================\n";
}

int main() {
    AccountManager authSystem;
    UserAccount* loggedInUser = nullptr;
    FurnitureManager fManager;
    OrderManager oManager;

    // --- CỔNG ĐĂNG NHẬP ---
    while (loggedInUser == nullptr) {
        cout << "\n===== WELCOME TO FURNITURE SYSTEM =====\n";
        cout << "1. Login\n2. Register Customer\n3. Register Admin\n0. Exit\n";
        int choice = readInt("Choose: ");
        if (choice == 0) return 0;

        if (choice == 1) {
            string u, p;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            loggedInUser = authSystem.login(u, p);
            if (!loggedInUser) cout << "Login failed!\n";
        } else if (choice == 2 || choice == 3) {
            string u, p;
            cout << "New Username: "; cin >> u;
            cout << "New Password: "; cin >> p;
            UserRole r = (choice == 2) ? UserRole::CUSTOMER : UserRole::ADMIN;
            authSystem.registerAccount(u, p, r);
        }
    }

    // --- SAU KHI ĐĂNG NHẬP ---
    
    if (loggedInUser->role == UserRole::ADMIN) {
        while (true) {
            showAdminMenu();
            int choice = readInt("Option: ");
            if (choice == 0) break;

            switch (choice) {
                case 1: {
                    string id = readLine("ID: ");
                    string name = readValidName("Enter Product Name: ");
                    int m = readInt("Material (0:Wood, 1:Metal, 2:Aluminum): ");
                    double w = readDouble("Width(cm): ");
                    double h = readDouble("Height(cm): ");
                    double d = readDouble("Depth(cm): "); 
                    string c = readLineAlpha("Color: ");
                    double price = readDouble("Price($): ");
                    int quantity = readNumber ("Quantity: ");
                    shared_ptr<FurnitureBase> f;
                    if (m == 0) f = make_shared<WoodFurniture>(id, w, h, d, c);
                    else f = make_shared<MetalFurniture>(id, w, h, d, c);
                    fManager.addFurniture(f);
                    cout << "\n>>> Success: Added new furniture item (Name: " << name << ", "<< "ID: "<<  id <<") successfully! <<<\n";
                    break;
                }
                case 2: {
                    auto f = fManager.searchById(readLineAlpha("ID: "));
                    if (f) cout << "Found item.\n";
                    break;
                }
                case 3: fManager.displayAll(); break;
                // Gọi với 7 tham số: OID, FID, Carpenter, Date, Days, fManager, username
                case 4: 
                    oManager.createOrder(readLineAlpha("OID: "), readLineAlpha("FID: "), 
                                         readLineAlpha("Carpenter: "), readLineAlpha("Date: "), 
                                         readInt("Days: "), fManager, loggedInUser->username);
                    break;
                case 5: oManager.trackByStatus(OrderStatus::PENDING); break;
                case 6: {
                    cout << "--- UPDATE FURNITURE INFO ---\n";
                    // Gọi hàm cập nhật của fManager (Bạn có thể viết thêm hàm này nếu muốn)
                    cout << "Tính năng cập nhật đang được phát triển...\n";
                    break;
                }
                case 7: {
                    cout << "--- STATISTICS / SORT ---\n";
                    // Gọi hàm thống kê hoặc sắp xếp của fManager
                    cout << "Tính năng thống kê đang được phát triển...\n";
                    break;
                }
                case 8: fManager.deleteProduct(readLineAlpha("Delete FID: ")); break;
                case 9: oManager.deleteOrder(readLineAlpha("Delete OID: ")); break;
                default: cout << "Invalid!\n";
            }
        }
    } else {
        cout << "Customer menu is currently under development.\n";
    }

    return 0;
}