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

int find_player_position(int *player_y, int *player_x) {
    *player_x = -1;
    *player_y = -1;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == PLAYER) {
                *player_x = x;
                *player_y = y;
                return 1;
            }
        }
    }
    return 0;
}

int find_ghost_positions(int *ghosts_x, int *ghosts_y) {
    int ghost_count = 0;
    
    for (int y = 0; y < height && ghost_count < NUM_GHOSTS; y++) {
        for (int x = 0; x < width && ghost_count < NUM_GHOSTS; x++) {
            if (map[y * width + x] == GHOST) {
                ghosts_x[ghost_count] = x;
                ghosts_y[ghost_count] = y;
                ghost_count++;
            }
        }
    }
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
    // Opens the map file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }

    // First count dimensions
    char line[256];
    *map_height = 0;
    *map_width = 0;
    
    // Counts the number of non-space characters in each line to determine map dimensions
    while (fgets(line, sizeof(line), fp)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] != ' ' && line[i] != '\n') {
                count++;
            }
        }
        if (count > *map_width) {
            *map_width = count;
        }
        (*map_height)++;
    }

    // Allocates memory for the map array based on dimensions
    char *map_array = malloc((*map_height) * (*map_width) * sizeof(char));
    if (map_array == NULL) {
        fclose(fp);
        return NULL;
    }

    // Resets file pointer to beginning for second pass
    rewind(fp);
    int row = 0;
    // Reads map characters into allocated array, ignoring spaces
    while (fgets(line, sizeof(line), fp)) {
        int col = 0;
        for (int i = 0; line[i] != '\0' && col < *map_width; i++) {
            if (line[i] != ' ' && line[i] != '\n') {
                map_array[row * (*map_width) + col] = line[i];
                col++;
            }
        }
        row++;
    }
    fclose(fp);
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
        if (i < width + 1) printf(" ");  // Don't print space after last character
    }
    printf("\n");

    // Prints each row of the map with wall borders
    for (int y = 0; y < height; y++) {
        // Prints the left wall border for each row
        printc(WALL);
        printf(" ");

        // Prints each character in the current row
        for (int x = 0; x < width; x++) {
            printc(map[y * width + x]);
            printf(" ");  // Always print space after each character
        }

        // Prints the right wall border for each row
        printc(WALL);
        printf("\n");
    }

    // Prints the bottom border of walls
    for (int i = 0; i < width + 2; i++) {
        printc(WALL);
        if (i < width + 1) printf(" ");  // Don't print space after last character
    }
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
    // Returns YES_WALL if coordinates are outside map boundaries
    if(y < 0 || y == height || x < 0 || x >= width) {
        return YES_WALL;
    }

    // Returns YES_WALL if the character at the coordinates is a wall
    return (map[y*width + x] == WALL) ? YES_WALL : NOT_WALL;
}
