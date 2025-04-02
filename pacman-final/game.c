// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

// Function to check if the player has won
int check_win(void) {
    // Check if there are any dots left on the map
    // Check if there are no empties
    // If so, return KEEP_GOING
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (dot_map[y * width + x] == DOT && dot_map[y * width + x] != EMPTY) {
                return KEEP_GOING;
            }
        }
    }
    // Return YOU_WIN
    return YOU_WIN;
}

// Function to check if the player has lost
int check_loss(int player_y, int player_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    // Check if the player has collided with any ghosts by iterating through each ghost's x and y position
    // If collided, return YOU_LOSE
    for (int i = 0; i < 2; i++) {
        if (player_y == ghosts_y[i] && player_x == ghosts_x[i]) {
            return YOU_LOSE;
        }
    }
    // Return KEEP_GOING
    return KEEP_GOING;
}
