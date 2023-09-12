// CS Carpark
//
// This program was written by Maximus Philips Chan (z5457349)
// on 10 JUly 2023
//
// CS Carpark is a COMP1511 assignment designed for managing a carpark system
// It comes with many features such as adding cars, modifying carpark types,
// etc. Below is a demonstration of the program

//Pre-coding notes for CS1511:
//ALL variables/functions are done in snake case

#include <stdio.h>
#include <math.h>

// TODO: REMOVE LATER
#include<unistd.h>

// Provided constants
#define CARPARK_ROWS 8
#define CARPARK_COLUMNS 6
#define MAX_DATABASE 1024 //If you just want to mathematically maxout the program, use 10000. 

#define NORMAL_PARKING_RATE 10

#define EMPTY -1

// Your constants here 

// Provided enums
enum space_type {
    NORMAL,
    PREMIUM,
    CARWASH_BAY,
    ELECTRIC_CHARGING_STATION,
};

#define LEAVE 4 //Leave is used as an enum. Due to how the code is written,
                //adding more enums to space_type creates errors. so LEAVE is a
                //constant that replaces 4

// Provided structs             //Electric notes
struct car_space {
    enum space_type type;       //Electric charging station 
    int parking_rate;           //not used
    int licence_plate;          //Cable length
    int occupied_since;         //If occupied or not
    int total_bill;             //Charge time end
    int original_arrival_time;
};

struct coordinate {
    int row;
    int col;
};

// enum activities {
//     NONE, 
//     NORMAL_PARKING,
//     PREMIUM_PARKING,
//     CAR_WASH,
//     CHARGING,
//     LEFT
// };

struct history {
    int plate_number;
    int charging_time[2];
    int charger_coordinates[2];
    int row_coordinates[24];
    int column_coordinates[24];
    int activity[24];
};

