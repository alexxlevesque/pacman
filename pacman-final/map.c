// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case GHOST:
            change_text_colour(PINK);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        case DOT:
            change_text_colour(WHITE);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

// Function to find the player coordinates in map array
int find_player_position(int *player_y, int *player_x) {
    // Initialize coordinates to 0
    *player_x = 0;
    *player_y = 0;

    // Iterate through every height and width of the map
    // If player is found, set y index to player_y and x index to player_x, then return 1
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == PLAYER) {
                *player_x = x;
                *player_y = y;
                return 1;
            }
        }
    }
    // Return 0 if no player is found
    return 0;
}

// Function to find the ghost coordinates in map array
int find_ghost_positions(int *ghosts_x, int *ghosts_y) {
    // Initialize ghost count to 0
    int ghost_count = 0;

    // Iterate through every height and width of the map
    // and while the number of ghosts is less than 2
    // meaning ghost_count will be 0 (1 ghost), then 1 (2 ghosts)
    // If ghost is found, set x index to ghosts_x and y index to ghosts_y
    // since ghost coordinates are an array, its position in the array is determined by the ghost count
    for (int y = 0; y < height && ghost_count < NUM_GHOSTS; y++) {
        for (int x = 0; x < width && ghost_count < NUM_GHOSTS; x++) {
            if (map[y * width + x] == GHOST) {
                ghosts_x[ghost_count] = x;
                ghosts_y[ghost_count] = y;
                ghost_count++;
            }
        }
    }
    // Return the number of ghosts
    return ghost_count;
}

/**
 * Loads a map file into an array allocated dynamically to store it.
 * The function must allocate space using malloc/realloc and load
 * the map file contents into it.  The return value is the pointer
 * to the allocated and populated memory, and the height/width values
 * that are returned via the map_height/map_width pass-by-reference
 * parameters.
 *
 * The function can assume that the parameters are valid pointers, but
 * it should not assume that the file exists.  The map file format
 * is #__#__# ... __# where the # are symbols and _ represent whitespace
 * which should be ignored.  That is, the function can assume that
 * symbols are each separated by two spaces.  The function MAY NOT
 * assume that the map is a specific size; it must properly load any
 * size map in the correct format.  It can assume that the only valid
 * symbols are DOT, PLAYER, GHOST, WALL, and EMPTY as defined in
 * defines.h.  The function can assume that the map is a rectangle.
 *
 * On error, the function should return NULL and should not write to
 * map_height or map_width.
 *
 * For example, if the map file contains the map:
 * .  P  .  .
 * W     W  W
 * G  .  .  G
 * Then the function should return a dynamically allocated array:
 * {'.', 'P', '.', '.', 'W', ' ', 'W', 'W', 'G', '.', '.', 'G'}
 * and set *map_height = 3, *map_width = 4.
 *
 * @param filename A string containing the map file name to read
 * @param map_height A pointer to where the map height should be stored
 * @param map_width A pointer to where the map width should be stored
 * @return A pointer to the loaded map, or NULL on error
 */
char * load_map(char * filename, int *map_height, int *map_width) {
    // Initialize file pointer
    FILE *fp = NULL;

    // Set file pointer to the opened file, reading mode
    fp = fopen(filename, "r");

    // If file pointer is still NULL, then no file was read
    // Return NULL
    if (fp == NULL) {
        return NULL;
    }

    // Initialize height and width pointers, and 1D array
    *map_height = 0;
    *map_width = 0;
    char line[256];

    // First pass to get the dimensions of the map while fgets can still read the file
    // Increase map height after every iteration (checking for number of rows)
    while (fgets(line, sizeof(line), fp)) {
        (*map_height)++;
        int width = 0;
        // Iterate through an entire row while the character isn't null (\0) or a new line (\n)
        // If the modulus 3 of the index is 0, increase map width (checking for number of columns)
        // Logic: each character is separated by two spaces, thus i % 3 represents characters
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            if ((i % 3) == 0) {
                width++;
            }
        }
        // If the width of the current row is greater than the width of the map, update the map width
        if (width > *map_width) {
            *map_width = width;
        }
    }

    // Allocate memory for the map
    char *map_array = malloc((*map_height) * (*map_width) * sizeof(char));
    if (map_array == NULL) {
        fclose(fp);
        return NULL;
    }

    // Initialize map with empty spaces
    for (int i = 0; i < (*map_height) * (*map_width); i++) {
        map_array[i] = EMPTY;
    }

    // Reset file pointer and read the map
    rewind(fp);
    int row = 0;

    // Second pass: read the actual map
    // Read the map line by line
    // If the row is less than the height of the map, read the map
    // If the column is less than the width of the map, read the map
    while (fgets(line, sizeof(line), fp) && row < *map_height) {
        int col = 0;
        // Iterate through the row while the character isn't null (\0) or a new line (\n)
        // If the modulus 3 of the index is 0, increase the column index
        // Logic: each character is separated by two spaces, thus i % 3 represents characters 
        // and col is the index of the character in the row
        for (int i = 0; line[i] != '\0' && line[i] != '\n' && col < *map_width; i++) {
            if ((i % 3) == 0) {
                map_array[row * (*map_width) + col] = line[i];
                col++;
            }
        }
        // Increase the row index after every iteration
        row++;
    }

    // Close the file
    fclose(fp);

    // Return the map
    return map_array;
}

/**
 * Prints the map using the global variables defined in apsc142project.c.
 * Preconditions: the map, dot_map, width, and height globals can be
 * assumed to be valid.
 */
void print_map(void) {
    // Prints the top border of walls
    for (int i = 0; i < width + 2; i++) {
        printc(WALL);
        // If the index is less than the width of the map, print a space
        if (i < width + 1) printf(" ");
    }
    printf("\n");

    // Prints each row of the map with wall borders
    for (int y = 0; y < height; y++) {
        // Prints the left wall border for each row
        printc(WALL);
        // If the index is less than the width of the map, print a space
        printf(" ");

        // Prints each character in the current row
        for (int x = 0; x < width; x++) {
            printc(map[y * width + x]);
            // Always print space after each character
            printf(" ");
        }

        // Prints the right wall border for each row
        printc(WALL);
        printf("\n");
    }

    // Prints the bottom border of walls
    for (int i = 0; i < width + 2; i++) {
        printc(WALL);
        // If the index is less than the width of the map, print a space
        if (i < width + 1) printf(" ");
    }
    // Print a new line after the bottom border
    printf("\n");
}

/**
 * Determines if a coordinate in the map is a wall or not.
 * This function should use the global map and the passed coordinates
 * to determine a yes/no answer if this coordinate is a wall.
 *
 * You should use the above #defines for return values from
 * this function.  This function can assume that the global map
 * and its height/width are all valid.
 *
 * @param y The Y coordinate on the map to check
 * @param x The X coordinate on the map to check
 * @return NOT_WALL if the coordinate is not a wall, YES_WALL if it is
 */
int is_wall(int y, int x) {
    // If the y coordinate is less than 0,
    // or the y coordinate is equal to the height of the map,
    // or the x coordinate is less than 0, 
    // or the x coordinate is greater than or equal to the width of the map, 
    // then return YES_WALL
    if(y < 0 || y == height || x < 0 || x >= width) {
        return YES_WALL;
    }

    // If the character at the coordinates is a wall, return YES_WALL
    // Otherwise, return NOT_WALL   
    return (map[y*width + x] == WALL) ? YES_WALL : NOT_WALL;
}
