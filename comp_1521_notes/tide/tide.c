////////////////////////////////////////////////////////////////////////////////
// COMP1521 23T3 --- Assignment 2: `tide', a terribly insecure (file) decryptor
// <https://www.cse.unsw.edu.au/~cs1521/23T3/assignments/ass2/index.html>
//
// 2023-10-25   v1.0    Team COMP1521 <cs1521 at cse.unsw.edu.au>
// 
// This program was written by YOUR-NAME-HERE (YOUR-ZID-HERE) on DD/MM/2023.
// (COMPLETE THE ABOVE COMMENT AND REMOVE THIS LINE FOR FREE STYLE MARKS!)

//Style guide
//Comments above function name (for VSCODE compatibility)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tide.h"

//Included for uint32_t
#include <stdint.h> 

// Add any extra #defines here.
#define buffer_size 1024
#define max_string_size 1024

// Add any extra function signatures here.
int print_error_message(const char *message, int return_value);

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

//////////////////////////// SELF-DEFIUNED FUNCTIONS ///////////////////////////
int print_error_message(const char *message, int return_value) {
    fprintf(stderr, "%s", message);
    return return_value;
}

/////////////////////////////////// SUBSET 0 ///////////////////////////////////

/**
 * @brief Printing current directory of function
 * 
 * @param None
 * @returns None
 */
void print_current_directory(void) {
    char buffer[buffer_size];
    if(getcwd(buffer, buffer_size) != NULL) {
        printf("The current directory is: %s\n", buffer);
    } else {
        fprintf(stderr, "getcwd fail\n");
    }
}

/**
 * @brief Change the current directory to the given pathname and prints message
 * 
 * @param {char*} Directory
 * @return None
 */
void change_current_directory(char *directory) {
    char buffer[buffer_size];

    if(strcmp(directory, "~") == 0) {
        strcpy(buffer, getenv("HOME"));
    } else if (directory[0] == '~') {
        sprintf(buffer, "%s/%s", getenv("HOME"), &directory[2]);
    } else {
        strcpy(buffer, directory);
    }

    if(chdir(buffer) == -1) {
        fputs(MSG_ERROR_CHANGE_DIR, stdout);
    } else {
        printf("Moving to %s\n", buffer);
    }
}

/**
 * @brief List the contents of the current directory.
 * 
 * @param None
 * @return None
 */
void list_current_directory(void) {
    //Assume never fails as with assignment specifications
    DIR *dirp = opendir(".");

    struct dirent *de;
    char *file_names[1024];

    //readdir automatically goes through files until the end unordered
    int i = 0;
    while ((de = readdir(dirp)) != NULL) {
        file_names[i] = de->d_name;
        ++i;
    };

    sort_strings(file_names, i);

    for(int j = 0; j < i; ++j) {
        struct stat s;
        stat(file_names[j], &s);

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

        printf("\t");
        printf("%s\n", file_names[j]);
    }

    closedir(dirp);
}

/////////////////////////////////// SUBSET 1 ///////////////////////////////////

// Check whether the file meets the criteria to be encrypted.
bool is_encryptable(char *filename) {

    char *location = strrchr(filename, '/');
    char final_file_name[max_string_size];

    //final_file_name eventually becomes the just filename
    strcpy(final_file_name, filename);

    //Code inside if statement executes only if change directory is needed
    if(location != NULL) {
        uint32_t length_of_filepath = location - filename;

        char file_location[max_string_size];
        memcpy(file_location, filename, length_of_filepath);
        change_current_directory(file_location);

        //final_file_name originally had path, therefore change it
        strcpy(final_file_name, &filename[length_of_filepath + 1]);
    }

    struct stat s;
    if(stat(final_file_name, &s) != 0) {
        return print_error_message(MSG_ERROR_FILE_STAT, false);
    }

    // Check for directory, read and write permissions
    if((s.st_mode & S_IFREG) == 0) {
        return print_error_message(MSG_ERROR_DIRECTORY, false);
    }

    if((s.st_mode & S_IRGRP) == 0) {
        return print_error_message(MSG_ERROR_READ, false);
    }

    if((s.st_mode & S_IWGRP) == 0) {
        return print_error_message(MSG_ERROR_WRITE, false);
    }

    return true;
}

// XOR the contents of the given file with a set key, and write the result to
// a new file.
void xor_file_contents(char *src_filename, char *dest_filename) {

}
/////////////////////////////////// SUBSET 2 ///////////////////////////////////

// Search the current directory and its subdirectories for filenames containing
// the search string.
void search_by_filename(char *search_string) {
    printf("TODO: COMPLETE ME");
}

// Search the current directory and its subdirectories for files containing the
// provided search bytes.
void search_by_content(char *search_bytes, int size) {
    printf("TODO: COMPLETE ME");
}

/////////////////////////////////// SUBSET 3 ///////////////////////////////////

char *shift_encrypt(char *plaintext, char password[CIPHER_BLOCK_SIZE]) {
    // TODO: complete me
    return NULL;
}

char *shift_decrypt(char *ciphertext, char password[CIPHER_BLOCK_SIZE]) {
    // TODO: complete me
    return NULL;
}

void ecb_encryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    printf("TODO: COMPLETE ME");
}

void ecb_decryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    printf("TODO: COMPLETE ME");
}

/////////////////////////////////// SUBSET 4 ///////////////////////////////////

void cbc_encryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    printf("TODO: COMPLETE ME");
}

void cbc_decryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    printf("TODO: COMPLETE ME");
}

/////////////////////////////////// PROVIDED ///////////////////////////////////
// Some useful provided functions. Do NOT modify.

// Sort an array of strings in alphabetical order.
// strings:  the array of strings to sort
// count:    the number of strings in the array
// This function is to be provided to students.
void sort_strings(char *strings[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(strings[i], strings[j]) < 0) {
                char *temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
    }
}

// Sort an array of content_result_t in descending order of matches.
// results:  the array of pointers to content_result_t to sort
// count:    the number of pointers to content_result_t in the array
// This function is to be provided to students.
void sort_content_results(content_result *results[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (results[i]->matches > results[j]->matches) {
                content_result *temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            } else if (results[i]->matches == results[j]->matches) {
                // If the matches are equal, sort alphabetically.
                if (strcmp(results[i]->filename, results[j]->filename) < 0) {
                    content_result *temp = results[i];
                    results[i] = results[j];
                    results[j] = temp;
                }
            }
        }
    }
}

// Generate a random string of length RAND_STR_LEN.
// Requires a seed for the random number generator.
// The same seed will always generate the same string.
// The string contains only lowercase + uppercase letters,
// and digits 0 through 9.
// The string is returned in heap-allocated memory,
// and must be freed by the caller.
char *generate_random_string(int seed) {
    if (seed != 0) {
        srand(seed);
    }
    char *alpha_num_str =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    char *random_str = malloc(RAND_STR_LEN);

    for (int i = 0; i < RAND_STR_LEN; i++) {
        random_str[i] = alpha_num_str[rand() % (strlen(alpha_num_str) - 1)];
    }

    return random_str;
}
