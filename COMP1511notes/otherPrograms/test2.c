#include <stdio.h>

int main() {
    scanf("%c");
    
    char x = getchar();

    do {
        printf("%c", x);
    } while (x != '\n');

    return 0;
}