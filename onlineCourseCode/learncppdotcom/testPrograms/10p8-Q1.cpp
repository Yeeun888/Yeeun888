#include <iostream>

struct Fraction {
    int numerator{};
    int denominator{ 1 };
};

Fraction getFraction() {
    Fraction tempFraction;

    std::cout << "Enter a value for the numerator: ";
    std::cin >> tempFraction.numerator;
    std::cout << "Enter a value for the denominator: ";
    std::cin >> tempFraction.denominator;

    return tempFraction;
}

int main() {
    Fraction fraction1 = getFraction();
    Fraction fraction2 = getFraction();

    int num1 = fraction1.numerator * fraction2.numerator;
    int num2 = fraction2.denominator * fraction1.denominator;

    std::cout << "Your fractions multiplied together: " << num1 << '/' << num2;
    return 0;
}