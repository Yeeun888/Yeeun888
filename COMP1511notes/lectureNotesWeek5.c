#include <stdio.h>
#include <stdlib.h> //Used for atoi

void pointerDemo(int inputNum) {
    int* pointerOfInputNum = &inputNum; //Address of inputNum is stored in
                                        //pointerOfInputNum
    //Int pointer 
}

void pointerChange(int *numPointer) {
   *numPointer = 7; //changes the variable assigned to 7 
}

//*Atoi() function is used to convert string to integers
int stringToInteger(const char *str) {
    return atoi(str);
}

//* Main can take arguments from the command line when the program is called
int main(int argc, char *argv[]) {
    //^Argc is the number of arguments given.
    //^Argv is the arguments themselves. They are always strings

    int variable = 3;
    pointerChange(&variable); //Given function address
    printf("%d", variable);
}