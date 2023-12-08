#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Wrong arguments");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "The is no file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);

    fseek(fp, 0, SEEK_SET); 

    //Check if following are LIT
    char s[4] = "  \0";
    s[0] = fgetc(fp);
    s[1] = fgetc(fp);
    s[2] = fgetc(fp);
    file_size -= 3;

    if(strcmp(s, "LIT\0") != 0) {
        fprintf(stderr, "Failed to read magic\n");
        return 1;
    }



    while(file_size > 0) {
        int size_of_integer = fgetc(fp) - 48;
        if(size_of_integer == 0 || size_of_integer == 9 || size_of_integer < 0) {
            fprintf(stderr, "Invalid record length\n");
            return 1;
        }
        file_size -= 1;

        uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        fread(buffer, 1, size_of_integer, fp);

        if(size_of_integer > file_size) {
            fprintf(stderr, "Broken Record\n");
            return 1;
        }

        file_size -= size_of_integer;

        uint64_t temp = 0;

        for(int i = 7; i >= 0; --i) {
            temp += buffer[i];
            if(i != 0) {
                temp <<= 8;
            }
        }

        printf("%lu\n", temp);
    }

    fclose(fp);

    return 0;
}