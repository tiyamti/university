#include <iostream>
#include <string>
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

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
