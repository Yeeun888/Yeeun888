// COMP1911 Assignment 2 CS Defence
// This program implements different functions to create a Tower Defence game
// This program was written by Lim Chun Heng (z5350151)
// Date : 26 July 2023

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;

    int n_enemies;
};

void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);

//Insert function prototypes here

int command_enemy (int enemies, struct tile *tile_name);
int command_tower (struct tile *tile_name, int *money);
int command_steps(int steps, struct tile map[MAP_ROWS][MAP_COLUMNS], int row, int col);
int call_step(int steps, struct tile map[MAP_ROWS][MAP_COLUMNS], int start_row, int start_col);

int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);
    
    int lives, money;
    int start_row, start_column, end_row, end_column;
    
    // Scan in lives, money and start/ending points
    printf("Starting Lives: ");
    scanf("%d", &lives);
    printf("Starting Money($): ");
    scanf("%d", &money);
    printf("Start Point: ");
    scanf("%d %d", &start_row, &start_column);
    printf("End Point: ");
    scanf("%d %d", &end_row, &end_column);
    
    map[start_row][start_column].land = PATH_START;
    map[end_row][end_column].land = PATH_END;
    
    // printing out the map, lives and money
    print_map(map, lives, money);

    // Ask for number of enemies and scan value    
    int enemies;
    
    printf("Initial Enemies: ");
    scanf("%d", &enemies);
    
    if (enemies > 0){
        map[start_row][start_column].n_enemies = enemies;
        map[start_row][start_column].entity = ENEMY;
    }
    // Prints enemy on map
    print_map(map, lives, money);
    
    int water_row, water_col, height, width;
    
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &water_row, &water_col, &height, &width);
    
    //If lake falls within the map, print the area of lake on the map
    if (height <= MAP_ROWS && width <= MAP_COLUMNS && water_row >= 0 && 
        water_col >= 0 && (water_row + height) <= MAP_ROWS && 
        (water_col + width) <= MAP_COLUMNS) {
        int i = 0;
        while (i < height) { 
            int j = 0;
            while (j < width) { 
                map[water_row + i][water_col + j].land = WATER;
                j++;
            }
            i++;
        }
    } else {
        printf("Error: Lake out of bounds, ignoring...\n");
    }
    print_map(map, lives, money);

    // Getting directions for path
    char direction;
    int cur_row = start_row;
    int cur_column = start_column;
 
    printf("Enter Path: ");
    
    int num_moves = 0;
    // code will keep executing until player reaches end point.
   if (cur_row == end_row && cur_column == end_column){
        map[cur_row][cur_column].land = PATH_END;
    }
        
    while (cur_row != end_row || cur_column != end_column ){
        scanf(" %c", &direction); 
        
        if (direction == 'u'){
            map[cur_row][cur_column].land = PATH_UP;
            cur_row = cur_row - 1;
        }
        else if (direction == 'd'){
            map[cur_row][cur_column].land = PATH_DOWN;
            cur_row++;
        }
        else if (direction == 'r'){
            map[cur_row][cur_column].land = PATH_RIGHT;
            cur_column++;
        }
        else if (direction == 'l'){
            map[cur_row][cur_column].land = PATH_LEFT;
            cur_column = cur_column - 1;
            }
        num_moves++ ;
    }
    
    print_map(map, lives, money);

    // Command loop that will spawn enemies & keep executing until killed 
    // by player. Will return Game Over !
    
    char input;
    printf("Enter Command: ");
    while (scanf(" %c", &input) != EOF) {
        if (input == 'e') {
            int num;
            scanf("%d", &num);
            command_enemy (num, &(map[start_row][start_column]));
            print_map(map, lives, money);
        } else if (input == 't'){
            int x_cord, y_cord;
            scanf("%d %d", &x_cord, &y_cord);
            if (money > 200 && x_cord <= 5 && y_cord <= 11 &&
                x_cord >= 0 && y_cord >= 0 &&
                map[x_cord][y_cord].land == GRASS &&
                map[x_cord][y_cord].entity == EMPTY){
                command_tower(&(map[x_cord][y_cord]) , &money);
            } else {
                printf("Error: Tower creation unsuccessful. Make sure you have at least $200 and that the tower is placed on a grass block with no entity.\n"); 
            }
        } else if (input == 'm') {
            int steps;
            scanf("%d", &steps);
            call_step(steps, map, start_row, start_column); 

            print_map(map, lives, money);
        }

        printf("Enter Command: ");
    }
    
    print_map(map, lives, money);
    printf("Enter Command: ");
   
    printf("\nGame Over!\n");

    return 0;
}

int call_step(int steps, struct tile map[MAP_ROWS][MAP_COLUMNS], int start_row, int start_col) {
    //Go through the path and memorize all the locations of enemies
    int row_cord[72];
    int col_cord[72];

    int last_index = 0;

    int row_end = start_row;
    int col_end = start_col;

    //Go through the path until the end
    while (map[row_end][col_end].land != PATH_END) {

        //printf("%d %d\n", row_end, col_end);
        if(map[row_end][col_end].entity == ENEMY) {
            row_cord[last_index] = row_end;
            col_cord[last_index] = col_end;
            last_index += 1;
        }

        if (map[row_end][col_end].land == PATH_RIGHT ){
            col_end += 1;
        } else if (map[row_end][col_end].land == PATH_LEFT){
            col_end -= 1;
        } else if (map[row_end][col_end].land == PATH_DOWN){
            row_end += 1;
        } else if (map[row_end][col_end].land == PATH_UP){
            row_end -= 1;
        }
    }

    //printf("%d %d", row_cord[0], col_cord[0]);

    for(int i = last_index; i >= 0; --i) {
        command_steps(steps, map, row_cord[i], col_cord[i]);
    }

    return 1;
}

int command_steps(int steps, struct tile map[MAP_ROWS][MAP_COLUMNS], int row, int col){
    //Keep track of the end
    int row_end = row;
    int col_end = col;
    int num_steps = 0;

    while (num_steps < steps) {
        if (map[row_end][col_end].land == PATH_RIGHT ){
            col_end += 1;
        } else if (map[row_end][col_end].land == PATH_LEFT){
            col_end -= 1;
        } else if (map[row_end][col_end].land == PATH_DOWN){
            row_end += 1;
        } else if (map[row_end][col_end].land == PATH_UP){
            row_end -= 1;
        }
        num_steps += 1;
    }

    //printf("%d %d, %d %d\n", row, col, row_end, col_end);

    map[row_end][col_end].entity = ENEMY;
    map[row_end][col_end].n_enemies = map[row][col].n_enemies;
    map[row][col].entity = EMPTY;
    map[row][col].n_enemies = 0;    

    return 1;
}

int command_enemy (int enemies, struct tile *tile_name) {
    tile_name -> n_enemies += enemies;
    tile_name -> entity = ENEMY;
    return 0;
}

int command_tower (struct tile *tile_name, int *money){
    tile_name -> entity = BASIC_TOWER;
    *money -= 200;
    printf("Tower successfully created!\n");
    return 0;
}

/**
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 * 
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

/**
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 * 
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

/**
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 * 
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */
void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}