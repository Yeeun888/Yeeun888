#include <stdio.h>

//program assumes odd numbers only.

//Function is written with ALL zero index
void createLine(int width, int startPoint) {
    int front = startPoint; 
    int back = width - startPoint - 1;
    int midPoint = (width / 2);

    int backStart = width;

    int frontLock = 0;

    for(int i = 0; i < width; ++i) {
        //Print a blank space if it does not print what is wanted
        if(i != front && i != backStart) {
            printf("-");
            continue;
        }

        //Code passed here meant that i will always match either FRONT or BACK

        if(frontLock == 0) {
        //Check for front and midpoint matching
            if((front + 4) <= midPoint) {
                printf("*");
                front += 4;
                continue;
            } else {
                backStart = (midPoint - front) + midPoint;
                if(backStart == front) { backStart += 4; };
                printf("*");
                frontLock = 1;
                continue;
            }
        }
        
        if((backStart + 4) <= back) {
            //Front has already exceeded or matched mid point for code here
            printf("*");
            backStart += 4;
            continue;
        } else {
            printf("*");
            backStart += 4;
            continue;
        }
    }
}

int lmao(int num) {
    if(num == 1) {return 3;};
    if(num == 2) {return 2;};
    if(num == 3) {return 1;};
    if(num == 0) {return 0;};

    return -1;
}

int main() {

    int size = 23;
    // printf("Enter size: ");
    // scanf("%d", &size);

    //Check for odd number
    if(size % 2 == 0) {
        return -1;
    }

    int beforeMidShift = 0;

    for(int row = 0; row < size / 2 + 1; ++row) {
        createLine(size, shift + (row % 4));
        printf("\n");   
    }

    for(int row = size / 2 + 2; row < size; ++row) {
        createLine(size, lmao((size - 1) % 8));
        printf("\n");
    }

    return 0;    
}