enum charger_function{
    DIAGONAL,
    CHARGER_ROW,
    CHARGER_COLUMN
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//* FUNCTION PROTOTYPES HERE

//plates refer to license plates 
int find_plate(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int find_plate_column(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int find_plate_row(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

int out_of_bound(int row, int column);
void park_car(int target_license_plate, int row, int column, int time_of_entry, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int print_spaces_available(int type_of_space, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int checkout_of_parking(int license_plate_target, int row, int column, int check_out_time, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], struct history history_database[MAX_DATABASE]);
int build_charger(int electric_row, int electric_col, int build_time, int cable_length, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void get_charger(int license_plate_target, int target_row, int target_column, int charge_time_start, int charge_time_end, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], struct history history_database[MAX_DATABASE]);
void move_car(int license_plate_target, int target_row, int target_column, int new_row, int new_col, int time_of_move, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

float find_diagonal(int x1, int x2, int y1, int y2);

//Carwash related functions
int check_carwash_bounds(int wash_row, int wash_col, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int find_non_adjacent_to_car_wash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);

//history and database functions
void initialize_database(struct history history_database[MAX_DATABASE]);
void add_database(int plate_number, int activity, int time, int row, int column, struct history history_database[MAX_DATABASE]);
void add_power(int plate_number, int start_time, int end_time, int charger_row, int charger_col, struct history history_database[MAX_DATABASE]);
void print_history(int row, int column, int activity);
int search_databse(int plate_number, struct history history_database[MAX_DATABASE]);
int find_non_negative(int array[24]);

//BFS
int search_for_exit(int start_row, int start_col, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int is_solid_block(int row, int column, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_array(int array[8][6]);

//Fix later if available time
// void add_activity(int plate_number, int activity, int start_time, int end_time, struct history history_database[MAX_DATABASE]);

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_car_space(struct car_space space);

int main(void) {
    //---------------------------- SETUP CODE ----------------------------------

    // Set up carpark. `carpark` is a 2D array of `struct car_space`s. 
    // It is `CARPARK_ROWS` x `CARPARK_COLUMNS` in size (which is 8 x 6 for this
    // assignment).
    struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS];

    // This will initialise all spaces in the carpark as NORMAL spaces which are 
    // all EMPTY.
    initialise_carpark(carpark);

    //Create a struct AND initialize an array size 1024 to store history data
    struct history history_database[MAX_DATABASE];
    initialize_database(history_database);

    // reserved for premium parking. The carpark should be printed once premium
    // parking is reserved.

    printf("Welcome to CS Carpark!\n\n");
    printf("Which row of the carpark would you like to reserve for premium parking? ");
    
    int premium_row;
    scanf("%d", &premium_row);

    for(int a = 0; a < CARPARK_COLUMNS; ++a) { //Note: Magic variable used for trivial for loop
        carpark[premium_row][a].type = PREMIUM; 
        carpark[premium_row][a].parking_rate = 50;
    }

    print_carpark(carpark);

    //Asks to add cars from the user.
    //Assumptions for code: 
    /**
     * 1. License plate is a 4 digit integer
     * 2. All cars have an entry time of zero 
     * 3. Invalid cars must be ignored but don't stop the program
     * 4. No two cars will be parked together
     */

    printf("Add all current cars to the carpark. How many cars would you like to add? ");
    int cars_to_be_added;
    scanf("%d", &cars_to_be_added);

    while(cars_to_be_added >= 49) { //If it exceeds 48 therefore it is impossible to add more.
        printf("Maximum limit is 48 cars. How many cars would you like to add? ");
        scanf("%d", &cars_to_be_added); //Ask user until given a number other than 48
    }

    printf("Where would you like to park each car?\n");
    int license_plate_no, row_car, col_car;
    for(int b = 0; b < cars_to_be_added; ++b) { //Loops the amount of cars
        scanf("%d %d %d", &license_plate_no, &row_car, &col_car);

        if (license_plate_no / 10000 != 0) { //check for valid license plates
            printf("Invalid license plate!\n");
            continue;
        }

        if ((row_car >= 8) || (col_car >= 6)) {
            printf("Invalid car space!\n");
            continue;
        }

        if (carpark[row_car][col_car].type == ELECTRIC_CHARGING_STATION) {
            printf("Cannot park on a space occupied by an electric charging station.\n");
        }

        //If all checks are passed, the code below executes
        carpark[row_car][col_car].licence_plate = license_plate_no;
        carpark[row_car][col_car].occupied_since = 0;
    }
    
    //Once the loop finishes
    print_carpark(carpark);
    printf("The carpark is now ready for business!\n");

    //------------------------- CONTINOUS LOOP ---------------------------------
    //Keep taking command until EOF (or null) is sent to the computer (ctrl-d).
    
    char input_character;

    printf("Enter a command: ");
    while(scanf(" %c", &input_character) != EOF) {
        if (input_character == 'P') { //PURPOSE OF FUNCTION: Prints the entire carpark
            print_carpark(carpark);

        } else if (input_character == 'p') { //PURPOSE OF FUNCTION: Parks new cars after setup
            //Uses buffer behvaior of scanf to take numbers instantly
            int target_license_plate, row, column, time_of_entry;
            scanf("%d %d %d %d", &target_license_plate, &row, &column, &time_of_entry);

            //Pre adding parking checks 
            if (out_of_bound(row, column) == 1) { //If out of bound print...
                printf("Invalid car space!\n");

            } else if (carpark[row][column].type == ELECTRIC_CHARGING_STATION) {
                printf("Cannot park on a space occupied by an electric charging station.\n");

            } else if (!(carpark[row][column].licence_plate == -1)) {
                printf("Car space is already occupied!\n");

            } else if (carpark[row][column].occupied_since == 69420) { 
                //If occupied_since is 69420 it means that it is beside a car wash
                if (find_non_adjacent_to_car_wash(carpark) == 0) { //Find for alternatives first
                    park_car(target_license_plate, row, column, time_of_entry, carpark);
                } else {
                    printf("Cannot park next to a carwash bay. There are still other spaces available in the carpark.\n");
                }

            } else {
                park_car(target_license_plate, row, column, time_of_entry, carpark);
            }

        } else if (input_character == 'o') { //PURPOSE OF FUNCTION: Shows carpark spaces left free
            int sum_of_cars = 0;

            for(int row = 0; row < CARPARK_ROWS; ++row) {
                for(int column = 0; column < CARPARK_COLUMNS; ++column) {
                    if (carpark[row][column].licence_plate == -1) {
                        continue; //do nothing
                    } else {
                        //Anything else must be a license plate and therefore a car
                        sum_of_cars += 1;
                    }
                }
            }

            printf("There are currently %d cars and %d empty car spaces in the carpark.\n", 
                            sum_of_cars, (CARPARK_COLUMNS*CARPARK_ROWS) - sum_of_cars);
            
        } else if (input_character == 'F') { //PURPOSE OF FUNCTION: Shows all free spaces

            printf("The normal car spaces that are still available are:\n");    
            print_spaces_available(NORMAL, carpark);

            printf("\nThe premium car spaces that are still available are:\n");    
            print_spaces_available(PREMIUM, carpark);

        } else if (input_character == 'd') { //PURPOSE OF FUNCTION: Implement discount of 10% to empty spaces
            for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
                for(int column = 0; column < CARPARK_COLUMNS; ++column) {
                    if (carpark[row][column].licence_plate == -1) { //If empty therefore
                        carpark[row][column].parking_rate = (int)(carpark[row][column].parking_rate * 0.9);
                    }
                }
            } 
            printf("A 10%% discount has been applied to all empty spaces!\n");

        } else if (input_character == 'f') {
            int license_plate_target;
            scanf(" %d", &license_plate_target);

            if (find_plate(license_plate_target, carpark) == 1) { 
                printf("Car %d is parked in car space (%d, %d).\n", license_plate_target,
                find_plate_row(license_plate_target, carpark),
                find_plate_column(license_plate_target, carpark) ); 
            } else { //no plate has been found
                printf("No car with licence plate number %d could be found.\n", license_plate_target);
            }

        } else if (input_character == 'l') {
            int license_plate_target, check_out_time;
            scanf(" %d %d", &license_plate_target, &check_out_time);
            
            int row = find_plate_row(license_plate_target, carpark);
            int column = find_plate_column(license_plate_target, carpark);

            if (find_plate(license_plate_target, carpark) == 1) {
                checkout_of_parking(license_plate_target, row, column, check_out_time, carpark, history_database);
            } else {
                printf("No car with licence plate number %d could be found.\n", license_plate_target);
            }
        
        } else if (input_character == 'e') {
            int electric_col, electric_row, build_time, cable_length;
            scanf("%d %d %d %d", &electric_col, &electric_row, &build_time, &cable_length);
            
            build_charger(electric_row, electric_col, build_time, cable_length, carpark);
        
        } else if (input_character == 'c') {
            int license_plate_target, charge_time_start, charge_time_end;
            scanf("%d %d %d", &license_plate_target, &charge_time_start, &charge_time_end);
          
            if (find_plate(license_plate_target, carpark) == 1) { //Executes if the plate is found
                int target_row = find_plate_row(license_plate_target, carpark);
                int target_column = find_plate_column(license_plate_target, carpark);

                get_charger(license_plate_target, target_row, target_column, charge_time_start, charge_time_end, carpark, history_database);

            } else {
                printf("No car with licence plate number %d could be found.", license_plate_target);
            }

        } else if (input_character == 'm') {
            int license_plate_target, new_row, new_col, time_of_move;
            scanf("%d %d %d %d", &license_plate_target, &new_row, &new_col, &time_of_move);

            if (find_plate(license_plate_target, carpark)) { //If license plate exists and is found
                int target_row = find_plate_row(license_plate_target, carpark);
                int target_column = find_plate_column(license_plate_target, carpark);

                if (new_row > CARPARK_ROWS || new_col > CARPARK_COLUMNS) {

                    printf("Car %d cannot be moved to an invalid car space.\n", license_plate_target);

                } else if (time_of_move < carpark[target_row][target_column].occupied_since) {

                    printf("The move time provided is invalid.\n");

                } else if (carpark[new_row][new_col].type == ELECTRIC_CHARGING_STATION) {

                    printf("Cannot park on a space occupied by an electric charging station.\n");

                } else if (carpark[new_row][new_col].occupied_since == 69420) {

                    if (find_non_adjacent_to_car_wash(carpark) == 0) { //All "good" spots are full
                        //Add into history
                        for(int time = carpark[target_row][target_column].occupied_since; time < time_of_move; ++time) {
                            add_database(license_plate_target, carpark[target_row][target_column].type,
                            time, target_row, target_column, history_database);
                        }

                        move_car(license_plate_target, target_row, target_column, new_row, new_col, time_of_move, carpark);

                        //If empty AND moved into a carwash
                        if (carpark[new_row][new_col].type == CARWASH_BAY) {
                            carpark[new_row][new_col].total_bill += 15;
                            printf("Car %d is now using the carwash bay located at (%d, %d).\n", license_plate_target, new_row, new_col);
                        } else {
                            printf("Car %d has been moved to space (%d, %d).\n", license_plate_target, new_row, new_col);
                        }
                    } else {
                        printf("Cannot park next to a carwash bay. There are still other spaces available in the carpark.\n");
                    }

                } else if (carpark[new_row][new_col].type == CARWASH_BAY) {
                    if (check_carwash_bounds(new_row,new_col,carpark) == 1) {
                        for(int time = carpark[target_row][target_column].occupied_since; time < time_of_move; ++time) {
                            add_database(license_plate_target, carpark[target_row][target_column].type,
                            time, target_row, target_column, history_database);
                        }

                        move_car(license_plate_target, target_row, target_column, new_row, new_col, time_of_move, carpark);

                        carpark[new_row][new_col].total_bill += 15;

                        printf("Car %d is now using the carwash bay located at (%d, %d).\n", license_plate_target, new_row, new_col);

                    } else {
                        printf("This carwash bay cannot be used as one or more of the surrounding spaces are currently occupied.\n");
                    }
                } else if (carpark[new_row][new_col].licence_plate == EMPTY) {
                    for(int time = carpark[target_row][target_column].occupied_since; time < time_of_move; ++time) {
                        add_database(license_plate_target, carpark[target_row][target_column].type,
                        time, target_row, target_column, history_database);
                    }

                    move_car(license_plate_target, target_row, target_column, new_row, new_col, time_of_move, carpark);

                    //If empty AND moved into a carwash
                    if (carpark[new_row][new_col].type == CARWASH_BAY) {
                        carpark[new_row][new_col].total_bill += 15;
                        printf("Car %d is now using the carwash bay located at (%d, %d).\n", license_plate_target, new_row, new_col);
                    } else {
                        printf("Car %d has been moved to space (%d, %d).\n", license_plate_target, new_row, new_col);
                    }
                    
                } else {
                    //Not empty
                    printf("Car %d could not be moved to space (%d, %d) as car %d is already parked there.\n",
                    license_plate_target, new_row, new_col, carpark[new_row][new_col].licence_plate);
                }

            } else { //No license plate found
                printf("No car with licence plate number %d could be found.\n", license_plate_target);
            }

        } else if (input_character == 'w') {
            int wash_row, wash_col, build_time;
            //Build time is kind of useless but we'll see
            scanf("%d %d %d", &wash_row, &wash_col, &build_time);

            //check for out of bounds comparisons
            if (check_carwash_bounds(wash_row, wash_col, carpark) == 1) {
                //set all original_arrival_time to 69420 which indicates adjacent to carwash
                for(int i = wash_row - 1; i <= wash_row + 1; ++i) {
                    for(int j = wash_col - 1; j <= wash_col + 1; ++j) {
                        if ((i < 8 && i >= 0) && (j < 6 && j >= 0)) {
                            carpark[i][j].occupied_since = 69420; //69420 indicates adjacent to the wash area

                            //middle exception
                            if (i == wash_row && j == wash_col) {
                                carpark[i][j].occupied_since = EMPTY;
                            }

                        }
                    } 
                }

                carpark[wash_row][wash_col].type = CARWASH_BAY;
                carpark[wash_row][wash_col].parking_rate = 0; //fixed fee. Apply as cars move in or park
                printf("Carwash bay has been built on space (%d, %d) at time %d.\n", wash_row, wash_col, build_time);

            } else {
                printf("This carwash bay cannot be built as one or more of the surrounding spaces are currently occupied.\n");
            }
        } else if (input_character == 'h') {
            //HERE WE GO AGAIN
            int target_license_plate;
            scanf("%04d", &target_license_plate);

            int license_index = search_databse(target_license_plate, history_database);
            int front_index = find_non_negative(history_database[license_index].row_coordinates);

            if ( license_index != -1) {
                printf("Here is the full parking report for car %04d:\n", target_license_plate);
                for(int i = 0; i < 23; ++i) { //Prevents out of bounds
                    if (history_database[license_index].row_coordinates[i] != history_database[license_index].row_coordinates[i + 1] || //Change in coordinates
                    history_database[license_index].column_coordinates[i] != history_database[license_index].column_coordinates[i + 1] ||
                    history_database[license_index].activity[i] != history_database[license_index].activity[i + 1]) {                        
                        print_history(history_database[license_index].row_coordinates[i], 
                                      history_database[license_index].column_coordinates[i], 
                                      history_database[license_index].activity[i]);

                        for( ;front_index <= i; ++front_index) {
                            if (history_database[license_index].activity[i] == -1) {
                                continue;
                            } else {
                                printf("\ttime %d.\n", front_index);
                            }
                        } 

                    } else {
                        continue;
                        //Ensures that the program keeps on going incase
                        //a car returns on a later time. 
                    }
                }

                if (history_database[license_index].charger_coordinates[0] != -1) { //Anything here works
                    printf("Charged using charger in space (%d, %d) from:\n", 
                    history_database[license_index].charger_coordinates[0], history_database[license_index].charger_coordinates[1]);
                    printf("\ttime %d to time %d.", 
                    history_database[license_index].charging_time[0], history_database[license_index].charging_time[1]);
                }

            } else {
                printf("No car with licence plate number %d could be found.\n", target_license_plate);
            }

        } else if (input_character == 'z') {

            //--------------- FOR DEBUGGING REPORT ----------------------------
            //Debugging purposes cause my debugger is broken :/
            //add_database(1111, PREMIUM, 4, history_database);

            // printf("Licence plate %04d\n", history_database[0].plate_number);
            
            // for(int i = 0; i < 24; ++i) {
            //     printf("%d ", i);
            // }
            // printf("\n");
            
            // for(int i = 0; i < 24; ++i) {
            //     printf("%d ", history_database[0].row_coordinates[i]);
            // }
            // printf("\n");

            // for(int i = 0; i < 24; ++i) {
            //     printf("%d ", history_database[0].column_coordinates[i]);
            // }
            // printf("\n");

            // for(int i = 0; i < 24; ++i) {
            //     printf("%d ", history_database[0].activity[i]);
            // }
            
            // printf("\n");

            //----------------- FOR DEBUGGING PATHFINDING ----------------------
            // printf("%d", out_of_bound(8,3));
            // printf("%d", out_of_bound(7,3));
            // printf("%d", out_of_bound(6,3));
            // printf("%d", out_of_bound(3,6));
            // printf("%d", out_of_bound(3,5));
            // printf("%d", out_of_bound(3,4));

            printf("%d", is_solid_block(1,0, carpark));
            printf("%d", is_solid_block(1,1, carpark));
            printf("%d", is_solid_block(1,2, carpark));
            printf("%d", is_solid_block(1,3, carpark));
        } 

        printf("Enter a command: ");

    }
    //CTRL-D is hit and the loop is exited 
    printf("The carpark is now closed. Bye!\n");
} 

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//* FUNCTIONS HERE
//Note: Functions are ordered in the order they appear in the code. Except the first 3.

int find_plate(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
        for(int column = 0; column < CARPARK_COLUMNS; ++column) {
            if (carpark[row][column].licence_plate == number_plate) { //Print for premium
                return 1;
            }
        }
    } 

    return 0;
}

int find_plate_column(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
        for(int column = 0; column < CARPARK_COLUMNS; ++column) {
            if (carpark[row][column].licence_plate == number_plate) { //Print for premium
                return column;
            }
        }
    } 
    return 0;
}

int find_plate_row(int number_plate, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
        for(int column = 0; column < CARPARK_COLUMNS; ++column) {
            if (carpark[row][column].licence_plate == number_plate) { //Print for premium
                return row;
            }
        }
    } 
    return 0;
}

int out_of_bound(int row, int column) {
    //PURPOSE OF FUNCTION: Yes
    if ((row > 8) || (row < -1) || (column > 6) || (column < -1)) {  return 1; } //Box is out of bounds
    else { return 0; }
}

void park_car(int target_license_plate, int row, int column, int time_of_entry, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    //PURPOSE OF FUNCTION: Parks new cars and sets up their variables
    carpark[row][column].licence_plate = target_license_plate; //Change license plates
    carpark[row][column].occupied_since = time_of_entry; //Change license plates
    carpark[row][column].original_arrival_time = time_of_entry; //Change license plates

    //Additional changes for car wash
    if (carpark[row][column].type == CARWASH_BAY) {
        carpark[row][column].total_bill += 15;
        printf("Car %d is now using the carwash bay located at (%d, %d).\n", target_license_plate, row, column);
    } else {
        printf("Car %04d was added into car space (%d, %d) at time %d!\n", target_license_plate, row, column, time_of_entry);
    } 
}

int print_spaces_available(int type_of_space, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    //PURPOSE OF FUNCTION: Function prints all spaces. Returns 0 if none are available
    int count = 0;
    
    for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
        for(int column = 0; column < CARPARK_COLUMNS; ++column) {
            if (carpark[row][column].type == type_of_space && carpark[row][column].licence_plate == -1) { //Print for normal
                count += 1; 
                printf("(%d, %d): $%d\n", row, column, carpark[row][column].parking_rate);
            }
        }
    }

    if (count == 0) { 
        printf("NONE\n");
        return 0; 
    }
    else { return 1; }
}

int checkout_of_parking(int license_plate_target, int row, int column, int check_out_time, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], struct history history_database[MAX_DATABASE]) {
    //PURPOSE OF FUNCTION: Prints checkout messages
    //and resets parking prices to original

    int display_hours = check_out_time - carpark[row][column].original_arrival_time;
    int hours = check_out_time - carpark[row][column].occupied_since;
    if (hours <= -1) {
        printf("The time of exit provided is invalid.\n");
        return -1;
    }

    //Code to add to history
    for(int time = carpark[row][column].occupied_since; time < check_out_time; ++time) {
        add_database(license_plate_target, carpark[row][column].type, time, row, column, history_database);
    }
    add_database(license_plate_target, LEAVE, check_out_time, row, column, history_database);

    //Code below executes when checks have been passed.
    printf("Car %d was parked for %d hours. The total price for this duration is $%d.\n", 
            license_plate_target, display_hours, hours * carpark[row][column].parking_rate + carpark[row][column].total_bill);
    carpark[row][column].licence_plate = -1; //Empty the parking lot

    //revert discount to original price 
    if (carpark[row][column].type == NORMAL) {
        carpark[row][column].parking_rate = 10;
    } else if (carpark[row][column].type == PREMIUM) {
        carpark[row][column].parking_rate = 50;
    }

    return 0;
}

int build_charger(int electric_row, int electric_col, int build_time, int cable_length, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    //PURPOSE OF FUNCTION: Builds electric chargers
    carpark[electric_col][electric_row].type = ELECTRIC_CHARGING_STATION;
    carpark[electric_col][electric_row].licence_plate = cable_length; //License plate here is used to store cable length
    carpark[electric_col][electric_row].occupied_since = 0;

    printf("Electric charging station has been built on space (%d, %d) at time %d with cable length of %d.\n",
        electric_col, electric_row, build_time, cable_length);

    return 1;
}

void get_charger(int license_plate_target, int target_row, int target_column, int charge_time_start, int charge_time_end, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], struct history history_database[MAX_DATABASE]) {
    //PURPOSE OF FUNCTION: Print messages related to getting a charger,
    //finds closest and free one if not available.
    
    int data[3]; //0 = diagonal, 1 = row, 2 = column

    //Set variables such that
    data[DIAGONAL] = -1;
    data[CHARGER_ROW] = 0;
    data[CHARGER_COLUMN] = 0;

    //Look for distance such that there exists a charger in range while being free
    for(int i = 0; i < CARPARK_ROWS; ++i) {
        for(int j = 0; j < CARPARK_COLUMNS; ++j) {
            if (carpark[i][j].type == ELECTRIC_CHARGING_STATION) {
                if (find_diagonal(target_row, i, target_column, j) < (float)data[DIAGONAL] && carpark[i][j].occupied_since <= charge_time_start) { //If nearest charger is closer, then change variables
                    data[CHARGER_ROW] = i;
                    data[CHARGER_COLUMN] = j;
                    data[DIAGONAL] = find_diagonal(target_row, i, target_column, j); 
                };
            }
        }
    }

    //Look for a distance where there are charger in range that are NOT free
    if ((int)data[DIAGONAL] == -1) {
        //The diagonal was never changed. Meaning that all charger stations must have been taken. 

        //Enclosing for loop finds chargers that are in range AND free. 
        for(int i = 0; i < CARPARK_ROWS; ++i) {
            for(int j = 0; j < CARPARK_COLUMNS; ++j) {
                if (carpark[i][j].type == ELECTRIC_CHARGING_STATION) {
                    if (find_diagonal(target_row, i, target_column, j) < (float)data[DIAGONAL]) { //If nearest charger is closer, then change variables
                        data[CHARGER_ROW] = i;
                        data[CHARGER_COLUMN] = j;
                        data[DIAGONAL] = find_diagonal(target_row, i, target_column, j); 
                    };
                }
            }
        }
        
        if (carpark[data[CHARGER_ROW]][data[CHARGER_COLUMN]].licence_plate < data[DIAGONAL]) {
            //Nearest charger diagonal is far away
            printf("Too far away to be charged, move closer to a charging station.\n");
        } else {
            printf("All nearby charging stations are currently in use. The next free charging station is (%d, %d), which will be free at time %d.\n", 
            data[CHARGER_ROW], data[CHARGER_COLUMN], carpark[data[CHARGER_ROW]][data[CHARGER_COLUMN]].occupied_since);
        } 

    } else { //Diagonal was changed and therefore there exists a charger available
        if (carpark[data[CHARGER_ROW]][data[CHARGER_COLUMN]].occupied_since <= charge_time_start) { //compare end of previous tenant with new car start charge time
            //In distance and empty
            add_power(license_plate_target, charge_time_start, charge_time_end, data[CHARGER_ROW], data[CHARGER_COLUMN], history_database);
            printf("Car %d is being charged by the charging station located at (%d, %d).\n", license_plate_target, data[CHARGER_ROW], data[CHARGER_COLUMN]);
            carpark[data[CHARGER_ROW]][data[CHARGER_COLUMN]].occupied_since = charge_time_end;
            carpark[target_row][target_column].total_bill += (charge_time_end - charge_time_start) * 7;
        } 
    }
}

