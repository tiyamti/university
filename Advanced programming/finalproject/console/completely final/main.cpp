#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
class Product {
private:
    string name;
    int quantity;
    double price;

public:
    Product(const string& name, int quantity, double price)
            : name(name), quantity(quantity), price(price) {}

    const string& getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }
    void setPrice(int newPrice) {
        price = newPrice;
    }
    void display() const {
        cout << "Name: " << name << "\tQuantity: " << quantity << "\tPrice: $" << price << endl;
    }
};
class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void removeProduct(const string& name) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it).getName() == name) {
                products.erase(it);
                break;
            }
        }
    }

    void editProduct(const string& name, int newQuantity, double newPrice) {
        for (auto& product : products) {
            if (product.getName() == name) {
                product.setQuantity(newQuantity);
                product.setPrice(newPrice);
                break;
            }
        }
    }

    void displayInventory() const {
        cout << "Inventory:" << endl;
        for (const auto& product : products) {
            product.display();
        }
    }

    Product* findProduct(const string& name) {
        for (auto& product : products) {
            if (product.getName() == name) {
                return &product;
            }
        }
        return nullptr;
    }

    void saveInventoryToFile() const {
        ofstream file("F:\\pishrafteh\\final project\\completely final\\inventory.txt");
        for (const auto& product : products) {
            file << product.getName() << " " << product.getQuantity() << " " << product.getPrice() <<endl;
        }
        file.close();
    }

    void loadInventoryFromFile() {
        ifstream file("F:\\pishrafteh\\final project\\completely final\\inventory.txt");
        string name;
        int quantity;
        double price;
        while (file >> name >> quantity >> price) {
            Product newProduct(name, quantity, price);
            products.push_back(newProduct);
        }
        file.close();
    }

    bool issueInvoice(const string& customerName, const vector<pair<string, int>>& purchasedProducts) {
        ofstream file(customerName + ".csv");
        if (!file) {
            cout << "Failed to create invoice file." << endl;
            return false;
        }

        file << "Product,Quantity,Price,Total" << endl;
        double totalPrice = 0.0;
        for (const auto& purchase : purchasedProducts) {
            string productName = purchase.first;
            int quantity = purchase.second;

            Product* product = findProduct(productName);
            if (product == nullptr || quantity > product->getQuantity()) {
                file.close();
                cout << "Failed to issue invoice. Product not found or insufficient quantity." << endl;
                return false;
            }

            double productPrice = product->getPrice();
            double productTotal = quantity * productPrice;
            totalPrice += productTotal;

            file << productName << "," << quantity << "," << productPrice << "," << productTotal << endl;

            product->setQuantity(product->getQuantity() - quantity);
        }

        file << endl << "Total Price: $" << totalPrice << endl;
        file.close();

        return true;
    }
};
class User {
private:
    string username;
    string password;

public:
    User(const string& username, const string& password)
            : username(username), password(password) {}

    const string& getUsername() const {
        return username;
    }

    const string& getPassword() const {
        return password;
    }
};
class Buyer {
private:
    string name;
    double balance;
    string currency;

public:
    Buyer(const string& name, double balance, const string& currency)
            : name(name), balance(balance), currency(currency) {}

    const string& getName() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    const string& getCurrency() const {
        return currency;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }

    void setCurrency(const string& newCurrency) {
        currency = newCurrency;
    }
};
class Application {
private:
    vector<Buyer> buyers;
    Inventory inventory;
    double exchangeRate;
    time_t lastUpdated;

public:
    Application()
            : exchangeRate(1.0), lastUpdated(time(nullptr)) {}

    void registerUser(const string& username, const string& password) {
        User newUser(username, password);
        users.push_back(newUser);
        saveUsersToFile();
    }

