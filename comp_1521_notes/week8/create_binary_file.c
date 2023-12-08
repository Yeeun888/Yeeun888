#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    //example of command
    //./create_binary_file count.binary 1 2 3 251 252 253 254 255
    
    if(argc < 2) {
        fprintf(stderr, "Not enough args");
        return 1;
    }

    FILE *fp = fopen(argv[1],"w");

    for(int i = 2; i < argc; ++i) {
        fputc(atoi(argv[i]), fp);
    }

    return 1;
}