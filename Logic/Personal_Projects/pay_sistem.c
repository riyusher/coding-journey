#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100
#define TOTAL_PRODUCTS 3
#define MAXOPTIONSIZE 5

enum Input {
    EXIT
};

struct Product {
    char name[MAXSIZE];
    double price;
    int inventory;
};

struct Product products[TOTAL_PRODUCTS] = {
    {"Quesidogo", 30.0, 12},
    {"Sencillo", 16.0, 9},
    {"Soda", 15.0, 23},
};

struct Cart {
    int cartSize;
};

void displayMenu() {
    printf("1.- %s $%.2lf\t2.- %s $%.2lf\t3.- %s $%.2lf\n",
    products[0].name, products[0].price, products[1].name, products[1].price, products[2].name, products[2].price);
    return;
}

void lowerCaseString(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
    return;
}

bool getContinue() {
    bool input = false;
    printf("¿Desea ordenar algo mas? (Si/No)");

    char *option;
    fgets(option, MAXOPTIONSIZE, stdin);

    lowerCaseString(option);

    while (strcmp(option, "si") != 0 || strcmp(option, "no") != 0) {
        printf("Digite una opción Valida (Si/No)");
        printf("¿Desea ordenar algo mas? (Si/No)");
        fgets(option, MAXOPTIONSIZE, stdin);
    }
    
    if (strcmp(option, "si") == 0) {
        input = true;
    }
    
    return input;
}

char* getProductRequest() {
    char *str;
    printf("Introduzca el nombre del producto que desea");
    fgets(str, MAXSIZE, stdin);
    return str;
}

int getAmountRequest() {
    int amount;
    printf("Introduzca la cantidad que desea del producto");
    scanf("%d", &amount);
    return amount;
}

void addProduct() {

}

void updateInventory() {
    
}

int main(void) {
    enum Input option;

    displayMenu();
    /*
    do {
        displayMenu();
        displayRequest();

    } while (option != EXIT);
    */

    return 0;
}