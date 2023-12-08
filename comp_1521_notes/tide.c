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
#define file_buffer_size sizeof(char) * 32768

// Add any extra function signatures here.
int print_error_message(const char *message, int return_value);

//Search by filename functions
void search_by_filename_recursive(char *search_string, int level, char *listings[]);
void add_files_and_permissions(char *file_name, int level, char *listings[]);
void sort_path(char *strings[], int count);
char *custom_strrchr(char *cp, int ch, int n);
void check_and_append_content_found(char *file_name, char *search_bytes, int size, content_result *files_found[], int level);

//Search by bytes functions
void search_by_content_recursive(char *search_bytes, int size, content_result *files_found[], int level);
void check_and_append_content_found(char *file_name, char *search_bytes, int size, content_result *files_found[], int level);

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

////////////////////////////////// ASSIGNMENT //////////////////////////////////

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

/**
 * @brief Checks whether a file is encryptable or not 
 * 
 * @param filename filename AT working directory 
 * @return true 
 * @return false 
 */
bool is_encryptable(char *filename) {
    struct stat s;
    if(stat(filename, &s) != 0) {
        printf(MSG_ERROR_FILE_STAT);
        return false;
    }

   // Check for directory, read and write permissions
    if (!S_ISREG(s.st_mode)) {
        printf(MSG_ERROR_DIRECTORY);
        return false;
    }
    if((s.st_mode & S_IRGRP) == 0) {
        printf(MSG_ERROR_READ);
        return false;
    }

    if((s.st_mode & S_IWGRP) == 0) {
        printf(MSG_ERROR_WRITE);
        return false;
    }

    return true;
}

/**
 * @brief XOR the contents of the given file with a set key, and write the 
 * restult to a new file 
 * 
 * @param src_filename source file name
 * @param dest_filename destination file name
 */
void xor_file_contents(char *src_filename, char *dest_filename) {
    FILE *original_file = fopen(src_filename, "r");
    FILE *new_file = fopen(dest_filename, "w");

    fseek(original_file, 0, SEEK_END);
    int original_file_size = ftell(original_file);
    fseek(original_file, 0, SEEK_SET);

    int i = 0;
    while(i < original_file_size) {
        fputc((fgetc(original_file) ^ XOR_BYTE_VALUE), new_file);
        ++i;
    }
    
    fclose(original_file);
    fclose(new_file);
}

// ⚠️ CAUTION: Beyond this point lies the abyss. Abandon all hope, ye who enter 
// here. The code that follows is a labyrinth of malevolent sorcery and cryptic 
// spells. Disturb it at your own risk, for consequences unknown shall befall 
// the foolhardy. May the programming gods have mercy on your soul. ⚔️🌑💀

/**
 * @brief Search directory and subdirectories for files based on filename
 * 
 * @param search_string 
 */
void search_by_filename(char *search_string) {
    if(strcmp(search_string, ".") == 0 || strcmp(search_string, "..") == 0) {
        printf("%s", MSG_ERROR_RESERVED);
        return;
    } 
    
    char *files_found[MAX_LISTINGS] = {NULL};
    search_by_filename_recursive(search_string, 0, files_found);

    int i = 0;
    while(files_found[i] != NULL) {
        ++i;
    }
    sort_path(files_found, i);

    printf("Found in %d filenames.\n", i);
    i = 0;
    while(files_found[i] != NULL) {
        printf("%s\n", files_found[i]);
        ++i;
    }

    i = 0;
    while(files_found[i] != NULL) {
        free(files_found[i]);
        ++i;
    }
}

/**
 * @brief Recursive function call for searching by filename. If found,
 * appends listings with filename and path (based on level)
 * 
 * @param search_string String to search
 * @param level Level of recursion
 * @param listings Pointer to array to append with list
 */
void search_by_filename_recursive(char *search_string, int level, char *listings[]) {
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
            if(strstr(de->d_name, search_string) != NULL) {
                add_files_and_permissions(de->d_name, level, listings);
            }
            chdir(de->d_name);
            search_by_filename_recursive(search_string, level + 1, listings);
            //Important to come back to original directory
            chdir("..");
        } else {
            if(strstr(de->d_name, search_string) != NULL) {
                add_files_and_permissions(de->d_name, level, listings);
            }
        }
    }

    closedir(dirp);
}

/**
 * @brief Adds permissions and path into a list of paths. Function works in the
 * CURRENT working directory. 
 * 
 * @param file_name File name in working directory. Also works with directories
 * @param level Level to format the working directory 
 * @param listings Pointer to array of listings / directories
 */
