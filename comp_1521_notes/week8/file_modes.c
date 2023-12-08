#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void print_stats(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }

    printf( (S_ISDIR(s.st_mode)) ? "d" : "-");
    printf( (s.st_mode & S_IRUSR) ? "r" : "-");
    printf( (s.st_mode & S_IWUSR) ? "w" : "-");
    printf( (s.st_mode & S_IXUSR) ? "x" : "-");
    printf( (s.st_mode & S_IRGRP) ? "r" : "-");
    printf( (s.st_mode & S_IWGRP) ? "w" : "-");
    printf( (s.st_mode & S_IXGRP) ? "x" : "-");
    printf( (s.st_mode & S_IROTH) ? "r" : "-");
    printf( (s.st_mode & S_IWOTH) ? "w" : "-");
    printf( (s.st_mode & S_IXOTH) ? "x" : "-");

}

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; ++i) {
        print_stats(argv[i]);
        printf(" %s\n", argv[i]);
    }
    return 0;
}