void move_car(int license_plate_target, int target_row, int target_column, int new_row, int new_col, int time_of_move, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    //Add cost to total bill and clear previous spot
    carpark[new_row][new_col].total_bill = carpark[target_row][target_column].total_bill;
    carpark[target_row][target_column].total_bill = 0;

    //Add old rate of place onto the bill
    carpark[new_row][new_col].total_bill += 
    (carpark[target_row][target_column].parking_rate * 
    (time_of_move - carpark[target_row][target_column].occupied_since));

    //Move the originial_arrival_time
    carpark[new_row][new_col].original_arrival_time = carpark[target_row][target_column].original_arrival_time;
    carpark[target_row][target_column].original_arrival_time = 0;

    //Move licence plate and empty previous one
    carpark[new_row][new_col].licence_plate = carpark[target_row][target_column].licence_plate;
    carpark[target_row][target_column].licence_plate = EMPTY;

    //Mark down occupancy time of new space and empty previous one
    carpark[new_row][new_col].occupied_since = time_of_move;
    carpark[target_row][target_column].occupied_since = 0;
}

float find_diagonal(int x1, int x2, int y1, int y2) {
    float temp = 0;
    temp = sqrt(
        ((x1 - x2) * (x1 - x2)) +
        ((y1 - y2) * (y1 - y2))
    );

    return temp;
}

