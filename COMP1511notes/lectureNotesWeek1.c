#include <stdio.h>

//*Types of variables
int x = 1;      //Integer value, no fractional components //4 bytes
char y = 2;     //Char data interpreted as character      //1 bytes
double z = 3.0; //Number with fractional component        //8 bytes hence the name double

void terminalOutput() {
    //*Naming convention of variables
    int height = 1523434;
    int HeIgHt = 2; //Are different as they are case sensitive

    printf("My height is %d\n", height); //d means decimal integer lmao
    printf("My height is %lf\n", height); //lf means long float
}

void terminalInput() {
    #if 0 
    int height;
    printf("Enter your height: ");
    scanf("%d", &height);
    #endif
    
    //*Interesting character protection! Ignores whitespace!
    char testCharacter;
    printf("Try a character here: ");
    scanf(" %c", &testCharacter); //Use the space before %c
}

int main() {
    terminalInput();
    return 0;
}