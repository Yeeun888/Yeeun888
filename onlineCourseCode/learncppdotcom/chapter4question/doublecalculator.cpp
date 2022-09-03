#include <iostream>

int main();

double getDoubleValue() {
    std::cout << "Please enter a double value: ";
    
    double tempDouble{};
    std::cin >> tempDouble;

    return tempDouble;
}

char getOperation() {
    std::cout << "Please enter one of the following operations +, -, *, or /:  ";

    char tempOperation{};
    std::cin >> tempOperation;

    return tempOperation;
}

double finalCalculation(double d1, double d2, char opr) {
    switch(opr) {
        case '+':
            return d1 + d2;
        case '-':
            return d1 - d2;
        case '*':
            return d1 * d2;
        case '/':
            return d1 / d2;
        default:
            std::cout << "You did not enter an operation properly " << '\n';
            main();
    }
}
int main() {

    double double1 = getDoubleValue();
    double double2 = getDoubleValue();

    char oper1 = getOperation();

    double finalVal = finalCalculation(double1, double2, oper1);
    
    std::cout << double1 << oper1 << double2 << " = " << finalVal << '\n';
    
    return 0;
}