int check_carwash_bounds(int wash_row, int wash_col, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    //Pre-function check;
    if (!(wash_row < 8 && wash_row >= 0) || !(wash_col < 6 && wash_col >= 0)) {
        //False if within 0-7               //False is wihthin 0-5
        //Any other produces true and the code below executes
        return 2;
    }
    
    //Checks if building a new carwash is valid

    for(int i = wash_row - 1; i <= wash_row + 1; ++i) {
        for(int j = wash_col - 1; j <= wash_col + 1; ++j) {
            if ((i < 8 && i >= 0) && (j < 6 && j >= 0)) {
                if (carpark[i][j].type == CARWASH_BAY) {
                    continue; //Skip one iteration where it is a carwash
                }
                
                if (carpark[i][j].licence_plate != -1) {
                    return 0; //Returns false as it detects a licence plate
                }
            } else {
                continue;
            }
        }
    }

    return 1; //The program exits without any detection for a car. 
}

int find_non_adjacent_to_car_wash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for(int row = 0; row < CARPARK_ROWS; ++row) { //Loop through the entire car park
        for(int column = 0; column < CARPARK_COLUMNS; ++column) {
            //if (occupied by other car || is adjacent to carwash || is a carwash)
            if (carpark[row][column].licence_plate != -1 || carpark[row][column].occupied_since == 69420 || carpark[row][column].type == CARWASH_BAY) {
                continue;
            } else {
                return 1; //Meaning there is other parking available 
            }
        }
    } 
    return 0; //No "good" parking available
}

