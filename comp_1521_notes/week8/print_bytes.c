#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Not enough args");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    int i = 0;
    int taken_char;
    while((taken_char = fgetc(fp)) != EOF) {
        printf("byte %4d: %3d 0x%02x", i , taken_char, taken_char);

        if(isprint(taken_char)) {
            printf(" '%c'", taken_char);
        }

        printf("\n");
        i += 1;
    }

    return 0;
}