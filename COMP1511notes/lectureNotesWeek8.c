#include <stdio.h>
#include <stdlib.h>

//*Code below is for generating a linked list
/**
 * linked list data structure
 * 
 * head node -> another node -> another node
 *  
 * access is done from the head to another node
 */

int main() {
    int array[5] = {1,2,3,4,5};

    array[1] = 3;
    
    printf("%d", *(array + 1));
}