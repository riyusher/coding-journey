#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSIZE 100
#define TOTAL_PRODUCTS 3
#define MAXOPTIONSIZE 5

#define printInvalidCardMessage printf("\nThe entered card is not valid\n");



typedef enum {
    EXIT
} Input;

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
    struct CartItem items[TOTAL_PRODUCTS];
    int cartSize;
};

struct Product {
    char name[MAXSIZE];
    int id;
    double price;
    int inventory;
};

struct Product products[TOTAL_PRODUCTS] = {
    {"Quesidogo", 0, 30.0, 12},
    {"Sencillo", 1, 16.0, 9},
    {"Soda", 2, 15.0, 23},
};

void initializeCart(struct Cart *cart) {
    cart->cartSize = 0;
}

void displayMenu() {
    printf("1.- %s $%.2lf\t2.- %s $%.2lf\t3.- %s $%.2lf\n",
    products[0].name, products[0].price, products[1].name, products[1].price, products[2].name, products[2].price);
    return;
}

bool isAProduct(char *product) {
    if (islower(product[0])) {
        product[0] = toupper(product[0]);
    }

    for (int i = 0; i < TOTAL_PRODUCTS; i++) {
        if (strcmp(product, products[i].name) == 0) {
            return true;
        }
    }

    return false;
}

void lowerCaseString(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
    return;
}

bool readOrderContinue() {
    printf("¿Desea ordenar algo mas? (Si/No)");

    char option[MAXOPTIONSIZE];
    fgets(option, MAXOPTIONSIZE, stdin);

    lowerCaseString(option);

    while (strcmp(option, "si") != 0 && strcmp(option, "no") != 0) {
        printf("Digite una opción Valida (Si/No)\n");
        printf("¿Desea ordenar algo mas? (Si/No)\n");
        fgets(option, MAXOPTIONSIZE, stdin);
        lowerCaseString(option);
    }
    
    return strcmp(option, "si") == 0;
}

char* readProductRequest() {
    char *str = malloc(MAXSIZE * sizeof(char));
    printf("Introduzca el nombre del producto que desea\n");
    fgets(str, MAXSIZE, stdin);
    return str;
}

int readAmountRequest() {
    int amount;
    printf("Introduzca la cantidad que desea del producto\n");
    scanf("%d", &amount);
    return amount;
}

void addProduct(struct Cart *cart, int productId, int quantity) {
    if (productId >= 0 && productId < TOTAL_PRODUCTS && products[productId].inventory >= quantity) {
        cart->items[cart->cartSize].productId = productId;
        cart->items[cart->cartSize].quantity = quantity;
        cart->cartSize++;
        products[productId].inventory -= quantity;
    } else {
        printf("Inventario insuficiente.\n");
    }
}

void deleteProduct(struct Cart *cart, int productId) {
    int i;
    for (i = 0; i < cart->cartSize; i++) {
        if (cart->items[i].productId == productId) {
            break;
        }
    }
    if (i < cart->cartSize) {
        products[cart->items[i].productId].inventory += cart->items[i].quantity;
        for (int j = i; j < cart->cartSize - 1; j++) {
            cart->items[j] = cart->items[j + 1];
        }
        cart->cartSize--;
    } else {
        printf("Producto no encontrado en el carrito.\n");
    }
}

void displayCart(struct Cart *cart) {
    float total = 0;
    printf("Carro:\n");
    for (int i = 0; i < cart->cartSize; i++) {
        float totalForThisProduct = products[cart->items[i].productId].price * cart->items[i].quantity;
        printf("%s (%.2f) x %d = %.2f\n", products[cart->items[i].productId].name, products[cart->items[i].productId].price, cart->items[i].quantity, totalForThisProduct);
        total += totalForThisProduct;
    }
    printf("Total: %.2f\n", total);
}

void cleanNonNumericCharacters(char *str) {
    int writeIndex = 0;
    for(int readIndex = 0; str[readIndex] != '\0'; readIndex++) {
        if(isdigit(str[readIndex])) {
            str[writeIndex] = str[readIndex];
            writeIndex++;
        }
    }
    str[writeIndex] = '\0';
}

bool isCardValid(char *card) {
    int stringLen = strlen(card);
    int sum = 0; 
    bool flag = false; 

    for(int i = stringLen - 1; i >= 0; i--) {
        int tempNum = card[i] - '0';
        
        if (flag) {
            tempNum *= 2;
            if(tempNum > 9) {
                tempNum -= 9;
            }
        }
        sum += tempNum;
        flag = !flag;
    }

    return (sum % 10 == 0);
}

bool startsWithRange(const char *str, int start, int end, int numChars) {
    char prefixStr[MAXSIZE] = {0};
    strncpy(prefixStr, str, numChars);
    int prefix = atoi(prefixStr);
    return prefix >= start && prefix <= end;
}

bool startsWith(const char *str, const char *prefix) {
    while(*prefix) {
        if(*prefix++ != *str++)
            return false;
    }
    return true;
}

CardType identifyCardType(char *cardNumber) {
    int cardLength = strlen(cardNumber);

    switch(cardLength) {
        case 13:
            if(startsWith(cardNumber, "4")) {
                return VISA;
            }
            break;
        case 16:
            if(startsWith(cardNumber, "4")) {
                return VISA;
            }
            else if(startsWithRange(cardNumber, 51, 55, 2)) {
                return MASTERCARD;
            }
            else if(startsWithRange(cardNumber, 2221, 2227, 4)) {
                return MASTERCARD;
            }
            break;
        case 15:
            if(startsWithRange(cardNumber, 34, 37, 2)) {
                return AMERICAN_EXPRESS;
            }
            break;
    }
    return INVALID;
}

void printCardType(CardType cardType) {
    switch(cardType) {
        case VISA:
            printf("La tarjeta ingresada es VISA\n");
            break;
        case MASTERCARD:
            printf("La tarjeta ingresada es MASTERCARD\n");
            break;
        case AMERICAN_EXPRESS:
            printf("La tarjeta ingresada es AMERICAN EXPRESS\n");
            break;
        case INVALID:
            printInvalidCardMessage
            break;
    }
}

bool isEnoughMoneyInCard(const double money, const double total) {
    return money >= total;
}

int main(void) {
    struct Cart cart;
    initializeCart(&cart);

    /*
    displayMenu();
    addProduct(&cart, 0, 2);
    addProduct(&cart, 1, 3);
    displayCart(&cart);
    */
    
    return 0;
}
