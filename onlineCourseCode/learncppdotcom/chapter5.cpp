#include <iostream>
#include <cmath> 

//*Basic Arithmetic Operators
void arithOperators() {
    //Unary assignment operators = Allow for 
    int x{2};
    -x;
    +x; 

    //Basic Binary Operations
    //+, -, *, /, %

    //Integer operations result in the fractional component being dropped
    int y{ 5/2 }; //results in 2 instead of 2.5

    //Assign an operator with a variable
    //+=, -=, *=, /=, %=

    x += 4; //x = x + 4

    //For modulo it gives the remainded to the variable assigned on the left.    
}

//*C++ has no exponentiation, therefore you must write a function to do it
int exponentiation(int base, int exponent) {
    int initialBase = base;
    for(int i = 1; i < exponent; ++i) {
        base *= initialBase;
    }

    return base;
}

//*Decrements can be done in two ways
void incrementAndDecrement() {
    //Showing how increment and decrement works
    int x{ 3 }; //3
    std::cout << ++x << '\n'; //4 //Will always incrementing before anything
    std::cout << x++ << '\n'; //5 //MAYBE will do something before incrementing

    int y = x++; //6
    int z = ++x; //7
    std::cout << y << z; //Compare to output
    //^ Best to just use preincrement/predecrement such that this doesn't happen
    
}

//*Conditionals can be uesd to evaluate small amounts
void conditionalFucntion(bool x) {
    (x == false) ? std::cout << "false" : std::cout << "true";
}

//*Comparisons on floating points should be done with std::abs
// epsilon is an absolute value
bool approximatelyEqualAbs(double a, double b, double absEpsilon) {
    // if the distance between a and b is less than absEpsilon, then a and b are "close enough"
    return std::abs(a - b) <= absEpsilon;
}

//*Logical Operators are used to evaluate copmarions quickly
void logicalOperators() {
    // !, &&, ||
    bool a{0};
    bool b{1};

    std::cout << !a << '\n'; //results in negation of A or true

    //OR gate, if one of them is true then true, else false

    std::cout << a || b << '\n'; //Shows true as one of them is true

    //AND gate, only true if both is true

    std::cout << a && b << '\n'; //Shows false because both is false
}

int main() {
    return 0;
}