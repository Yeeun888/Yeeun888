#include <stdio.h>
//Stdio.h includes both fgets and fputs

//*Strings are just an array of characters with adjacent memory locations
void stringDemo() {
    char testWord[] = {"This is an example string"};
}

//*Fgets inserts strings safely into other things 
void fgetsDemo() {
    //Modifies the string
    char testWord[] = {"This is an example string"};
    printf("%s\n", &testWord);

    //Fgets limited to 12 characters 

    //fgets(input, MAX_LENGTH, stream source)
    fgets(testWord, 12, stdin); 
    printf("%s", &testWord);
}

//*Gputs brings an output onto a stream
void fputsDemo() {
    char testWord[] = {"This is an example string"};
    fputs(testWord, stdout);
}

int main() {
    fputsDemo();
    return 0;
}