//Database related code

void initialize_database(struct history history_database[MAX_DATABASE]) {
    for(int i = 0; i < MAX_DATABASE; ++i) {
        history_database[i].plate_number = -1; //Meaning it is empty
        for(int j = 0; j < 24; ++j) {
            //Initialize all activities and time as zero
            history_database[i].activity[j] = -1;
        }

        for(int k = 0; k < 24; ++k) {
            history_database[i].row_coordinates[k] = -1; //Represents row
            history_database[i].column_coordinates[k] = -1; //represents col
        }

        //Assumes charges once
        history_database[i].charging_time[0] = -1;
        history_database[i].charging_time[1] = -1;
        history_database[i].charger_coordinates[0] = -1;
        history_database[i].charger_coordinates[1] = -1;
        
    }
}

int search_databse(int plate_number, struct history history_database[MAX_DATABASE]) {
    for(int i = 0; i < MAX_DATABASE; ++i) {
        if (history_database[i].plate_number == plate_number) {
            return i;
        }
    } 

    return -1;
}

void add_database(int plate_number, int activity, int time, int row, int column, struct history history_database[MAX_DATABASE]) {
    //Search for existing license plate
    //If exists append onto database
    //Else make new license plate

    //Function assumes all calls are valid without errors

    for(int i = 0; i < MAX_DATABASE; ++i) {
        if (history_database[i].plate_number == plate_number) {
            //If plate number found
            history_database[i].activity[time] = activity;
            history_database[i].row_coordinates[time] = row;
            history_database[i].column_coordinates[time] = column;
            break;
        } else if (history_database[i].plate_number == -1) {
            //Make a new one
            history_database[i].plate_number = plate_number;
            history_database[i].activity[time] = activity;
            history_database[i].row_coordinates[time] = row;
            history_database[i].column_coordinates[time] = column;
            break;
        } else {

        }
    }
}

