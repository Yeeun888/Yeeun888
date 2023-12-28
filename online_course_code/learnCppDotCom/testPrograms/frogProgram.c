#include <stdio.h>
#include <stdlib.h>

int numberOfRuns() {
    int testInteger;
    scanf("%d", &testInteger);
    return testInteger;
}

int main() {
    int x = numberOfRuns();

    int *array = malloc(sizeof(int) * x);
    int *arrayPair = malloc(sizeof(int) * x);

    for(int i = 0; i < x; ++i) {
        scanf("%i", (array + i));
        scanf("%i", (arrayPair + i));
    }

    for(int i = 0; i < x; ++i) {
        if(*(array + i) % 2 == 0  && *(arrayPair + i) % 2 == 0) {
            printf("Case #%i: Party time!\n", i);
        } else {
            printf("Case #%i: Need more frogs\n", i);
        }
    }

//    printf("%d", *array);
//    printf("%d", *arrayPair);

    return 0;
}