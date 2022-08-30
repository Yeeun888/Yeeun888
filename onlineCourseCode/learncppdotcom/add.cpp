#ifndef IOSTREAM
#include <iostream>
#endif

#include "header.h"

int readNumber() {
    std::cout << "Please enter an interger number: ";

    int input{};
    std::cin >> input;
    return input;
}

void writeAnswer(int input) {
    std::cout << "The integer that you wrote is " << input;
}
