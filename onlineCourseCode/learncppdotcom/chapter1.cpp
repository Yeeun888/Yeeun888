#include <iostream>

//* Chapter 1 Notes - CPP Basics

//*Each line of a cpp program is a statement 
//such as "#include iostream", and hellow world.

//*Comments can come in two forms

//Single line

//or

/**
 * Multi  
 * Line
 * Comments
 */

//*Objects are data stored with a memory address. They addresses are tied
//*to variable names which is how they are accessed

//*Object are later then assigned and initialized

void variableExamples() {
    int x;     //A location of memory for integer by variable name X is allocated
    int y = 3; //Variable Y is allocated memory and the number 3

    [[maybe_unused]] int z; //Some compilers treat unused variables as warnings
                            //add [[maybe_unused]] tag to fix
}

//^If variables are uninitialized when used, they produce undefined behavior

void uninitializedVariable() {
    int x;

    std::cout << x;
}
//Hence it is best practice to use initialized variables

void typesOfVariableInitialization() {
               //Different types of initialization
    int a = 3; //Copy initialization; declare and then copy a value into variable
    int b (3); //Direct initlization; declare and initilizae together
    int c {3};
               //Best method because throws error for unexpected values or nonfitting values.
}

//*Input and output from console come from std::cout, std::cin, and std::endl

void inputAndOutput() {
    std::cout << 4; //Display output of text or variables
    std::cout << "Try putting a string in\n"; // "\n" is a speical character

    int inputTest {0};
    std::cin >> inputTest;

    std::cout << inputTest;
}

//*Good naming prices for variables or fucntions
//Variables and functions should describe what they do in the name.
//Other than this, they should also be capitalized properly

/*
ex:
numApples = 3;
multiplyNumber(int num, int multiplier);
etc.
*/




int main() {
    return 0;
}