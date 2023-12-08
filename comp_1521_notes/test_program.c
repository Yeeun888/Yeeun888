#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// Add any extra #defines here.

#define MAX_PATH_LEN 4096
// The maximum number of listings possible for a directory, or results for
// a given search.
#define MAX_LISTINGS 512
// The maximum number of bytes that a user could search for.
#define MAX_SEARCH_SIZE 256
// The key for the XOR encryption algorithm.
#define XOR_BYTE_VALUE 0xA9
// The size of a cipher block.
#define CIPHER_BLOCK_SIZE 16
// The size of the initialisation vector.
#define RAND_STR_LEN 16

// Add any extra function signatures here.
typedef struct content_result {
    char *filename;  /* The filename of the result. */
    int matches;     /* The number of matches in the file. */
} content_result;
// Some provided strings which you may find useful. Do not modify.
const char *const MSG_ERROR_FILE_STAT  = "Could not stat file.\n";
const char *const MSG_ERROR_FILE_OPEN  = "Could not open file.\n";
const char *const MSG_ERROR_CHANGE_DIR = "Could not change directory.\n";
const char *const MSG_ERROR_DIRECTORY  =
    "tide does not support encrypting directories.\n";
const char *const MSG_ERROR_READ       =
    "group does not have permission to read this file.\n";
const char *const MSG_ERROR_WRITE      =
    "group does not have permission to write here.\n";
const char *const MSG_ERROR_RESERVED   =
    "'.' and '..' are reserved filenames, please search for something else.\n";

#define buffer_size 1024
#define max_string_size 1024

void recursive_search(char *directory) {
    char buffer[buffer_size];
    DIR *dirp = opendir(".");

    struct dirent *de;
    printf("checking %s\n", directory);
    while((de = readdir(dirp)) != NULL) {
        struct stat s;
        stat(de->d_name, &s);

        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }

        if(S_ISDIR(s.st_mode)) {
            printf("Going in %s\n", de->d_name);
            chdir(de->d_name);
            recursive_search(".");
            chdir("..");
        } else {
            getcwd(buffer, buffer_size);
            printf("%s %s\n", de->d_name, buffer);
        }
    }
}

char *custom_strrchr(char *cp, int ch, int n) {
    cp = &cp[strlen(cp) - 1];
    for(int i = 0; i != n; --cp) {
        if(*cp == ch) {
            ++i;
        }

        if(i == n) {
            return cp;
        }
    }

    return NULL;
}

// void search_by_content(char *search_bytes, int size) {
//     FILE *fp = fopen("test.txt", "r");
//     fseek(fp, 0, SEEK_END);
//     int fp_size = ftell(fp);
//     fseek(fp, 0, SEEK_SET);

//     char buffer[buffer_size];
//     fread(buffer, fp_size, 1, fp);
//     printf("%s\n", buffer);

//     char cmp[size];
//     //search for content in the file
//     for(int i = 0; i <= (fp_size - size); ++i) {
//         strncpy(cmp, (buffer + i), 3); 
//         if(strcmp(cmp, search_bytes) == 0) {
//                 printf("found at pos %d\n", i);
//         }
//     }
// }