void add_power(int plate_number, int start_time, int end_time, int charger_row, int charger_col, struct history history_database[MAX_DATABASE]) {
    
    for(int i = 0; i < MAX_DATABASE; ++i) {
        if (history_database[i].plate_number == plate_number) {
            //If plate number found
            history_database[i].charging_time[0] = start_time;
            history_database[i].charging_time[1] = end_time;

            history_database[i].charger_coordinates[0] = charger_row;
            history_database[i].charger_coordinates[1] = charger_col;
            break;
        } else if (history_database[i].plate_number == -1) {
            //Make a new one
            history_database[i].plate_number = plate_number;
            history_database[i].charging_time[0] = start_time;
            history_database[i].charging_time[1] = end_time;

            history_database[i].charger_coordinates[0] = charger_row;
            history_database[i].charger_coordinates[1] = charger_col;

            break;
        } else {

        }
    } 
}

void print_history(int row, int column, int activity) {
   switch(activity) {
        case(NORMAL):
            printf("Parked in normal space (%d, %d) at: \n", row, column);
            break;
        case(PREMIUM):
            printf("Parked in premium space (%d, %d) at: \n", row, column);
            break;
        case(CARWASH_BAY):
            printf("Used carwash bay in space (%d, %d) at: \n", row, column);
            break;
        case(ELECTRIC_CHARGING_STATION):
            break; 
        case(LEAVE):
            printf("Left the carpark at: \n");
            break;
   } 
}

