#include <stdio.h>
#include <stdlib.h>

void change_integer(int *test_int);
struct node{
    int data;
    struct node *next;
};

struct node create_node(int data, struct node *next) {
    struct node *temp_node = malloc(sizeof(struct node));
    temp_node->data = data;
    temp_node->next = next;
    return *temp_node;
}

void add_front(struct node *node_ptr) {
    struct node *temp_node = malloc(sizeof(struct node));
    *temp_node = *node_ptr;
    
    struct node *new_head = malloc(sizeof(struct node));
    new_head->data = 1;
    new_head->next = temp_node;
    *node_ptr = *new_head;
}

int main() {
    struct node *head_node = malloc(sizeof(struct node));
    head_node->data = 3;
    head_node->next = malloc(sizeof(struct node));
    head_node->next->data = 4;

    add_front(head_node);

    while (head_node != NULL) {
        printf("%d > ", head_node->data);
        head_node = head_node->next;
    }

    // int x = 5;
    // change_integer(&x);

    // printf("%d", x);
}

void change_integer(int *test_int) {
    *test_int = 2;
}   