void add_files_and_permissions(char *file_name, int level, char *listings[]) {
    char buffer[buffer_size];
    struct stat file_stats;
    stat(file_name, &file_stats);

    char file_permissions[11];
    sprintf(file_permissions, "%s%s%s%s%s%s%s%s%s%s",
        ((S_ISDIR(file_stats.st_mode)) ? "d" : "-"),
        ((file_stats.st_mode & S_IRUSR) ? "r" : "-"),
        ((file_stats.st_mode & S_IWUSR) ? "w" : "-"),
        ((file_stats.st_mode & S_IXUSR) ? "x" : "-"),
        ((file_stats.st_mode & S_IRGRP) ? "r" : "-"),
        ((file_stats.st_mode & S_IWGRP) ? "w" : "-"),
        ((file_stats.st_mode & S_IXGRP) ? "x" : "-"),
        ((file_stats.st_mode & S_IROTH) ? "r" : "-"),
        ((file_stats.st_mode & S_IWOTH) ? "w" : "-"),
        ((file_stats.st_mode & S_IXOTH) ? "x" : "-") 
    );

    getcwd(buffer, buffer_size);

    char *final_ptr;
    char empty_string[] = "";
    if((final_ptr = custom_strrchr(buffer, '/', level)) == NULL) {
        final_ptr = empty_string;
    }

    int i = 0;
    while(listings[i] != NULL) {
        ++i;
    }

    listings[i] = malloc(sizeof(char) * max_string_size);
    sprintf(listings[i], "%s\t.%s/%s", file_permissions, final_ptr, file_name);
}

/**
 * @brief Takes a list of paths and sorts them based on filename
 * 
 * @param strings The pathnames
 * @param count Number of paths to sort
 */
void sort_path(char *strings[], int count) {
    //This function is a variant of the sort_strings function already given by
    //COMP1521, credit to them. 

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(strrchr(strings[i], '/'), strrchr(strings[j], '/')) < 0) {
                char *temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
    }
}

/**
 * @brief A custom variant of strrchr that returns the pointer of the n'th last
 * character.  
 * 
 * @param cp Pointer to the string
 * @param ch Character needed
 * @param n Number of character requied
 * @return char* 
 */
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

/**
 * @brief Search the current directory and subdirectory for files containing
 * bytes
 * 
 * @param search_bytes Bytes in *char array form
 * @param size Size of the array in serach_bytes
 */
void search_by_content(char *search_bytes, int size) {
    content_result *files_found[MAX_LISTINGS] = {NULL};

    search_by_content_recursive(search_bytes, size, &files_found, 0);

    int i = 0;
    while(files_found[i] != NULL) {
        i += 1;
    }

    sort_content_results(&files_found, i);
    if(i == 1) {
        printf("Found in %d file.\n", i);
    } else {
        printf("Found in %d files.\n", i);
    }

    i = 0;
    while(files_found[i] != NULL) {
        printf("%d: %s\n", files_found[i]->matches, files_found[i]->filename);
        i += 1;
    }

    i = 0;
    while(files_found[i] != NULL) {
        free(files_found[i]->filename);
        free(files_found[i]);
        i += 1;
    }
}

/**
 * @brief Search through files and appends their paths and names into 
 * files_found if bytes match
 * 
 * @param search_bytes Bytes to be found
 * @param size Size of search_bytes 
 * @param files_found Pointer to array to add
 * @param level Level of recursion. 
 */
void search_by_content_recursive(char *search_bytes, int size, content_result *files_found[], int level) {
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
            search_by_content_recursive(search_bytes, size, files_found, level+1);
            //Important to come back to original directory
            chdir("..");
        } else {
            check_and_append_content_found(de->d_name, search_bytes, size, files_found, level);
        }
    }

    closedir(dirp);
}

/**
 * @brief Check for bytes appends to files_found if so. 
 * 
 * @param file_name Filename
 * @param search_bytes Bytes to search for
 * @param size Size of search_bytes
 * @param files_found Pointer to array to append
 * @param level Level of recursion
 */
