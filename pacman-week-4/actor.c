// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "actor.h"
#include "map.h"   // included for is_wall

extern char * map, * dot_map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int ghost_y, int ghost_x) {
    // check to see if the ghost is eating the player
    if (player_x == ghost_x && player_y == ghost_y) {
        return EATING_PLAYER;
    }

    // check if neither the x nor y coordinate is the same as the player
    // if one of them is the same, check if the path in between is clear
    // if there's a wall in between, they can't see
    if (player_x != ghost_x && player_y != ghost_y) {
        return SEES_NOTHING;
    }

    // Check horizontal line of sight
    if (player_y == ghost_y) {
        // Check if the ghost is to the right of the player
        if (ghost_x < player_x) {
            // Check if there's a wall between ghost and player
            for (int x = ghost_x + 1; x < player_x; x++) {
                if (map[ghost_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return RIGHT;
        }   
        // Check if the ghost is to the left of the player
        if (ghost_x > player_x) {
            // Check if there's a wall between ghost and player
            for (int x = player_x + 1; x < ghost_x; x++) {
                if (map[ghost_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return LEFT;
        }
    }

    // Check vertical line of sight
    if (player_x == ghost_x) {
        // Check if the ghost is below the player
        if (ghost_y < player_y) {
            for (int y = ghost_y + 1; y < player_y; y++) {
                if (map[y * width + ghost_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return DOWN;
        }
        // Check if the ghost is above the player
        if (ghost_y > player_y) {
            // Check if there's a wall between ghost and player
            for (int y = player_y + 1; y < ghost_y; y++) {
                if (map[y * width + ghost_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return UP;
        }
    }

    return SEES_NOTHING;
}

int move_player(int * y, int * x, char direction) {
    // calculate the new coordinates to use on success (store in local variables)

    // check if the new coordinates point outside the map
    // check if the new coordinates point to a wall
    int new_y = *y;
    int new_x = *x;

    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (direction != RIGHT && direction != LEFT && direction != UP && direction != DOWN){
        return MOVED_INVALID_DIRECTION;
    }

    // Move the player in the specified direction
    if (direction == RIGHT){
        new_x++;
    }
    if (direction == LEFT){
        new_x--;
    }
    if (direction == UP){
        new_y--;
    }
    if (direction == DOWN){
        new_y++;
    }
    if(is_wall(new_y, new_x)) {
        return MOVED_WALL;
    }

    // remove player from the old position and replace with EMPTY
    map[*y*width + *x] = EMPTY;

    // set PLAYER in the new position in map
    map[new_y*width + new_x] = PLAYER;

    // update the x/y coordinate pointers
    *y = new_y;
    *x = new_x;

    // set EMPTY in the new position in dot_map
    dot_map[*y*width + *x] = EMPTY;

    return MOVED_OKAY;
}

int move_ghost(int * y, int * x, char direction) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (direction != RIGHT && direction != LEFT && direction != UP && direction != DOWN){
        return MOVED_INVALID_DIRECTION;
    }

    // calculate the new coordinates to use on success (store in local variables)
    int new_y = *y;
    int new_x = *x;

    // Move the ghost in the specified direction (only one space)
    switch(direction) {
        case RIGHT:
            new_x++;
            break;
        case LEFT:
            new_x--;
            break;
        case UP:
            new_y--;
            break;
        case DOWN:
            new_y++;
            break;
    }

    // check if the new coordinates point to a wall
    // check if the new coordinates point outside the map (also a wall)
    if(is_wall(new_y, new_x)) {
        return MOVED_WALL;
    }

    // get the value from the old position in the dot_map (either EMPTY or DOT)
    char temp = dot_map[*y*width + *x];

    // remove ghost from the old position and replace with what was in dot_map
    map[*y*width + *x] = temp;

    // set GHOST in the new position in map
    map[new_y*width + new_x] = GHOST;

    // update the x/y coordinate pointers
    *y = new_y;
    *x = new_x;
    return MOVED_OKAY;
}
