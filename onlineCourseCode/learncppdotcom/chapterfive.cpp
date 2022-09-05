#include <iostream>

void arithOperators() {
    //Chapter 5.2 - Arithmetic Operators

    //Unary assignment operators = Allow for 
    int x{2};
    -x;
    +x; 

    //Basic Binary Operations
    //+, -, *, /, %

    double y = 78/345;

    //Assignment Binary Operations - Very Interesting!!!

    //Assign an operator with a variable
    //+=, -=, *=, /=, %=

    x += 4; //x = x + 4

    //For modulo it gives the remainded to the variable assigned on the left.    
    
}

void additionalBasics() {
    //5.3 Modulo, exponents, and others.

    std::cout << -5 % 3 << '\n'; //Negative numbers in modulo result in negatives

    //quick power functions can be done with std::pow function
    //however making another function is better. Such as the below.
}

void decrementIncrement() {
    int a = 3;

    a++;
     /**
     * post increment. Meaning a copy of 'a' is created and stored, assigned, etc.
     * then a is actuall incremented before the copy is thrown away 
     */
    --a; 
    /**
     * pre decrement, it is knocked down by one peg before anything is done
     * more performance efficient and actually better to use
     * prefer pre-decrement/pre-increment.
     */
}

void commaConditional() {
    //Commas are just use for separating multiple statements

    int a=1, b=2, c=3;

    //Conditional statements can be used for very efficient and trivial if statements
    //Conditional ? if true execute : if false execute

    (a > 4) ? std::cout << "a is larger than 4" : std::cout << "a is smaller than 4" ;
}

void relationalFloatingPoints() {
    //Relationals are like <, >, <=, >=, ==, and !=
    //Using them with floats can be dangerous due to rounding errors

    //Comparisons of floating points have to be done carefully
    //ex: Epsilon comparison algorithm
}

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
    