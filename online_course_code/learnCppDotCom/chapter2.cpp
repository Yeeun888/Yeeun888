#include <iostream>

//*Chapter 2 - Function and Files 

//*Functions are blocks of code that pause execution and have the cpu jump
int exampleFunction1(std::string passedText) {
    std::cout << passedText;
    return 0;
}

//Functions are called as follows
void callFunction() {
    exampleFunction1("Here is some argument text");
}

/**
 * Function can return multiple things such as  
 * int, char, std::string even objects. Void means that the function
 * returns nothing.
 */

//*The parameter is set during the function definition. The argument is the
//*object passed when the parameter is called. 

//*Functions must be defined before they are called as programs execute sequentially.
//*therefore, they can be forward declared

int returnZero();

void callForwardFunction() {
    std::cout << returnZero();
}

int returnZero() {
    return 0;
} 
 //returnZero defined right after it was used. 
//^If forward declaring a function without defining it, it will produce an error

//* #Define and #Include can be used as a preprocessor directive. 
//^ Preprocessor directives are checked top-to-bottom regardless of where it is 
//^ positioned. 

void demonstratePreprocessorDirective() {
    #define PRINT_JOE 

    #ifdef PRINT_BOB //As PRINT_BOB is not defined therefore the code doesn't run
    std::cout << "Bob\n";
    #endif

    #ifdef PRINT_JOE
    std::cout << "Joe\n";
    #endif

    #if 0 //"#if 0" excludes all the code below it until "#endif"
    for(int i = 0; i < 5, ++i) {
        std::cout << i << " ";
    };
    #endif //Very easy way of commenting out code
}

//*All preprocessor directives just copy the code from the selected file. 
//*therefore using headers (filled with forward declared functions) 
//*is much more preferred. 
//Refer to chapter2head.h for notes. 

int main() {
    return 0;
}