void check_and_append_content_found(char *file_name, char *search_bytes, int size, content_result *files_found[], int level) {
    FILE *fp = fopen(file_name, "r");

    if(fp == NULL) {
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    int fp_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Increase file_buffer_size to accomodate scanning larger files. 
    if(fp_size > file_buffer_size) {
        return;
    }

    char read_buffer[file_buffer_size];
    fread(read_buffer, 1, file_buffer_size, fp);

    int sb_found  = 0;
    for(int i = 0; i <= (fp_size - size); ++i) {
        for(int byte_index = 0; byte_index < size; ++byte_index) {
            if(read_buffer[byte_index + i] != search_bytes[byte_index]) {
                break;
            }

            //Code on the bottom always executes in the bottom where letters match
            if(byte_index == (size - 1)) {
                sb_found += 1;
            }
        }
    }

    if(sb_found == 0) {
        return;
    }

    char empty_string[] = "";
    char path_buffer[buffer_size];
    getcwd(path_buffer, buffer_size);
    char *final_path_string;
    if((final_path_string = custom_strrchr(path_buffer, '/', level)) == NULL) {
        final_path_string = empty_string;
    }

    //Iterate to get the index to add new content_result
    int ff_index = 0;
    while(files_found[ff_index] != NULL) {
        ff_index += 1;
    }

    files_found[ff_index] = malloc(sizeof(content_result));
    files_found[ff_index]->filename = malloc(sizeof(char) * max_string_size);
    sprintf(files_found[ff_index]->filename, ".%s/%s", final_path_string, file_name);
    files_found[ff_index]->matches = sb_found;

    fclose(fp);
}

/**
 * @brief Cyclic left shifts each bit of plaintext by each bit of password
 * 
 * @param plaintext Text to encrypt
 * @param password Password in plaintext
 * @return The encrypted string in char* form. 
 */
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

/**
 * @brief Cyclic right shifts each bit of plaintext by each bit of password
 * 
 * @param ciphertext Original cipher text
 * @param password Password
 * @return Returns decrypted plaintext
 */
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

/**
 * @brief Creates a new files of .ecb form which encrypts a file
 *
 * @param filename filename in WORKING DIRECTORY to be encrypted
 * @param password password to encrypt with
 */
void ecb_encryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    chmod(filename, 0777);
    FILE *read_fp = fopen(filename, "a+");

    if(read_fp == NULL) {
        printf("NULL FILE\n");
        return;
    }

    fseek(read_fp, 0, SEEK_END);
    int read_fp_size = ftell(read_fp);
    fseek(read_fp, 0, SEEK_SET);

    //Bytes padding
    int remaining_bytes = CIPHER_BLOCK_SIZE - (read_fp_size % CIPHER_BLOCK_SIZE);
    if(read_fp_size % CIPHER_BLOCK_SIZE != 0) {
        for(int i = 0; i < remaining_bytes; ++i) {
            char empty_char = 0;
            fputc(empty_char, read_fp);
        }
    }
    
    fseek(read_fp, 0, SEEK_SET);

    //Below operations are done when bytes are already padded
    char final_file_name[buffer_size];
    sprintf(final_file_name, "%s.ecb", filename);
    FILE *write_fp = fopen(final_file_name, "a");
    chmod(final_file_name, 0777);
    
    int count = 0;
    char char_buffer;
    char str_to_be_encrypted[CIPHER_BLOCK_SIZE];
    char *encrypted_string;

    while((char_buffer = fgetc(read_fp)) != EOF) {

        //Order of code is cruical in this function
        str_to_be_encrypted[count] = char_buffer;
        count += 1;

        if(count == CIPHER_BLOCK_SIZE) {
            encrypted_string = shift_encrypt(str_to_be_encrypted, password);
            count = 0;
            fwrite(encrypted_string, 1, CIPHER_BLOCK_SIZE, write_fp);
            free(encrypted_string);
        } 
    }  

    fclose(read_fp);
    fclose(write_fp);
}

/**
 * @brief Decrypts files encrypted with ECB algorithm above. Assumes files are
 * always multiple of 16 bytes. 
 * 
 * @param filename filename in WORKING DIRECTORY to be decrypted
 * @param password password to decrypt with
 */
void ecb_decryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    chmod(filename, 0777);
    FILE *read_fp = fopen(filename, "r");

    if(read_fp == NULL) {
        printf("NULL FILE\n");
        return;
    }

    fseek(read_fp, 0, SEEK_SET);

    //Below operations are done when bytes are already padded
    char final_file_name[buffer_size];
    sprintf(final_file_name, "%s.dec", filename);
    FILE *write_fp = fopen(final_file_name, "w+");
    chmod(final_file_name, 0777);
    
    int count = 0;
    char temp_char;
    char str_to_be_encrypted[CIPHER_BLOCK_SIZE];
    char *decrypted_string;

    while((temp_char = fgetc(read_fp)) != EOF) {

        //Order of code is cruical in this function
        str_to_be_encrypted[count] = temp_char;
        count += 1;

        if(count == CIPHER_BLOCK_SIZE) {
            decrypted_string = shift_decrypt(str_to_be_encrypted, password);
            count = 0;
            fwrite(decrypted_string, 1, CIPHER_BLOCK_SIZE, write_fp);
            free(decrypted_string);
        } 
    }  

    fclose(read_fp);
    fclose(write_fp);
}