void check_and_append_content_found(char *file_name, char *search_bytes, int size, content_result *files_found[], int level) {
    FILE *fp = fopen(file_name, "r");

    if(fp == NULL) {
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    int fp_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char read_buffer[buffer_size];
    fread(read_buffer, 1, buffer_size, fp);

    int counter = 0;
    for(int i = 0; i <= (fp_size - size); ++i) {
        for(int cmp = 0; cmp < size; ++cmp) {
            if(read_buffer[cmp + i] != search_bytes[cmp]) {
                break;
            }

            //Code on the bottom always executes in the bottom where letters match
            if(cmp == (size - 1)) {
                counter += 1;
            }
        }
    }

    if(counter == 0) {
        return;
    }

    char empty_string[] = "";
    char path_buffer[buffer_size];
    getcwd(path_buffer, buffer_size);
    char *path_string_ptr;
    if((path_string_ptr = custom_strrchr(path_buffer, '/', level)) == NULL) {
        path_string_ptr = empty_string;
    }

    int ff_index = 0;
    while(files_found[ff_index] != NULL) {
        ff_index += 1;
    }

    files_found[ff_index] = malloc(sizeof(content_result));
    files_found[ff_index]->filename = malloc(sizeof(char) * max_string_size);
    sprintf(files_found[ff_index]->filename, ".%s/%s", path_string_ptr, file_name);
    files_found[ff_index]->matches = counter;
}

void search_by_content_tracked(char *search_bytes, int size, content_result *files_found[], int level) {
    DIR *dirp = opendir(".");

    struct dirent *de;
    while((de = readdir(dirp)) != NULL) {
        struct stat s;
        stat(de->d_name, &s);

        //Skip . and .. as they are irrelevant
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }

        if(S_ISDIR(s.st_mode)) {
            chdir(de->d_name);
            search_by_content_tracked(search_bytes, size, files_found, level + 1);
            //Important to come back to original directory
            chdir("..");
        } else {
            check_and_append_content_found(de->d_name, search_bytes, size, files_found, level);
        }
    }
}

void search_by_content(char *search_bytes, int size) {
    content_result files_found[MAX_LISTINGS] = {NULL};

    search_by_content_tracked(search_bytes, size, &files_found, 0);
}

//JIMMY CODE
// #define CURRENT_DIRECTORY "."
// #define PARENT_DIRECTORY ".."
// void recursive_search_content (char *search_bytes, int size, char *current_path, int *count, struct content_result *result[]);

// void search_by_content(char *search_bytes, int size) {
//     int count = 0;
//     struct content_result *result = malloc(MAX_PATH_LEN * sizeof(struct content_result));

//     recursive_search_content(search_bytes, size, CURRENT_DIRECTORY, &count, &result);

//     for (int i = 0; i < count; i++) {
//         printf("%s\n", result[i].filename);
//         free(result[i].filename);
//         //FIX PRINT ONCE IT FUNCTIONS PROPERLY
//     }

// }

// void recursive_search_content (char *search_bytes, int size, char *current_path, int *count, struct content_result *result[]) {
//     char full_path[MAX_PATH_LEN];
//     getcwd(full_path, MAX_PATH_LEN);
//     DIR *current_directory = opendir(full_path);

//     struct dirent *directory_entry;
//     struct stat file_stat;

//     while ((directory_entry = readdir(current_directory)) != NULL) { 
//         // traverse through the current_directory and check if any of the files
//         // match the inputted search_string

//         stat(directory_entry->d_name, &file_stat);

//         if (S_ISREG(file_stat.st_mode)) {
//             char file_path[MAX_PATH_LEN];
//             sprintf(file_path, "%s/%s", full_path, directory_entry->d_name);
//             FILE *entry_file = fopen(file_path, "r");
//             // open and read the file (if it is a regular file) 
//             char byte_sequence[size];

//             while (fread(byte_sequence, 1, size, entry_file)) {
                
//                 if (memcmp(byte_sequence, search_bytes, size) == 0) {
//                     (*result)[*count].filename = malloc(MAX_PATH_LEN);
//                     (*result)[*count].filename = file_path;
//                     (*result)[*count].matches++;
//                 }
//             }

//             fclose(entry_file);

//             if ((*result)[*count].matches > 0) {
//                 (*count)++;
//             }

//         } else if (S_ISDIR(file_stat.st_mode) && strcmp(directory_entry->d_name, CURRENT_DIRECTORY) != 0
//             && strcmp(directory_entry->d_name, PARENT_DIRECTORY) != 0) {
//             // if the directory_entry is a subdirectory, recursively search through
//             // the subdirectory for the provided search_bytes

//             char relative_path[MAX_PATH_LEN];
//             sprintf(relative_path, "%s/%s", current_path, directory_entry->d_name);
//             // build the relative path of any potential files that match content search

//             chdir(directory_entry->d_name);
//             // change and traverse to the subdirectory 