    void loginUser() {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                cout << "Logged in successfully!" << endl;
                return;
            }
        }

        cout << "Invalid username or password." << endl;
    }

    void loadUsersFromFile() {
        ifstream file("F:\\pishrafteh\\final project\\completely final\\users.txt");
        string username, password;
        while (file >> username >> password) {
            User newUser(username, password);
            users.push_back(newUser);
        }
        file.close();
    }

    void saveUsersToFile() const {
        ofstream file("F:\\pishrafteh\\final project\\completely final\\users.txt");
        for (const auto& user : users) {
            file << user.getUsername() << " " << user.getPassword() << endl;
        }
        file.close();
    }

    void addProductToInventory() {
        string name;
        int quantity;
        double price;

        cout << "Enter product details:" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price: ";
        cin >> price;

        Product newProduct(name, quantity, price);
        inventory.addProduct(newProduct);
        inventory.saveInventoryToFile();
    }

    void removeProductFromInventory() {
        string name;
        cout << "Enter the name of the product to remove: ";
        cin >> name;
        inventory.removeProduct(name);
        inventory.saveInventoryToFile();
    }

    void editProductInInventory() {
        string name;
        int newQuantity;
        double newPrice;

        cout << "Enter the name of the product to edit: ";
        cin >> name;
        cout << "Enter the new quantity: ";
        cin >> newQuantity;
        cout << "Enter the new price: ";
        cin >> newPrice;

        inventory.editProduct(name, newQuantity, newPrice);
        inventory.saveInventoryToFile();
    }

    void displayInventory() const {
        inventory.displayInventory();
    }

    void issueInvoice() {
        string customerName;
        cout << "Enter customer name: ";
        cin >> customerName;

        vector<pair<string, int>> purchasedProducts;

        while (true) {
            string productName;
            int quantity;
            cout << "Enter product name (or 'done' to finish): ";
            cin >> productName;
            if (productName == "done") {
                break;
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            purchasedProducts.push_back(make_pair(productName, quantity));
        }

        if (inventory.issueInvoice(customerName, purchasedProducts)) {
           cout << "Invoice issued successfully!" << endl;
        }
    }

    void loadInventoryFromFile() {
        inventory.loadInventoryFromFile();
    }

    void saveInventoryToFile() const {
        inventory.saveInventoryToFile();
    }

    void addBuyer() {
        string name;
        double balance;
        string currency;

        cout << "Enter buyer details:" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Balance: ";
        cin >> balance;
        cout << "Currency: ";
        cin >> currency;

        Buyer newBuyer(name, balance, currency);
        buyers.push_back(newBuyer);
    }

    void removeBuyer() {
        string name;
        cout << "Enter the name of the buyer to remove: ";
        cin >> name;

        for (auto it = buyers.begin(); it != buyers.end(); ++it) {
            if ((*it).getName() == name) {
                buyers.erase(it);
                break;
            }
        }
    }

    void displayBuyerDashboard(const std::string& buyerName) {
        for (const auto& buyer : buyers) {
            if (buyer.getName() == buyerName) {
                cout << "Buyer: " << buyer.getName() << endl;
                cout << "Balance: " << buyer.getBalance() << " " << buyer.getCurrency() << endl;
                return;
            }
        }

        cout << "Buyer not found." << endl;
    }

    void updateExchangeRate(double newRate) {
        exchangeRate = newRate;
    }

    void manuallyUpdateExchangeRate() {
        double newRate;
        cout << "Enter the new exchange rate: ";
        cin >> newRate;
        updateExchangeRate(newRate);
    }

    double getExchangeRate() const {
        return exchangeRate;
    }


    vector<User> users;
};

int main() {
    Application app;
    app.loadUsersFromFile();
    app.loadInventoryFromFile();

    // Register a user if no users exist
    if (app.users.empty()) {
        string username, password;
        cout << "Welcome! Let's create your account." << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        app.registerUser(username, password);
    }

    app.loginUser();

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add product to inventory" << endl;
        cout << "2. Remove product from inventory" << endl;
        cout << "3. Edit product in inventory" << endl;
        cout << "4. Display inventory" << endl;
        cout << "5. Issue invoice" << endl;
        cout << "6. Add buyer" <<endl;
        cout << "7. Remove buyer" << endl;
        cout << "8. Display buyer dashboard" << endl;
        cout << "9. Update exchange rate manually" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                app.addProductToInventory();
                break;
            case 2:
                app.removeProductFromInventory();
                break;
            case 3:
                app.editProductInInventory();
                break;
            case 4:
                app.displayInventory();
                break;
            case 5:
                app.issueInvoice();
                break;
            case 6:
                app.addBuyer();
                break;
            case 7:
                app.removeBuyer();
                break;
            case 8: {
                string buyerName;
                cout << "Enter the name of the buyer: ";
                cin >> buyerName;
                app.displayBuyerDashboard(buyerName);
                break;
            }
            case 9:
                app.manuallyUpdateExchangeRate();
                break;
            case 10:
                app.saveUsersToFile();
                app.saveInventoryToFile();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
