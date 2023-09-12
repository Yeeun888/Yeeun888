// Program name
//
// This program was written by Maximus Philips Chan (z5457349)
// started on 27 July 2023. Finished on XX/XX/XX
// 
//
/** DESCRIPTION OF THE PRORGAM
 * This assignment will test your ability to create, use, manipulate and 
 * solve problems using linked lists. To do this, you will be implementing a 
 * bookshelf manager using linked lists of books and bookshelves.
 */

//Program notes, most of the comments in this program were styled with 
//colorful comments (extension ID: ParthR2031.colorful-comments). Install it
//and the program becomes more readable

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG_MEM_LEAK 0

////////////////////////////////////////////////////////////////////////////////
///////////////////////////      CONSTANTS      ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define MAX_STR_LEN 32
#define MAX_RATING 5
#define MIN_RATING 1

// Provided enums
enum book_genre {CLASSICS, FANTASY, MYSTERY, NON_FICTION, SCI_FI, INVALID};

//^ADDITIONAL DEFINED ENUMS

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct shelf {
    // the name of the shelf
    char name[MAX_STR_LEN];
    // pointer to the list of books on the shelf
    struct book *books;
    // pointer to the next shelf
    struct shelf *next;
};

struct book {
    // title of the book
    char title[MAX_STR_LEN];
    // author of the book
    char author[MAX_STR_LEN];
    // genre of the book
    enum book_genre genre;
    // rating of book out of 5
    int rating;
    // number of pages in the book
    int pages_count;
    // number of pages read
    int pages_read;

    struct book *next;
};

//^ADDITIONAL DEFINED STRUCTS

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void print_usage(void);
void print_book(struct book *book);
void scan_title_author(char title[MAX_STR_LEN], char author[MAX_STR_LEN]);
void scan_string(char string[MAX_STR_LEN]);
enum book_genre scan_genre(void);

void print_reading_stats(
    double average_rating,
    int total_read,
    int total_pages,
    enum book_genre longest_grouping,
    int grouping_length
);

void print_shelf_summary(
    int is_selected,
    int n,
    char name[MAX_STR_LEN],
    int num_books
);

void genre_to_string(enum book_genre genre, char genre_string[MAX_STR_LEN]);

// Additional provided function prototypes
// You won't need to use these functions!
// We use just them to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
enum book_genre string_to_genre(char *genre_str);

////////////////////////////////////////////////////////////////////////////////
//*                       YOUR FUNCTION PROTOTYPE  
////////////////////////////////////////////////////////////////////////////////

struct shelf *create_shelf(char name[MAX_STR_LEN]);

struct book *create_book(
    char title[MAX_STR_LEN],
    char author[MAX_STR_LEN],
    enum book_genre genre,
    int rating,
    int pages_count
);

//^ADDITIONAL FUNCTION PROTOTYPES
int command_loop(
    char command, 
    struct shelf *selected_shelf, 
    struct shelf *head_shelf,
    struct shelf **selected_shelf_address,
    struct shelf **head_shelf_address
);

//Below are functions that are part of the command loop
int append_books(struct shelf *head_shelf);
void print_books_on_shelf(struct shelf *my_shelf);
int count_books_on_shelf(struct shelf *head_shelf);
int check_append_errors(
    struct shelf *book_head_shelf,
    char title[MAX_STR_LEN],
    char author[MAX_STR_LEN],
    enum book_genre genre,
    int rating,
    int pages_count
);
int insert_book(struct shelf *head_shelf);
int read_book(struct shelf *head_shelf);
struct book *find_book(struct shelf *head_shelf, char title[MAX_STR_LEN], char author[MAX_STR_LEN]);
int reading_stats_for_shelf(struct shelf *head_shelf);
int insert_shelf(struct shelf *head_shelf, struct shelf **head_ptr, char name[MAX_STR_LEN]);
struct shelf *move_left(struct shelf *head_shelf, struct shelf *current_shelf);
struct shelf *move_right(struct shelf *head_shelf, struct shelf *current_shelf);
struct shelf *find_shelf(char name_of_shelf[MAX_STR_LEN], struct shelf *head_shelf);
void print_shelf(struct shelf *shelf_head, struct shelf *selected_shelf);
int delete_book(struct shelf *selected_shelf);
int delete_shelf(
    struct shelf *head_shelf, 
    struct shelf *selected_shelf,
    struct shelf **head_address,
    struct shelf **select_address
);
void free_shelf(struct shelf *shelf_name);
int create_genre_shelf(struct shelf *head_shelf, struct shelf **head_ptr);
int copy_book_onto_another_shelf(struct shelf *head_shelf, struct book *book); 
// int delete_book_on_shelf(struct shelf *head_shelf, struct book *book_ptr);
int delete_book_by_address(struct shelf *selected_shelf, struct book *delete_ptr);

