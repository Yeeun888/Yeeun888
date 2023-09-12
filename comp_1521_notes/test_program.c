#include <stdio.h>

int main() {
    char c;
    while(scanf("%c", &c) != EOF) {
        //Check if vowels
        if(c == 'A' || c == 'E' || c == 'U' || c == 'I' || c == 'O' ||
           c == 'a' || c == 'e' || c == 'u' || c == 'i' || c == 'o') {
            continue;
        }

        printf("%c", c);

    }

    return 0;
}