//             recursive_search_content(search_bytes, size, relative_path, count, result);
//             //search the subdirectory for the given search_bytes recursively

//         }

//         chdir(full_path);

//     }

//     closedir(current_directory);

// }

void ecb_encryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    FILE *read_fp = fopen(filename, "a+");

    if(read_fp == NULL) {
        return;
    }

    fseek(read_fp, 0, SEEK_END);
    int read_fp_size = ftell(read_fp);
    fseek(read_fp, 0, SEEK_SET);

    int remaining_bytes = CIPHER_BLOCK_SIZE - (read_fp_size % CIPHER_BLOCK_SIZE);
    if(read_fp_size % CIPHER_BLOCK_SIZE != 0) {
        for(int i = 0; i < remaining_bytes; ++i) {
            char empty_char = 0;
            fputc(empty_char, read_fp);
        }
    }
    
    char final_file_name[buffer_size];
    sprintf(final_file_name, "%s.ecb", filename);
    FILE *write_fp = fopen(final_file_name, "w");

    char test_buffer[17]; //for
    for(int i = 0; i < 16; ++i) {
        test_buffer[i] = fgetc(read_fp);
    }

    printf("%s\n", test_buffer);
}

void print16(char *text) {
    for(int i = 0; i < 16; ++i) {
        printf("%X ", text[i]);
    }

    printf("\n");
}

char *shift_encrypt(char *plaintext, char password[CIPHER_BLOCK_SIZE]) {
    char *return_array = malloc(sizeof(char) * CIPHER_BLOCK_SIZE);

    for (int i = 0; i < CIPHER_BLOCK_SIZE; ++i) {
        uint8_t current_char = plaintext[i];
        for (int shift = 0; shift < password[i]; ++shift) {
            uint8_t front = (current_char & 0x80); 
            uint8_t back = (current_char & 0x7F);
            front >>= 7;
            back <<= 1;
            uint8_t added = front + back;
            current_char = added;
        }
        return_array[i] = current_char;
    }

    return return_array;
}

char *shift_decrypt(char *ciphertext, char password[CIPHER_BLOCK_SIZE]) {
    char *return_array = malloc(sizeof(char) * CIPHER_BLOCK_SIZE);

    for (int i = 0; i < CIPHER_BLOCK_SIZE; ++i) {
        uint8_t current_char = ciphertext[i];
        for (int shift = 0; shift < password[i]; ++shift) {
            uint8_t front = (current_char & 0xFE); 
            uint8_t back = (current_char & 0x01);
            front >>= 1;
            back <<= 7;
            uint8_t added = front + back;
            current_char = added;
        }
        return_array[i] = current_char;
    }

    return return_array;
}

int main(int argc, char *argv[]) {
    // chdir("recursive_test");
    // recursive_search("recursive_test");
    // char *test_char = "here_is_a_sentence";
    // printf("%s\n", custom_strrchr(test_char, '_', 2));
    // char *char_array[10] = {NULL};
    // char_array[0] = "This is a string";
    // char_array[1] = "This is a not string";
    // printf("%d\n", sizeof(char_array) / sizeof(char *));

    // int i = 0;
    // while(char_array[i] != NULL) {
    //     printf("%s\n", char_array[i]);
    //     i++;
    // }
//    check_and_append_content_found(char *file_name, char *search_bytes, int size, content_result *files_found[], int level) 
    // content_result *files_found[512] = {NULL};
    // check_and_append_content_found("test.txt", "the", 3, &files_found, 0);
    // printf("%s, %d\n", files_found[0]->filename, files_found[0]->matches);
    // check_and_append_content_found("test.txt", "the", 3, &files_found, 0);
    // printf("%s, %d\n", files_found[1]->filename, files_found[1]->matches);
 
    char *finished_test_1;
    char my_text[16] = "AAAABBBBCCCCDDDD";
    finished_test_1 = shift_encrypt(my_text, "passwordpassword");

    char *finished_test_2;
    finished_test_2 = shift_decrypt(finished_test_1, "passwordpassword");

    print16(finished_test_1);
    print16(finished_test_2);

    return 1;
}

