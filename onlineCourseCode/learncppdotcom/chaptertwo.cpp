#include <iostream>

void chapter29() {
    std::cout << "this is some text\n"; //Use std:: to denote namespace

    //Manual namespace is considered good practice
}

int doublenumber(int num) {
    return num*2;
}

int chapter24(int x, int y) { //x called into local scope
    //int x and int y are called parameters which are defined at execution of function
    
    return x+y; //x and y are destoryed here
}

void chapter23() {
    //void is a function that does not return anything
}

//Function Prototype Demonstration

int multiply(int a, int b); //Function Prototype defines existing function without the body

int main() {
    
    std::cout << multiply(2,5);
    
    return 0; 
    /**
     * 0 indicates that the program has executed successfully
     * returning 0 is best practice for main()
     */
}

int multiply(int a, int b) { //Here is the final function with the contents
    return a*b;
}