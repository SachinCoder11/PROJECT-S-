#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Shop {
private:
    int prdCode;          // Product code
    float price;          // Product price
    float discount;       // Discount on the product
    string prdName;       // Product name

public:
    void menu();
    void adminLogin();
    void administrator();
    void addProduct();
    void editProduct();
    void removeProduct();
    void listProducts();
    void generateReceipt();
    void saveBillToFile(const string& billDetails);
    void displayPreviousBills();
};

string getCurrentDateTime() {
    // Get the current date and time in a readable format
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " +
           to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
}

void Shop::adminLogin() {
    string email, password;
    cout << "\n\tADMIN LOGIN\n";
    cout << "\n\tEmail: ";
    cin >> email;
    cout << "\tPassword: ";
    cin >> password;

    // Simple admin authentication
    if (email == "shopkeeper@gmail.com" && password == "1234") {
        cout << "\n\tLogin successful! Welcome back.\n";
        administrator();
    } else {
        cout << "\n\tInvalid credentials. Please try again.\n";
        adminLogin(); // Retry login
    }
}

void Shop::menu() {
    int choice;
    cout << "\n\tSupermarket Main Menu\n";
    cout << "\n\t1) Administrator\n";
    cout << "\t2) Buyer\n";
    cout << "\t3) View Previous Bills\n";
    cout << "\t4) Exit\n";
    cout << "\n\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: adminLogin(); break;           // Go to admin login
        case 2: generateReceipt(); break;      // Generate a receipt for the buyer
        case 3: displayPreviousBills(); break; // Show previously saved bills
        case 4: exit(0);                      // Exit the application
        default:
            cout << "\n\tInvalid choice. Please select a valid option.\n";
            menu(); // Re-show menu if invalid choice
    }
}

void Shop::administrator() {
    int choice;
    cout << "\n\tAdministrator Menu\n";
    cout << "\n\t1) Add Product\n";
    cout << "\t2) Edit Product\n";
    cout << "\t3) Delete Product\n";
    cout << "\t4) Back to Main Menu\n";
    cout << "\n\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: addProduct(); break;           // Add a new product
        case 2: editProduct(); break;          // Edit an existing product
        case 3: removeProduct(); break;        // Remove a product
        case 4: menu(); break;                 // Return to main menu
        default:
            cout << "\n\tInvalid choice. Please try again.\n";
            administrator(); // Re-show admin menu if invalid choice
    }
}

void Shop::addProduct() {
    fstream data;
    int code;
    float price, discount;
    string name;

    cout << "\n\tAdd New Product\n";
    cout << "\n\tProduct code: ";
    cin >> code;
    cout << "\n\tProduct name: ";
    cin >> name;
    cout << "\n\tPrice: ";
    cin >> price;
    cout << "\n\tDiscount: ";
    cin >> discount;

    // Append new product details to the database file
    data.open("database.txt", ios::app | ios::out);
    if (!data) {
        cout << "\n\tError opening database file. Please check the file path.\n";
    } else {
        data << code << " " << name << " " << price << " " << discount << "\n";
        data.close();
        cout << "\n\tProduct added successfully!\n";
    }

    administrator(); // Return to admin menu after adding product
}

void Shop::editProduct() {
    fstream data, tempData;
    int code, newCode;
    float newPrice, newDiscount;
    string newName;
    bool found = false;

    cout << "\n\tEdit Product\n";
    cout << "\n\tEnter the product code to edit: ";
    cin >> code;

    // Open database file to read existing products
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\tError opening database file.\n";
        administrator();
        return;
    }

    // Create a temporary file to store updated product list
    tempData.open("database_temp.txt", ios::app | ios::out);
    while (data >> prdCode >> prdName >> price >> discount) {
        if (prdCode == code) {
            cout << "\n\tEnter new code: ";
            cin >> newCode;
            cout << "\tNew name: ";
            cin >> newName;
            cout << "\tNew price: ";
            cin >> newPrice;
            cout << "\tNew discount: ";
            cin >> newDiscount;
            tempData << newCode << " " << newName << " " << newPrice << " " << newDiscount << "\n";
            found = true;
        } else {
            tempData << prdCode << " " << prdName << " " << price << " " << discount << "\n";
        }
    }
    data.close();
    tempData.close();

    if (found) {
        remove("database.txt");
        rename("database_temp.txt", "database.txt");
        cout << "\n\tProduct updated successfully!\n";
    } else {
        cout << "\n\tProduct with the given code not found.\n";
        remove("database_temp.txt");
    }

    administrator(); // Return to admin menu after editing product
}

