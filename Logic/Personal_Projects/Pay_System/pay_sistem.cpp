#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

#include "shopping_cart.cpp"

#define MAX_INPUT_PRODUCT_SIZE 20
#define LARGEST_PRODUCT_SIZE 9
#define TOTAL_PRODUCTS 3
#define MAXOPTIONSIZE 5
#define ROW_DISPLAY_CHANGE 4

#define printInvalidCardMessage printf("\nThe entered card is not valid\n");

using namespace std;

typedef enum {
    EXIT,
    CONTINUE
} INPUT;

typedef enum {
    VISA,
    MASTERCARD,
    AMERICAN_EXPRESS,
    INVALID
} CardType;

struct CartItem {
    int productId;
    int quantity;
};

struct Cart {
    vector<CartItem> items;
    int cartSize;
};

struct Product {
    string name;
    double price;
    int inventory;
};

vector<Product> products = {
    {"Quesidogo", 30.0, 12},
    {"Sencillo", 16.0, 9},
    {"Soda", 15.0, 23}
};

void initializeCart(Cart& cart) {
    cart.cartSize = 0;
    cart.items.clear();
}

void displayMenu() {
    for (int i = 0; i < TOTAL_PRODUCTS; i++) {
        if (i != 0 && i % ROW_DISPLAY_CHANGE == 0) {
            cout << endl;
        }

        cout << setw(2) << i + 1 << ".- " << 
        setw(LARGEST_PRODUCT_SIZE) << left << products[i].name << 
        " $" << fixed << setprecision(2) << products[i].price << "\t";
    }

    cout << endl;
}

void capitalizeFirstLetter(string& str) {
    if (!str.empty() && islower(str[0])) {
        str[0] = toupper(str[0]);
    }
}

void lowerCaseStr(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void normalizeStr(string& str) {
    lowerCaseStr(str);
    capitalizeFirstLetter(str);
}


int identifyProductId(const string input) {
    string normalizedInput = input;
    
    normalizeStr(normalizedInput);

    for (int productId = 0; productId < TOTAL_PRODUCTS; ++productId) {
        if (normalizedInput == products[productId].name) {
            return productId;
        }
    }

    return -1;
}

INPUT readOrderContinue() {
    string response;

    do {
        cout << "¿Desea ordenar algo mas? (Si/No)" << endl;
        cin >> response;

        lowerCaseStr(response);
    } while (response != "si" && response != "no");

    return response == "si" ? CONTINUE : EXIT;
}

int readProductRequest() {
    string input;
    
    cout << "Introduzca el nombre del producto que desea" << endl;
    cin >> input;
    
    return identifyProductId(input);
}

int readAmountRequest() {
    int amount;

    cout << "Introduzca la cantidad que desea del producto" << endl;
    cin >> amount;

    return amount;
}

void addProduct(Cart& cart, int productId, int quantity) {
    if (products[productId].inventory >= quantity) {
        cart.items.push_back({productId, quantity});
        cart.cartSize++;
        products[productId].inventory -= quantity;
    } else {
        cout << "Inventario insuficiente." << endl;
    }
}

void deleteProduct(Cart& cart, int productId) {
    for (int i = 0; i < cart.cartSize; ++i) {
        if (cart.items[i].productId == productId) {
            // cart->items changed to cart.items, expected errors
            products[cart.items[i].productId].inventory += cart.items[i].quantity;
            cart.items.erase(cart.items.begin() + i);
            cart.cartSize--;
            return;
        }
    }

    cout << "Producto no encontrado en el carrito." << endl;
}

float calculateTotal(const Cart& cart) {
    float total = 0.0f;

    for (const CartItem& item : cart.items) {
        total += products[item.productId].price * item.quantity;
    }

    return total;
}

void displayCart(const Cart& cart) {
    float total = calculateTotal(cart);

    cout << "Carro:" << endl;

    for (const CartItem& item : cart.items) {
        cout << products[item.productId].name << " (";
        cout << fixed << setprecision(2) << products[item.productId].price << ") x ";
        cout << item.quantity << " = ";
        cout << fixed << setprecision(2) << products[item.productId].price * item.quantity << endl;
    }

    cout << "Total: " << fixed << setprecision(2) << total << endl;
}

void cleanNonNumericCharacters(string& str) {
    string result;
    for (char c : str) {
        if (isdigit(c)) {
            result += c;
        }
    }
    str = result;
}


bool isCardValid(const string& cardNumber) {
    int sum = 0;
    bool alternate = false;

    for (int i = cardNumber.length() - 1; i >= 0; --i) {
        int digit = cardNumber[i] - '0';

        if (alternate) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        alternate = !alternate;
    }

    return (sum % 10) == 0;
}

bool startsWithRange(const string& str, int start, int end, int numChars) {
    if (numChars > str.length()) {
        return false; 
    }

    string prefix = str.substr(0, numChars);
    int prefixInt = stoi(prefix);
    return prefixInt >= start && prefixInt <= end;
}

bool startsWith(const string& str, const string& prefix) {
    return str.substr(0, prefix.length()) == prefix;
}

CardType identifyCardType(const string& cardNumber) {
    switch (cardNumber.length()) {
        case 13:
            if (startsWith(cardNumber, "4")) {
                return VISA;
            }
            break;
        case 16:
            if (startsWith(cardNumber, "4")) {
                return VISA;
            } else if (startsWithRange(cardNumber, 51, 55, 2)) {
                return MASTERCARD;
            } else if (startsWithRange(cardNumber, 2221, 2227, 4)) {
                return MASTERCARD;
            }
            break;
        case 15:
            if (startsWithRange(cardNumber, 34, 37, 2)) {
                return AMERICAN_EXPRESS;
            }
            break;
    }
    return INVALID;
}

void printCardType(CardType cardType) {
    switch (cardType) {
        case VISA:
            cout << "La tarjeta ingresada es VISA\n";
            break;
        case MASTERCARD:
            cout << "La tarjeta ingresada es MASTERCARD\n";
            break;
        case AMERICAN_EXPRESS:
            cout << "La tarjeta ingresada es AMERICAN EXPRESS\n";
            break;
        case INVALID:
            cout << "La tarjeta ingresada es inválida\n";
            break;
    }
}

bool isEnoughMoneyInCard(const double money, const double total) {
    return money >= total;
}

int main(void) {
    /*
    struct Cart cart;
    initializeCart(cart);
    INPUT input = CONTINUE;
    
    do {    
        displayMenu();
        int product = readProductRequest();
        int quantity = readAmountRequest();
        addProduct(cart, product, quantity);
        displayCart(cart);
        input = readOrderContinue();
    } while (input == CONTINUE);
    
    
    displayMenu();
    int product = readProductRequest();
    int quantity = readAmountRequest();
    addProduct(&cart, product, quantity);
    displayCart(&cart);
    */

    return 0;
}
