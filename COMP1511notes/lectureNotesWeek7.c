#include <stdio.h>
#include <stdlib.h>

//Stack  behavior
//* The stack keeps tracked of the items called
int sum(int n);

void stackBehavior() {
    sum(6);
}

int sum(int n) { //Recursive function on the call stack
    if(n != 0) { //Note: use debugger
        return n + sum(n - 1);
    } else {
        return 0; //Returns zero and exits all functions
    }
}

/**
 * Call stack of the program above 
 * -main
 * -stackBehavior 
 * -sum - 6
 * -sum - 5
 * -sum - 4
 * -sum - 3
 * -sum - 2
 * -sum - 1
 * -sum - 0
 * 
 * GO BACK INTO MAIN
 * All the functions return a go back to the point where they wre called.
 * In otherwords, in reverse to the initial order of things
 * exit
 */


//Heap behavior
//*The heap is a massive area of memory that can be used by the programmer
struct node {
    int x;
    int y;
};

struct node* allocNode() {
    struct node* nodePtr = malloc(sizeof(struct node));
    return nodePtr;
}
//Code above pushes node into the heap and it is accessible by all programs in
//memory
void heapBehavior() {
    struct node* MyNode = allocNode();
    //Once done free memory
    free(MyNode);
}  

//Another example is dynamic arrays
int* dynamicArray() {
    int size;
    printf("Allocate a size of array: ");
    scanf("%d", &size);

    int* data = malloc(sizeof(int) * size);
    return data;
}

int main() {
    int* myArray = dynamicArray();

    myArray[1] = 3;
    printf("The locatation at myArray [1] is %d", myArray[1]);

    return 0;
}