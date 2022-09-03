#include <iostream>

using namespace std;

void lastChapter() {
    std::cout << "Enter an integer to double! -> ";

    int num {0};
    std::cin >> num;

    std::cout << "Double that number is " << num*2 << "!" << std::endl;
}

void chapter17() {
    //Best naming practices for variables and functions

    //Always start value names with lower case
    /**
     * 2. Identifiers should not being with underscore 
     * 3. Identifiers should be descriptive to what they do in actual real code
     */
    int value;
    int this_is_snake_case; //Using underscores to separate the values
    int thisIsCamelCase;    //Using upper case letters to distinguish the values
}

void chapter16() {
    int x;

    std::cout << x;
}

void chapter15() {
    std::cout << 4; //Display output of text or variables
    std::cout << "Try putting a string in\n"; // "\n" is a speical character

    int inputTest {0};
    cin >> inputTest;

    std::cout << inputTest;
}

void chapter14() {
               //Different types of initialization
    int a = 3; //Copy initialization; declare and then copy a value into variable
    int b (3); //Direct initlization; declare and initilizae together
    int c {3};
               //Best method because throws error for unexpected values or nonfitting values.
}

void chapter13() {
    int x; //This is declaration, it only allocates space and a type to the variable
    int y = 3; //This is initilization which also give it a new value
}

int main() {
    
    std::cout << std::endl;

    //1.2 Comments
    //Good comments are describe why some choice of code was used.d

    //ex: Done to see if iostream library is properly imported.

    std::cout << __cplusplus << std::endl;

    lastChapter();

    return 0;
}