#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
