#include <iostream>

int addition(int x, int y) {
    return x+y;
}

int subtraction(int x, int y) {
    return x-y;
}

int multiplication(int x, int y) {
    return x*y;
}

int division(int x, int y) {
    return x/y;
}

char getOperation() {
    char operation{};
    while(true) {
        std::cin >> operation;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        } else if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
            return operation;
        } else { std::cout << "Enter something valid\n"; std::cin.ignore(1000, '\n'); continue; }
    }
}

using ArithmeticFunction = int (*)(int, int);

ArithmeticFunction getFunction(char op) {
    switch(op) {
        case '+': return ArithmeticFunction{ &addition };
        case '-': return ArithmeticFunction{ &subtraction };
        case '*': return ArithmeticFunction{ &multiplication };
        case '/': return ArithmeticFunction{ &division };
    }
}

int main() {
    char operation = getOperation();
    ArithmeticFunction funcPtr = getFunction(operation);
    
    //Numbers to operate on
    int x, y;
    std::cin >> x >> y;

    std::cout << funcPtr(x, y);

    return 0;
}