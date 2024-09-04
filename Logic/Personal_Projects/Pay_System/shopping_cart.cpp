#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:
    string name;
    double price;
    int quantity;

public:
    Item(const string itemName, double itemPrice, int itemQuantity) : name(itemName), price(itemPrice), quantity(itemQuantity) {}
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int itemQuantity) {
        this->quantity = itemQuantity;
    }
};

class ShoppingCart {
private:
    vector<Item> items;
    int cartSize;

public:
    void addItem(const Item& item) {
        items.push_back(item); 
    }

    removeItem(const string& item) {
        for (auto i = items.begin(); i != items.end(); ++i) {
            if (i->getName() == name) {
                items.erase(i);
                break;
            }
        }
    }

    double calculateTotal() const {
        double total = 0.0;

        for (const Item& item : items) {
            total = item.getPrice() * item.getQuantity();
        }
        return total;
    }
};