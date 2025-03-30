// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "actor.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width, height;


/**
 * This is the hardcoded map used for labs 1-3.
 * Once you implement load_map in lab 4 you should remove this map, as it cannot be used for the
 * final version of the project.
 * The map's dimensions are 9x9
 */
// #define HARDCODED_WIDTH 9
// #define HARDCODED_HEIGHT 9
// char hardcoded_map[] = {
//         GHOST, DOT, DOT, DOT, WALL, DOT, DOT, DOT, EMPTY,
//         DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
//         DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
//         DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
//         DOT, DOT, DOT, DOT, PLAYER, DOT, DOT, DOT, DOT,
//         DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
//         DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
//         DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
//         EMPTY, DOT, DOT, DOT, WALL, DOT, DOT, DOT, GHOST
// };

// You are NOT allowed to add more global variables!
// The globals that are included in the starter code provide a convenient way to share information
// between the many functions that all need access to the same data, but all other data must be
// passed using function arguments.  If you add new globals, the autograder tests will fail to run
// and you will not receive a good mark.

/**
 * Updates the positions of the ghosts.
 * For a passed ghosts, this function checks if they can see the
 * player and moves them accordingly.  If a ghost can see the player,
 * it must move towards the player.  Otherwise, the ghost will move
 * in a random valid direction (not into a wall).  If the ghost is
 * trapped by walls in all four directions, it should give up and
 * not move.
 *
 * The ghosts_y and ghosts_x arrays are meant to hold NUM_GHOSTS
 * coordinates.  So, index 0 of ghosts_x holds the X coordinate
 * of ghost 0 and index 0 of ghosts_y holds the Y coordinate of
 * ghost 0.
 * @param player_y The Y coordinate of player
 * @param player_x The X coordinate of player
 * @param ghost_y A pointer to the Y coordinates of a ghost
 * @param ghost_x A pointer to the X coordinates of a ghost
 * @return
 */
void update_ghost(int player_y, int player_x, int * ghost_y, int * ghost_x);

// define a return code for a memory error
#define ERR_MEMORY 4

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PLAYER when no player is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    // This ensures that printf writes to the console immediately, instead of buffering.
    // If you remove this, you will not be able to rely on printf to work if your program crashes.
    setbuf(stdout, NULL);

    // Loads the game map from the specified file
    map = load_map("map.txt", &height, &width);
    if (map == NULL) {
        return ERR_NO_MAP;
    }

    // Allocates memory for tracking remaining dots
    dot_map = malloc(width * height);
    if (dot_map == NULL) {
        free(map);
        return ERR_MEMORY;
    }
    // copy dots into dot_map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == DOT) {
                dot_map[y * width + x] = DOT;
            } else {
                dot_map[y * width + x] = EMPTY;
            }
        }
    }

    // Locates the player's starting position on the map
    int player_x, player_y;
    if (!find_player_position(&player_y, &player_x)) {
        free(map);
        free(dot_map);
        return ERR_NO_PLAYER;
    }

    // Locates the starting positions of all ghosts
    int ghosts_x[NUM_GHOSTS] = {-1, -1}, ghosts_y[NUM_GHOSTS] = {-1, -1};
    int ghost_count = find_ghost_positions(ghosts_x, ghosts_y);
    if (ghost_count < NUM_GHOSTS) {
        free(map);
        free(dot_map);
        return ERR_NO_GHOSTS;
    }

    // Stores the current user input character
    char input = 0;

    // Runs the main game loop until EOF is received
    while (input != EOF) {
        // Displays the current state of the game map
        print_map();

        // Waits for and reads a single character input
        input = getch();

        // Updates the player's position based on input
        move_player(&player_y, &player_x, input);

        // Updates the position of each ghost
        for (int ghost = 0; ghost < NUM_GHOSTS; ghost++) {
            update_ghost(player_y, player_x, &ghosts_y[ghost], &ghosts_x[ghost]);
        }

        // Checks if the player has lost the game
        if (check_loss(player_y, player_x, ghosts_y, ghosts_x) == YOU_LOSE) {
            printf("YOU_LOSE!");
            break;
        }
        // Checks if the player has won the game
        if (check_win() == YOU_WIN) {
            printf("YOU_WIN!");
            break;
        }
    }

    // Frees all allocated memory before program exit
    free(map);
    free(dot_map);

    return NO_ERROR;
}

void update_ghost(int player_y, int player_x, int * ghost_y, int * ghost_x) {
    // check if the ghost can see the player
    char direction = sees_player(player_y, player_x, *ghost_y, *ghost_x);

    // if the ghost doesn't see the player
    if (direction == SEES_NOTHING) {
        // get a random direction, keeping track of if we already tried it
        char tried_directions[] = {0,0,0,0};
        char direction_map[] = {UP, LEFT, DOWN, RIGHT};
        int move_result;
        do {
            // get a random direction
            int direction_int = rand() % 4;
            // set that we tried the direction
            tried_directions[direction_int] = 1;
            // get the input direction to move
            direction = direction_map[direction_int];
            // try it!
            move_result = move_ghost(ghost_y, ghost_x, direction);
            // if we try all the directions, bail out - we can't move
        } while (move_result != MOVED_OKAY &&
                 (!tried_directions[0] || !tried_directions[1] || !tried_directions[2] || !tried_directions[3]));
    } else if (direction != EATING_PLAYER) {
        // if the ghost does see the player (but is not eating them), move in that direction
        move_ghost(ghost_y, ghost_x, direction);
    }
}