void Shop::removeProduct() {
    fstream data, tempData;
    int code;
    bool found = false;

    cout << "\n\tDelete Product\n";
    cout << "\n\tEnter product code to delete: ";
    cin >> code;

    // Open database file to read existing products
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\tError opening database file.\n";
        administrator();
        return;
    }

    // Create a temporary file to store updated product list
    tempData.open("database_temp.txt", ios::app | ios::out);
    while (data >> prdCode >> prdName >> price >> discount) {
        if (prdCode == code) {
            cout << "\n\tProduct deleted successfully.\n";
            found = true;
        } else {
            tempData << prdCode << " " << prdName << " " << price << " " << discount << "\n";
        }
    }
    data.close();
    tempData.close();

    if (found) {
        remove("database.txt");
        rename("database_temp.txt", "database.txt");
    } else {
        cout << "\n\tProduct with the given code not found.\n";
        remove("database_temp.txt");
    }

    administrator(); // Return to admin menu after deleting product
}

void Shop::listProducts() {
    fstream data;
    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\tNo products found in the database.\n";
    } else {
        cout << "\n\tProduct List:\n";
        cout << "Code\tName\t\tPrice\tDiscount\n";
        while (data >> prdCode >> prdName >> price >> discount) {
            cout << prdCode << "\t" << prdName << "\t" << price << "\t" << discount << "\n";
        }
        data.close();
    }
}

void Shop::generateReceipt() {
    fstream data;
    int codes[100], quantities[100];
    int c = 0;
    float total = 0;
    string customerName;
    char choice;

    cout << "\n\tGenerate Receipt\n";
    cout << "\n\tCustomer Name: ";
    cin.ignore();
    getline(cin, customerName);

    listProducts(); // Display available products for selection
    cout << "\n\tPlace your order:\n";

    // Collect product codes and quantities from the user
    do {
        cout << "\n\tProduct code: ";
        cin >> codes[c];
        cout << "\tQuantity: ";
        cin >> quantities[c];
        c++;
        cout << "\n\tAdd more products? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    string billDetails = "Customer: " + customerName + "\nDate: " + getCurrentDateTime() + "\n";
    billDetails += "Code\tName\t\tQuantity\tPrice\tAmount\tDiscounted Amount\n";

    // Generate receipt details based on product data
    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        while (data >> prdCode >> prdName >> price >> discount) {
            if (prdCode == codes[i]) {
                float amount = price * quantities[i];
                float discountedAmount = amount - (amount * discount / 100);
                total += discountedAmount;

                billDetails += to_string(prdCode) + "\t" + prdName + "\t\t" + to_string(quantities[i]) + "\t" +
                               to_string(price) + "\t" + to_string(amount) + "\t" + to_string(discountedAmount) + "\n";
            }
        }
        data.close();
    }

    cout << "\n\n----------------Receipt----------------\n";
    cout << billDetails;
    cout << "\nTotal: " << total << "\n";
    cout << "----------------------------------------\n";

    // Save the bill details to a file
    saveBillToFile(billDetails + "\nTotal: " + to_string(total) + "\n----------------------------------------\n");
}

void Shop::saveBillToFile(const string& billDetails) {
    fstream billFile;
    // Append the bill details to the bills file
    billFile.open("bills.txt", ios::app | ios::out);
    billFile << billDetails;
    billFile.close();
    cout << "\n\tBill saved successfully!\n";
}

void Shop::displayPreviousBills() {
    fstream billFile;
    string line;
    billFile.open("bills.txt", ios::in);

    if (!billFile) {
        cout << "\n\tNo previous bills found.\n";
    } else {
        cout << "\n\tPrevious Bills:\n\n";
        // Read and display all saved bills
        while (getline(billFile, line)) {
            cout << line << "\n";
        }
        billFile.close();
    }
}

int main() {
    Shop shop;
    shop.menu(); // Start the application by displaying the main menu
    return 0;
}
