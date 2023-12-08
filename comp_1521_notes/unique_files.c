#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int check_file_inode(int list[], int list_size, int inode) {
    for(int i = 0; i < list_size; ++i) {
        if(list[i] == inode) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    //Assume files are in current_working_directory

    char *filenames[1024];
    int inode_list[1024] = {0};

    int i = 0;
    for(int j = 1; j < argc; ++j) {
        struct stat s;
        stat(argv[j], &s);

        if(check_file_inode(inode_list, i, s.st_ino) == 0) {
            inode_list[i] = s.st_ino;
            filenames[i] = argv[j]; 
            i++;
        }
    }

    for(int j = 0; j < i; j++) {
        printf("%s\n", filenames[j]);
    }

    return 0;
}