int find_non_negative(int array[24]) {
    for(int i = 0; i < 24; ++i) {
        if (array[i] != -1) {
            return i;
        }
    }

    return -1;
}

int is_solid_block(int row, int column, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    
    if (carpark[row][column].licence_plate != -1 ||              //License plate has something
       carpark[row][column].type == CARWASH_BAY ||                 //Is a carwash 
       carpark[row][column].type == ELECTRIC_CHARGING_STATION) {   //Is a charging station
        return 1; //it is solid
    } else {
        return 0; //No solid block
    }
}


void print_array(int array[8][6]) {
    for(int i = 0; i < CARPARK_ROWS; ++i) {
        for(int j = 0; j < CARPARK_COLUMNS; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

struct node {
    int row;
    int column;
}; 

int bfs_search(int start_row, int start_col, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    return 1;
}

int search_for_exit(int start_row, int start_col, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    // int search_row = start_row;
    // int serach_col = start_col;

    int goal_row = 7;
    int goal_col = 3;

    int searched_blocks[CARPARK_ROWS][CARPARK_COLUMNS] = {0};
    searched_blocks[start_row][start_col] = 1; //1 means path, 2 means searched through, 0 means new

    print_array(searched_blocks);

    while(1) {
        int one_is_present = 0;
        int break_var = 0;

        for(int i = 0; i < CARPARK_ROWS; ++i) {
            if (break_var == 1) {
                continue;
            }

            for(int j = 0; j < CARPARK_COLUMNS; ++j) {
                if (searched_blocks[i][j] == 1) { //such that only travelled blocks are affected 
                    if (searched_blocks[i][j] == 1) {
                        one_is_present = 1;
                    }

                    if (!(out_of_bound(i + 1, j))) { //If not out of bound
                        if (!(is_solid_block(i + 1, j, carpark))) { //If not a solid block
                            searched_blocks[i + 1][j] = 1;
                        } else { searched_blocks[i + 1][j] = 2; }
                    } else { searched_blocks[i + 1][j] = 2; }
                    
                    if (!(out_of_bound(i - 1, j))) {
                        if (!(is_solid_block(i - 1, j, carpark))) {
                            searched_blocks[i - 1][j] = 1;
                        } else {searched_blocks[i - 1][j] = 2;}
                    } else {searched_blocks[i - 1][j] = 2;}

                    if (out_of_bound(i, j + 1)) {
                        if (!(is_solid_block(i, j + 1, carpark))) {
                            searched_blocks[i][j + 1] = 1;
                        } else { searched_blocks[i][j + 1] = 2; }
                    } else { searched_blocks[i][j + 1] = 2; }

                    if ((out_of_bound(i, j - 1))) {
                        if (!(is_solid_block(i, j - 1, carpark))) {
                            searched_blocks[i][j - 1] = 1;
                        } else { searched_blocks[i][j - 1] = 2; }
                    } else { searched_blocks[i][j - 1] = 2; }
                    
                    searched_blocks[i][j] = 2; //Such that it is not searched anymore

                    if (searched_blocks[goal_row][goal_col] == 1 || searched_blocks[goal_row][goal_col] == 2) {
                        return 1;
                    }

                    break_var = 1;
                    break;
                }
            }
        }

        print_array(searched_blocks);
        sleep(1);

        if (one_is_present == 0) {
            return 0; 
        }
    }

    //Check if element is present 
}

// void add_activity(int plate_number, int activity, int start_time, int move_time, struct history history_database[MAX_DATABASE]) {
//     for(int i = start_time; i < move_time; ++i) {
//         add_database(plate_number, activity, i, &history_database[MAX_DATABASE]);
//     }
// }

// struct coordinate find_chargers(int target_row, int target_column, struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
//     struct coordinate temp = {0,0};



// }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * Initialises carpark spaces as NORMAL spaces with NORMAL_PARKING_RATE that are
 * initially EMPTY.
 * 
 * Parameters:
 *     carpark - The carpark to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            carpark[row][col].type = NORMAL;
            carpark[row][col].parking_rate = NORMAL_PARKING_RATE;
            carpark[row][col].licence_plate = EMPTY;
            carpark[row][col].occupied_since = EMPTY;
            carpark[row][col].total_bill = 0;
            carpark[row][col].original_arrival_time = 0;
        }
    }
}