/////////////////////////////////// SUBSET 4 ///////////////////////////////////

void cbc_encryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    chmod(filename, 0777);
    FILE *read_fp = fopen(filename, "a+");

    if(read_fp == NULL) {
        printf("NULL FILE\n");
        return;
    }

    fseek(read_fp, 0, SEEK_END);
    int read_fp_size = ftell(read_fp);
    fseek(read_fp, 0, SEEK_SET);

    //Bytes padding
    int remaining_bytes = CIPHER_BLOCK_SIZE - (read_fp_size % CIPHER_BLOCK_SIZE);
    if(read_fp_size % CIPHER_BLOCK_SIZE != 0) {
        for(int i = 0; i < remaining_bytes; ++i) {
            char empty_char = 0;
            fputc(empty_char, read_fp);
        }
    }
    
    fseek(read_fp, 0, SEEK_SET);

    //Below operations are done when bytes are already padded
    char final_file_name[buffer_size];
    sprintf(final_file_name, "%s.cbc", filename);
    FILE *write_fp = fopen(final_file_name, "a");
    chmod(final_file_name, 0777);
    
    int count = 0;
    char temp_char;
    char str_to_be_encrypted[CIPHER_BLOCK_SIZE];
    char *encrypted_string;
    char *initialization_vector = generate_random_string(1);

    while((temp_char = fgetc(read_fp)) != EOF) {

        //Order of code is cruical in this function
        str_to_be_encrypted[count] = temp_char;
        count += 1;

        if(count == CIPHER_BLOCK_SIZE) {
            //Add XOR operation before encrypting
            for(int xor_index = 0; xor_index < 16; xor_index += 1) {
                //XOR with initialization vector
                str_to_be_encrypted[xor_index] = (str_to_be_encrypted[xor_index] ^ initialization_vector[xor_index]);
            }
            
            encrypted_string = shift_encrypt(str_to_be_encrypted, password);
            count = 0;

            for(int xor_index = 0; xor_index < 16; xor_index += 1) {
                //Initialization vector = previous ciphertex
                initialization_vector[xor_index] = encrypted_string[xor_index];
            }

            fwrite(encrypted_string, 1, 16, write_fp);
            free(encrypted_string);
        } 
    }  

    fclose(read_fp);
    fclose(write_fp);
}

void cbc_decryption(char *filename, char password[CIPHER_BLOCK_SIZE]) {
    chmod(filename, 0777);
    FILE *read_fp = fopen(filename, "a+");

    if(read_fp == NULL) {
        printf("NULL FILE\n");
        return;
    }

    //Below operations are done when bytes are already padded
    char final_file_name[buffer_size];
    sprintf(final_file_name, "%s.dec", filename);
    FILE *write_fp = fopen(final_file_name, "a");
    chmod(final_file_name, 0777);
    
    int count = 0;
    char temp_char;
    char str_to_be_decrypted[CIPHER_BLOCK_SIZE];
    char *decrypted_string;
    char *initialization_vector = generate_random_string(1);

    while((temp_char = fgetc(read_fp)) != EOF) {

        //Order of code is cruical in this function
        str_to_be_decrypted[count] = temp_char;
        count += 1;

        if(count == CIPHER_BLOCK_SIZE) {
            //Add XOR operation
            
            decrypted_string = shift_decrypt(str_to_be_decrypted, password);
            count = 0;

            for(int xor_index = 0; xor_index < 16; xor_index += 1) {
                //XOR with initialization vector
                decrypted_string[xor_index] = (decrypted_string[xor_index] ^ initialization_vector[xor_index]);
            }

            for(int xor_index = 0; xor_index < 16; xor_index += 1) {
                //Initialization vector = previous ciphertex
                initialization_vector[xor_index] = str_to_be_decrypted[xor_index];
            }

            fwrite(decrypted_string, 1, 16, write_fp);
            free(decrypted_string);
        } 
    }  

    fclose(read_fp);
    fclose(write_fp);
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
