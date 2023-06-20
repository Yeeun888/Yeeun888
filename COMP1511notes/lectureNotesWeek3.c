#include <stdio.h>

//*Basics of functions

//function starts with return type
//then function name
int add(int x, int y) {
    //x and y are parameters
    return x+y; //return kills the program
}

//*Arrays can be used to store multiple variables together 
void arrayDemo() {
    //Code above stores the amount in some variables
    int listOfNumbers[10] = {1,2,3,4,5,6,7,8,9};
    //^Numbers that are uninitialized are left to start with zero

    //Arrays then can be looped into
    for(int i = 0; i < 10; ++i) {
        printf("%d\n", listOfNumbers[i]);
    } 
}

int main() {
    int twoNumbers = add(2,3); //Add is called with arguments

    arrayDemo();
    return 0;
}