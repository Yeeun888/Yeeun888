#include <stdio.h> //Used for input output

//*Messages can be printed with printf
int printAndReturnMessage() {
    printf("%s", "Give me a number");
    int x;
    scanf("%i", &x);
    return x;
}

//*Loops can be used to repeat code
int loopsDemo() {
    //While loop
    int whileVar = 0;
    while(whileVar < 5) {
        ++whileVar;
    }

    //^Loops can be nested
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < i; ++j) {
            printf("%i ", j);
        }
        printf("\n");
    }

    return 0;
}

//*Generate custom data structures to define things yourself!
//^Structs cannot be initialized with values before hand
struct Shoe{
    int shoeSize;
    int soleSize;
};

void structCreation() {
    struct Shoe maxWhiteShoes;

    //^access of variables are done though the . operator
    maxWhiteShoes.shoeSize = 45;
    maxWhiteShoes.soleSize = 42;
}

//*Enumerators are used to substitute numbers
enum weekdays { Mon, Tue, Wed, Thu, Fri, Sat, Sun };


int main() {
    loopsDemo();
    return 0;
}
