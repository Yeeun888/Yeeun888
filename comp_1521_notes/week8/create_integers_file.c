
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(int argc, char* argv[]) {
    if(argc != 4) {
        fprintf(stderr, "Not enough args");
        return 1;
    }

    //Example command ./create_integers_file 1000.txt 1 1000

    FILE *fp = fopen(argv[1], "w");

    if(fp == NULL) {
        perror(argv[1]);
        return 1;
    }

    int last_num = atoi(argv[3]);
    for(int i = atoi(argv[2]); i <= last_num; ++i) {
        fprintf(fp, "%d\n", i);
    }
    
    fclose(fp);

    return 0;
}