/**
 * Prints all carpark spaces, displaying their type and the licence plate of 
 * any cars parked in the carpark.
 * 
 * Parameters:
 *     carpark   - The carpark to be printed
 * Returns:
 *     Nothing.
 */
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    printf("-------------------------------------------------------------------\n");
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            print_car_space(carpark[row][col]);
        }
        printf("|\n");
        printf("-------------------------------------------------------------------\n");
    }
    printf("\n");
}

/**
 * Prints the type of a particular car space, as well as the licence plate of 
 * the car located at that car space.
 * 
 * Parameters:
 *     car_space         - The car space to print.
 *
 * Returns:
 *     Nothing.
 */
void print_car_space(struct car_space car_space) {
    printf("|");
    if (car_space.type == NORMAL) {
        printf(" N :");
    } else if (car_space.type  == PREMIUM) {
        printf(" P :");
    } else if (car_space.type  == CARWASH_BAY) {
        printf(" W :");
    } else if (car_space.type  == ELECTRIC_CHARGING_STATION) {
        printf(" CHARGER  ");
    }
    if (car_space.type != ELECTRIC_CHARGING_STATION) {
        if (car_space.licence_plate == EMPTY) {
            printf("      ");
        } else {
            printf(" %04d ", car_space.licence_plate);
        }
    }
    
}