//Not part of Command_loop
void debug(struct shelf *head_shelf, struct shelf *selected_shelf);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {

    printf("Welcome to Bookshelf Manager!\n");

    char command;
    printf("Enter command: ");

    //starting shelf passed on
    struct shelf *head_shelf = create_shelf("tbr"); 

    //selected shelf to start going out and about
    struct shelf *selected_shelf = head_shelf;

    while (scanf(" %c", &command) == 1) {
        command_loop(command, selected_shelf, head_shelf, &selected_shelf, &head_shelf);
        printf("Enter command: ");
    }
    
    printf("\nGoodbye\n");

    //Loop throughout the shelf to deallocate memory???
    while (head_shelf != NULL) {
        struct shelf *next_shelf = head_shelf->next;
        free_shelf(head_shelf);
        head_shelf = next_shelf;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//*                            YOUR FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//-------------------------- STAGE 1 FUNCTIONS ---------------------------------

// Command loop scans in characters before then using an if else chain
// Parameters: 
// 1. command - character indicating command given
// 2. head_shelf - address to the start

int command_loop(
    char command, 
    struct shelf *selected_shelf, 
    struct shelf *head_shelf,
    struct shelf **selected_shelf_address,
    struct shelf **head_shelf_address
) {
    //Function just starts the command loop. Exits the function when done.
    if (command == '?') {
        print_usage();
    } else if (command == 'a') {
        append_books(selected_shelf);
    } else if (command == 'p') {
        print_books_on_shelf(selected_shelf);
    } else if (command == 'c') {
        int count = count_books_on_shelf(selected_shelf);
        if (count == 0) {
            printf("There are no books on this shelf!\n");
        } else if (count == 1) {
            printf("There is 1 book on this shelf!\n");
        } else {
            printf("There are %d books on this shelf!\n", count);
        }
    } else if (command == 'i') {
        insert_book(selected_shelf);
    } else if (command == 'r') {
        read_book(selected_shelf);
    } else if (command == 's') {
        reading_stats_for_shelf(selected_shelf);
    } else if (command == 'A') {
        //Remember selected shelf
        char select_name[MAX_STR_LEN];
        strcpy(select_name, selected_shelf->name);

        char name[MAX_STR_LEN];
        scan_string(name);
        insert_shelf(head_shelf, head_shelf_address, name);

        *selected_shelf_address = find_shelf(select_name, head_shelf);
    } else if (command == '<') {
        *selected_shelf_address = move_left(head_shelf, selected_shelf);
        //selected_shelf = move_right(head_shelf, selected_shelf);
    } else if (command == '>') {
        *selected_shelf_address = move_right(head_shelf, selected_shelf);
        //selected_shelf = move_left(head_shelf, selected_shelf);
    } else if (command == 'P') {
        print_shelf(head_shelf, selected_shelf);
    } else if (command == 'd') {
        delete_book(selected_shelf);
    } else if (command == 'D') {
        delete_shelf(
            head_shelf, 
            selected_shelf, 
            head_shelf_address, 
            selected_shelf_address
        );
    } else if (command == 'G') {
        create_genre_shelf(head_shelf, head_shelf_address);
    } else if (command == 'z') {
        debug(head_shelf, selected_shelf);
    }

    return 0;
}

//Append books adds books into a shelf
//Parameters:
//1. Pointer to shelf
//Note: Functionality is inside function 
int append_books(struct shelf *head_shelf) {
    //Process of getting the data needed
    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    scan_title_author(title, author);

    enum book_genre genre = scan_genre();

    int rating;
    int page_count;
    scanf("%d %d", &rating, &page_count);

    //Check for errors
    if (check_append_errors(
        head_shelf, title, author, genre, rating, page_count) == 1) {
        return 0;
    }

    // Find a spot in the linked list;
    struct book *book_ptr = head_shelf->books;

    if (head_shelf->books == NULL) {
        head_shelf->books = create_book(title, author, genre, rating, page_count);
    } else { 
        //Look for a spot continously
        while (book_ptr->next != NULL) {
            book_ptr = book_ptr->next;
        }
        book_ptr->next = create_book(title, author, genre, rating, page_count);
    }

    printf("Book: '%s' added!\n", title);

    return 1;
}

//The function (no surprise) counts books on a shelf (who knew?)
//Parameters:
//1. Pointer to head of shelf
int count_books_on_shelf(struct shelf *head_shelf) {
    struct book *book_ptr = head_shelf->books;
    
    int count = 0;
    while (book_ptr != NULL) {
        count += 1;
        book_ptr = book_ptr->next;
    }

    return count;
}

//Prints books on shelf
void print_books_on_shelf(struct shelf *my_shelf) {
    //Handle NULL books
    if (my_shelf->books == NULL) {
        printf("There are no books on this shelf!\n");
    }

    //Non null books
    struct book *book_ptr = my_shelf->books;
    while (book_ptr != NULL) {
        print_book(book_ptr);
        book_ptr = book_ptr->next;
    }
}

//Creates a shelf by receiving the shelf name
struct shelf *create_shelf(char name[MAX_STR_LEN]) {
    //Creates temporary shelf ptr
    struct shelf *temp_shelf_ptr;
    temp_shelf_ptr = (struct shelf *) malloc(sizeof(struct shelf));
    //Copy name into pointer
    strcpy(temp_shelf_ptr->name, name); 
    temp_shelf_ptr->books = NULL;
    temp_shelf_ptr->next = NULL;
    return temp_shelf_ptr;
}

//Adds books onto a shelf
//Takes in all the valid parameters to create a book
//Note: Some values are intiailized by the funciton instead of the function call
//such as the pages_read. 
struct book *create_book(
    char title[MAX_STR_LEN],
    char author[MAX_STR_LEN],
    enum book_genre genre,
    int rating,
    int pages_count
) {
    struct book *temp_book_ptr;
    temp_book_ptr = (struct book *) malloc(sizeof(struct book));
    strcpy(temp_book_ptr->title, title);
    strcpy(temp_book_ptr->author, author);
    temp_book_ptr->genre = genre;
    temp_book_ptr->rating = rating;
    temp_book_ptr->pages_count = pages_count;
    temp_book_ptr->pages_read = 0;
    temp_book_ptr->next = NULL; 

    return temp_book_ptr;
}

//------------------------- STAGE 2 FUNCTIONS ----------------------------------

//Function checks for append errors
//Parameters are head_shelf pointer and parts of the book
//Note that the function call here returns:
//  1 - Signifies TRUE e.g. there are errors
//  0 - Signifies FALSE e.g. no errors
int check_append_errors(
    struct shelf *book_head_shelf,
    char title[MAX_STR_LEN],
    char author[MAX_STR_LEN],
    enum book_genre genre,
    int rating,
    int pages_count
) {
    //Note: Passing a full book using malloc would leave the object lost in 
    //memory hence why many parameters are used
    
    if (genre == INVALID) {
        printf("ERROR: Invalid book genre\n");
        return 1;
    }

    if (rating <= 0 || rating > 5) {
        printf("ERROR: Rating should be between 1 and 5\n");
        return 1;
    }

    if (pages_count <= 0) {
        printf("ERROR: Page count should be positive\n");
        return 1;
    } 

    //Search for book
    struct book *book_ptr = book_head_shelf->books;
    while (book_ptr != NULL) {
        if (strcmp(title,book_ptr->title) == 0 &&
        strcmp(author, book_ptr->author) == 0
        ) {
            printf("ERROR: a book with title: '%s' by '%s'", title, author);
            printf(" already exists in this shelf\n");
            return 1;
        }
        book_ptr = book_ptr->next;
    }

    return 0;
}

int insert_book(struct shelf *head_shelf) {
    int book_index;
    scanf("%d", &book_index);

    //Process of getting the data needed
    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    scan_title_author(title, author);

    enum book_genre genre = scan_genre();

    int rating;
    int page_count;
    scanf("%d %d", &rating, &page_count);

    //Check for errors
    //Append errors
    if (check_append_errors(
        head_shelf, title, author, genre, rating, page_count) == 1) {
        return 0;
    }
    //Check is position is more than 0
    if (!(book_index >= 0)) {
        printf("ERROR: n must be at least 0\n");
        return 1;
    }

    //Real code starts below

    //If n = 0
    if (book_index == 0) {
        struct book *temp_ptr = head_shelf->books;
        head_shelf->books = create_book(title, author, genre, rating, page_count);
        head_shelf->books->next = temp_ptr;
        printf("Book: '%s' inserted!\n", &title[0]);
        return 1;
    }

    //Where n > 0
    struct book *header = head_shelf->books;
    struct book *previous_book = head_shelf->books;

    for(int iterator = 0; iterator < book_index; ++iterator) {
        if (header == NULL) {
            break; 
        }
        previous_book = header;
        header = header->next;
    }

    if (previous_book == NULL) {
        //Indicates that the array started empty
        head_shelf->books = create_book(title, author, genre, rating, page_count);
        printf("Book: '%s' inserted!\n", &title[0]);
        return 1;
    }

    previous_book->next = create_book(title, author, genre, rating, page_count);
    previous_book->next->next = header;
    printf("Book: '%s' inserted!\n", &title[0]);

    return 1;
}

int read_book(struct shelf *head_shelf) {
    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    scan_title_author(title, author);

    int pages_read;
    scanf("%d", &pages_read);

    //Error checking
    if (!(pages_read > 0)) {
        printf("ERROR: n must be a positive integer\n");
        return 0;
    }

    //Loop through the linked list to find matching title and author
    struct book *modified_book = find_book(head_shelf, title, author);
    if (modified_book == NULL) {
        printf("ERROR: No book '%s' by '%s' exists\n", title, author);
        return 0;
    } else {
        //Book exists
        //Check if the pages left are enough
        if (pages_read > (modified_book->pages_count - modified_book->pages_read)) {
            printf("ERROR: cannot read %d pages, there are only %d left to read\n",
            pages_read, modified_book->pages_count - modified_book->pages_read);
            return 0;
        } else {
            //Book exists and there are enough pages
            modified_book->pages_read += pages_read;
            printf("Pages read for '%s' has been increased by %d\n", title, pages_read);
            return 1;
        }
    }
}

struct book *find_book(
    struct shelf *head_shelf, 
    char title[MAX_STR_LEN], 
    char author[MAX_STR_LEN]) 
{
    struct book *book_ptr = head_shelf->books;
    while (book_ptr != NULL) {
        //If a match has been found then take action
        if (strcmp(title, book_ptr->title) == 0 &&
        strcmp(author, book_ptr->author) == 0) {
            return book_ptr;
        }

        book_ptr = book_ptr->next;
    }

    //Return NULL indicating there is nothing
    return NULL; 
}

int reading_stats_for_shelf(struct shelf *head_shelf) {

    int total_books = 0;
    int total_rating = 0;
    int total_read_pages = 0;
    int total_total_pages = 0;
    int book_grouping[5] = {0, 0, 0, 0, 0};

    struct book *book_ptr = head_shelf->books;

    //Error checking
    if (book_ptr == NULL) {
        printf("No books on this shelf, so no stats to display!\n");
        return 0;
    }

    //If no errors, loop through the shelf and update the stats
    while (book_ptr != NULL) {
        total_books += 1;
        total_rating += book_ptr->rating;
        total_read_pages += book_ptr->pages_read;
        total_total_pages += book_ptr->pages_count;
        book_grouping[book_ptr->genre] += 1;

        book_ptr = book_ptr->next;
    }

    //Find largest element
    int largest_genre = -1;
    int number_of_books_in_largest_genre = 0;

    //Find largest book grouping
    for(int iterator = 0; iterator < 5; ++iterator) {
        if (book_grouping[iterator] >= number_of_books_in_largest_genre) {
            largest_genre = iterator;
            number_of_books_in_largest_genre = book_grouping[iterator];
        }
    }

    //Process stats
    double average_rating = (double) total_rating / (double) total_books;

    print_reading_stats(average_rating, total_read_pages, total_total_pages, 
    largest_genre, number_of_books_in_largest_genre);

    return 1;
}

//-------------------------- STAGE 3 FUNCTIONS ---------------------------------

//To be honest I don't know why I wrote this function it probably doesn't work
//You've probably figured out by now I didn't read the instrucitons before
//doing stage 3.1

// //Function return -1 if the strings are completely identical
// //Function returns 0 if the string is alphabetically smaller
// //Function return 1 if the string is alphabetically larger
// int is_alphabetically_larger(char string[MAX_STR_LEN], char comp[MAX_STR_LEN]) {
//     //Use the smallest number
//     int smallest_num_chars = 0;
//     if (strlen(string) > strlen(comp)) {
//         smallest_num_chars = strlen(comp);
//     } else if (strlen(string) < strlen(comp)){
//         smallest_num_chars = strlen(string);
//     } else {
//         //indicating they are equal length
//         smallest_num_chars = strlen(string);
//     }

//     for(int i = 0; i < smallest_num_chars; ++i) {
//         if (string[i] > comp[i]) {
//             return 1;
//         } else if (string[i] < comp[i]) {
//             return 0;
//         }
//     }

//     //If the strings are completely identical
//     return -1;
// }

void debug(struct shelf *head_shelf, struct shelf *selected_shelf) {
    struct shelf *original_head = head_shelf;
    while (head_shelf != NULL) {
        printf("%s > ", head_shelf->name);
        head_shelf = head_shelf->next;
    }
    printf("\n");
    printf("head: %s, selected: %s\n", original_head->name, selected_shelf->name);
}

//THIS FUNCTION IS A WORK OF ARTTTTTTT
//Function returns 1 for successful additions into the list
//Function takes in head_shelf as the pointer and the name;
int insert_shelf(
    struct shelf *head_shelf, 
    struct shelf **head_ptr, 
    char name[MAX_STR_LEN]
) {
    //Check if other shelves with same name exist
    struct shelf *iterator_ptr = head_shelf;
    while (iterator_ptr != NULL) {
        if (strcmp(iterator_ptr->name, name) == 0) {
            printf("ERROR: a shelf with name '%s' already exists\n", name);
            return 0;
        }
        iterator_ptr = iterator_ptr->next;
    }

    //Check if name is smaller than front
    if (strcmp(name, head_shelf->name) < 0) {

        struct shelf *temp_shelf = create_shelf(name);
        temp_shelf->next = head_shelf;
        *head_ptr = temp_shelf;

        return 1;
    }

    //Go around the shelf linked list to add more shelves
    while (head_shelf->next != NULL) {
        //If name is smaller than the next item it implies that
        //the item before it, must be larger (as the shelf is inorder);
        if (strcmp(name, head_shelf->next->name) < 0) { 
            struct shelf *new_shelf = create_shelf(name);
            new_shelf->next = head_shelf->next;
            new_shelf->books = NULL;
            head_shelf->next = new_shelf;

            return 1;
        }

        head_shelf = head_shelf->next;
    }

    //head_shelf->next is already NULL;
    head_shelf->next = create_shelf(name);

    return 1;
}

//Function exists to path bugs in the previous function;
struct shelf *find_shelf(char name_of_shelf[MAX_STR_LEN], struct shelf *head_shelf) {
    while (head_shelf != NULL) {
        if (strcmp(name_of_shelf, head_shelf->name) == 0) {
            return head_shelf;
        }
        head_shelf = head_shelf->next;
    }

    return NULL;
}

struct shelf *move_left(struct shelf *head_shelf, struct shelf *current_shelf) {
    if (current_shelf == head_shelf) {
        //Loop to the end 
        while (head_shelf->next != NULL) {
            head_shelf = head_shelf->next;
        }

        return head_shelf;
    } else {
        while (head_shelf->next != current_shelf) {
            head_shelf = head_shelf->next;
        }

        return head_shelf;
    }
}

struct shelf *move_right(struct shelf *head_shelf, struct shelf *current_shelf) {
    struct shelf *shelf_ptr = current_shelf;
    if (shelf_ptr->next == NULL) {
        return head_shelf;
    } else {
        return shelf_ptr->next;
    }
}

void print_shelf(struct shelf *shelf_head, struct shelf *selected_shelf) {
    //Loop through the entire linked list

    int counter = 0;
    while (shelf_head != NULL) {
        print_shelf_summary(
            shelf_head == selected_shelf,
            counter, 
            shelf_head->name, 
            count_books_on_shelf(shelf_head)
        );
        counter += 1;
        shelf_head = shelf_head->next;
    }
}



//Clarification: Search only the shelf NOT all shelves
int delete_book(struct shelf *selected_shelf) {
    char author[MAX_STR_LEN];
    char title[MAX_STR_LEN];

    scan_title_author(title, author);

    struct book *prev_ptr = selected_shelf->books;
    struct book *book_ptr = selected_shelf->books;
    while (book_ptr != NULL) {
        if (
            strcmp(book_ptr->author, author) == 0 &&
            strcmp(book_ptr->title, title) == 0
        ) {
            //Edge case for first book
            if (book_ptr == selected_shelf->books) {
                selected_shelf->books = selected_shelf->books->next;
                return 1;
            }
            
            prev_ptr->next = book_ptr->next;
            free(book_ptr);

            return 1;
        }

        prev_ptr = book_ptr;
        book_ptr = book_ptr->next;
    }
    printf("ERROR: No book '%s' by '%s' exists\n", title, author);

    return 0;
}

void free_shelf(struct shelf *shelf_name) {
    struct book *book_ptr = shelf_name->books;
    while (book_ptr != NULL) {
        struct book *temp_ptr = book_ptr->next;
        //printf("Free book: %s\n", book_ptr->title);
        free(book_ptr);
        book_ptr = temp_ptr;
    }

    //printf("Free Shelf: %s\n", shelf_name->name);
    free(shelf_name);
}

//Returns the new selected shelf
int delete_shelf(
    struct shelf *head_shelf, 
    struct shelf *selected_shelf,
    struct shelf **head_address,
    struct shelf **select_address
) {
    //If head_shelf is same as selected_shelf 
    if (head_shelf == selected_shelf) {
        *head_address = head_shelf->next;
        *select_address = head_shelf->next;
        free_shelf(head_shelf);

        if (*head_address == NULL) {
            *head_address = create_shelf("tbr");
            *select_address = *head_address;
        }

        return 1;
    }

    //If not the first one, loop through the linked list
    while (head_shelf != NULL) {
        if (head_shelf->next == selected_shelf) {
            head_shelf->next = selected_shelf->next;
            *select_address = head_shelf;
            free_shelf(selected_shelf);
            return 1;
        }

        head_shelf = head_shelf->next;
    }

    //Check if head_address is NULL and create a new shelf accordingly?
    return 0;
}

//-------------------------   STAGE 4 FUNCTIONS   ------------------------------

int create_genre_shelf(struct shelf *head_shelf, struct shelf **head_ptr) {
    //BUGS NOTE:
    //If the inserted shelf is later INFRONT OF THE HEAD, the *head_shelf
    //will be behind the real head. Therefore do all the code likewise

    enum book_genre input_genre;
    input_genre = scan_genre();


    char genre_name[MAX_STR_LEN];
    genre_to_string(input_genre, genre_name);

    //Tiny loop to change name
    for(int i = 0; i < strlen(genre_name); ++i) {
        genre_name[i] = tolower(genre_name[i]);
    }

    //Check for errors
    if (input_genre == INVALID) {
        printf("ERROR: Invalid book genre\n");
        return 1;
    } else {
        //Check for same name
        if (find_shelf(genre_name, head_shelf) != NULL) {
            printf("ERROR: a shelf with name '%s' already exists\n", genre_name);
            return 1;
        }
    }

    //Make a shelf of genre_name
    insert_shelf(head_shelf, head_ptr, genre_name);
    head_shelf = *head_ptr;
    //Get the shelf memory location
    struct shelf *genre_shelf_ptr = find_shelf(genre_name, head_shelf);

    //printf("%s\n", genre_shelf_ptr->name);

    //Code goes through all shelves and their books
    while (head_shelf != NULL) {
        struct book *book_ptr = head_shelf->books;

        while (book_ptr != NULL) {
            if (book_ptr->genre == input_genre) {
                //printf("%s\n", book_ptr->title);
                //Insert book into the shelf
                copy_book_onto_another_shelf(genre_shelf_ptr, book_ptr);

                // delete book from previous shelf
                // delete_book_on_shelf(head_shelf, book_ptr);
                // delete_book_by_address(head_shelf, book_ptr);
            }

            book_ptr = book_ptr->next;
        }

        head_shelf = head_shelf->next;
    }

    //Reset head_shelf to the start
    head_shelf = *head_ptr;
    while (head_shelf != NULL) {
        //If it is genre shelf skip it. We don't want to delete books from this shelf
        #if DEBUG_MEM_LEAK
        printf("In shelf %s\n", head_shelf->name);
        #endif

        if (strcmp(head_shelf->name, genre_name) == 0) {
            //skip and go
            head_shelf = head_shelf->next;
            continue;
        }

        struct book *book_ptr = head_shelf->books;
        while (book_ptr != NULL) {
            
            if (book_ptr->genre == input_genre) {
                // delete book from previous shelf
                // delete_book_on_shelf(head_shelf, book_ptr);
                struct book *temp_ptr = book_ptr;
                book_ptr = book_ptr->next;

                delete_book_by_address(head_shelf, temp_ptr);
                
                //CONTINUE EXISTS SUCH THAT THE LINE BELOW THE IF STATEMENT
                //DOES NOT EXECUTE
                continue;
            }

            book_ptr = book_ptr->next;
        }

        head_shelf = head_shelf->next;
    } 

    return 1;
}

//Appends a book another another shelf based on another book
int copy_book_onto_another_shelf(struct shelf *head_shelf, struct book *book) {
    struct book *book_ptr = head_shelf->books;

    //Attempt to find book
    struct book *prev_book = find_book(head_shelf, book->title, book->author);

    //If a previous book is found then,
    if (prev_book != NULL) {
        if (book->pages_read > prev_book->pages_read) {
            prev_book->pages_read = book->pages_read;
            return 1;
        } else {
            //No modification is made
            return 0;
        } 
    }

    if (head_shelf->books == NULL) {
        head_shelf->books = create_book(book->title, book->author, 
        book->genre, book->rating, book->pages_count);
        return 1;
    } else { 
        //Loop until the last book such that the book_ptr->next is NULL;
        while (book_ptr->next != NULL) {
            book_ptr = book_ptr->next;
        }

        book_ptr->next = create_book(book->title, book->author, book->genre, 
        book->rating, book->pages_count);
        return 1;
    }
}

//Both functions do the same thing
int delete_book_by_address(struct shelf *selected_shelf, struct book *delete_ptr) {
    struct book *prev_ptr = selected_shelf->books;
    struct book *book_ptr = selected_shelf->books;

    while (book_ptr != NULL) {
        if (book_ptr == delete_ptr) {
            //Edge case if book_ptr is the first book
            if (book_ptr == selected_shelf->books) {
                struct book *temp_ptr = selected_shelf->books;
                selected_shelf->books = selected_shelf->books->next;
                free(temp_ptr); 
                return 1;
            } 

            prev_ptr->next = book_ptr->next;
            
            #if DEBUG_MEM_LEAK
            
            printf("Free book: %s\n", book_ptr->title);

            #endif

            free(book_ptr);
            return 1;
        }

        prev_ptr = book_ptr;
        book_ptr = book_ptr->next;
    }

    return 1;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////  PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Prints the Bookshelf Manager usage instructions,
// displaying the different commands and their arguments.
//
void print_usage(void) {
    printf(
        "=====================[  Bookshelf Manager ]=====================\n"
        "      ===============[     Usage Info     ]===============      \n"
        "  ?                                                             \n"
        "    Show help                                                   \n"
        "  a [title] [author] [genre] [rating] [pages_count]             \n"
        "    Add a book to the shelf                                     \n"
        "  p                                                             \n"
        "    Print out all of the books on the shelf                     \n"
        "  c                                                             \n"
        "    Count all of the books on the shelf                         \n"
        "                                                                \n"
        "  i [n] [title] [author] [genre] [rating] [page_count]          \n"
        "    Insert a book into the shelf at position `n`                \n"
        "  r [title] [author] [n]                                        \n"
        "    Read `n` pages of the book with matching `title` and        \n"
        "    `author`                                                    \n"
        "  s                                                             \n"
        "    Display the reading stats                                   \n"
        "                                                                \n"
        "  A [name]                                                      \n"
        "    Add a new empty shelf in alphabetical order                 \n"
        "  >                                                             \n"
        "    Select the next shelf in the shelf list.                    \n"
        "  <                                                             \n"
        "    Select the previous shelf in the shelf list.                \n"
        "  P                                                             \n"
        "    Print out the shelves list                                  \n"
        "  d [title] [author]                                            \n"
        "    Delete book with matching `title` and `author` from         \n"
        "    the selected shelf.                                         \n"
        "  D                                                             \n"
        "    Remove the selected shelf.                                  \n"
        "                                                                \n"
        "  G [genre]                                                     \n"
        "    Create a new shelf with all the books of `genre`            \n"
        "  S [pattern]                                                   \n"
        "    Search for titles that match `pattern` across all shelves   \n"
        "================================================================\n"
    );
}

// Formats and prints out a book struct,
//
// Parameters:
//      book - The struct book to print.
// 
void print_book(struct book *book) {
    char genre_string[MAX_STR_LEN];
    genre_to_string(book->genre, genre_string);

    printf(" ---------------------------------- \n");
    printf("| %-32s |\n", book->title);
    printf("| %-32s |\n", book->author);
    printf("| %-32s |\n", genre_string);
    printf("| Rating: %d/%d     Pages: %4d/%4d |\n", 
            book->rating, MAX_RATING, book->pages_read, book->pages_count);
    printf(" -----------------V---------------- \n");
}


// Scan in the title and authors strings into the provided char array, placing 
// '\0' at the end.
//
// Parameters:
//      title  - a char array of length MAX_STR_LEN, which will be used
//              to store the title.
//      author - a char array of length MAX_STR_LEN, which will be used
//              to store the author.
// 
// Usage: 
// ```
//      char title[MAX_STR_LEN];
//      char author[MAX_STR_LEN];
//      scan_title_author(title, author);
// ```
void scan_title_author(
    char title[MAX_STR_LEN],
    char author[MAX_STR_LEN]
) {
    scan_token(title, MAX_STR_LEN);
    scan_token(author, MAX_STR_LEN);
}

// Scan in a string into the provided char array, placing '\0' at the end.
//
// Parameters:
//      string  - a char array of length MAX_STR_LEN, which will be used
//              to store the string.
//
// Usage: 
// ```
//      char string[MAX_STR_LEN];
//      scan_string(string);
// ```
void scan_string(char string[MAX_STR_LEN]) {
    scan_token(string, MAX_STR_LEN);
}

// Scans a string and converts it to a genre.
//
// Returns:
//      The corresponding genre, if the string was valid,
//      Otherwise, returns INVALID.
// 
// Usage: 
// ```
//      enum genre genre = scan_genre();
// ```
//
enum book_genre scan_genre(void) {
    char genre[MAX_STR_LEN];
    scan_token(genre, MAX_STR_LEN);
    return string_to_genre(genre);
}

// Formats and prints out the reading statistics
//
// Parameters:
//      average_rating  - The average rating of all books in selected shelf
//      total_read      - The total pages read for books on selected shelf.
//      total_pages     - The total pages for books on selected shelf.
//      longest_grouping  - The longest grouping of adjacent genres
//      grouping_length  - The length of the longest genre grouping
//
void print_reading_stats(
    double average_rating,
    int total_read,
    int total_pages,
    enum book_genre longest_grouping,
    int grouping_length
) {
    char genre_name[MAX_STR_LEN];
    genre_to_string(longest_grouping, genre_name);
    printf("  Average Rating    :  %.2lf / %d\n", average_rating, MAX_RATING);
    printf("  Pages Read        : %5d / %5d\n", total_read, total_pages);
    printf("  Longest Grouping  : %s of length %d\n", 
            genre_name, grouping_length);
}

// Formats and prints out various information about a given shelf.
//
// Parameters:
//      is_selected - 1, if this shelf is the currently selected shelf, 
//                    0, otherwise.
//      n           - The position of the given shelf in the list of shelves, 
//                    starting from 0.
//      name        - The name of the given shelf.
//      num_books   - The number of books in the given shelf.
//
void print_shelf_summary(
    int is_selected, 
    int n, 
    char name[MAX_STR_LEN],
    int num_books
) {
    printf("     ---------------------------------- \n");
    printf("    | Shelf: %-25d |\n", n);

    if (is_selected) {
        printf("--->");
    } else {
        printf("    ");
    }

    printf("| %-32s |\n", name);
    printf("    | Books: %-25d |\n", num_books);
    printf("     -----------------V---------------- \n");
}

// Get a string from an enum book_genre
// 
// Parameters:
//      genre           - the genre to be converted to a string
//      genre_string    - the char array the name of genre should be written to
//
void genre_to_string(enum book_genre genre, char genre_string[MAX_STR_LEN]) {
    if (genre == CLASSICS) {
        strcpy(genre_string, "CLASSICS");
    } else if (genre == FANTASY) {
        strcpy(genre_string, "FANTASY");
    } else if (genre == MYSTERY) {
        strcpy(genre_string, "MYSTERY");
    } else if (genre == NON_FICTION) {
        strcpy(genre_string, "NON_FICTION");
    } else if (genre == SCI_FI) {
        strcpy(genre_string, "SCI_FI");
    } else {
        strcpy(genre_string, "INVALID");
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////// ADDITIONAL PROVIDED FUNCTIONS ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

// Convert a string into an enum book_genre
// 
// Parameters:
//      genre_str   - a string version of the genre
// Returns:
//      enum book_genre
//
enum book_genre string_to_genre(char *genre_str) {
    int len = strlen(genre_str);

    if (strncasecmp(genre_str, "classics", len) == 0) {
        return CLASSICS;
    } 
    if (strncasecmp(genre_str, "fantasy", len) == 0) {
        return FANTASY;
    } 
    if (strncasecmp(genre_str, "mystery", len) == 0) {
        return MYSTERY;
    }
    if (strncasecmp(genre_str, "non_fiction", len) == 0) {
        return NON_FICTION;
    } 
    if (strncasecmp(genre_str, "sci_fi", len) == 0) {
        return SCI_FI;
    } 

    return INVALID;
}

// Scan a token into the provided buffer of buffer_size
// 
// Parameters:
//      buffer      - the buffer being scanned into
//      buffer_size - the size of buffer
// Returns:
//      the number of chars scanned
//
int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    // consume all leading whitespace
    scanf(" ");

    // Scan in characters until whitespace
    while (i < buffer_size - 1
        && (num_scanned = scanf("%c", &c)) == 1 
        && !isspace(c)) {

        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}
