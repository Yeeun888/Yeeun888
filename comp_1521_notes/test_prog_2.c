#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CIPHER_BLOCK_SIZE 16

void print16(char *array) {
    for (int i = 0; i < CIPHER_BLOCK_SIZE; ++i) {
        printf("%02x ", array[i]);
    }
    printf("\n");
}

char *shift_encrypt(const char *plaintext, const char password[CIPHER_BLOCK_SIZE]) {
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
        return_array[i] = current_char & 0xFF;
    }

    return return_array;
}

int main() {
    const char plaintext[CIPHER_BLOCK_SIZE] = "AAAABBBBCCCCDDDD";
    const char password[CIPHER_BLOCK_SIZE] = "passwordpassword";

    char *encrypted = shift_encrypt(plaintext, password);

    // Print the encrypted text
    print16(encrypted);

    free(encrypted); // Don't forget to free the allocated memory

    return 0;
}
