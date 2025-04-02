// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "actor.h"
#include "map.h"   // included for is_wall

extern char * map, * dot_map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int ghost_y, int ghost_x) {
    // Check to see if the ghost is eating the player
    // Return EATING_PLAYER
    if (player_x == ghost_x && player_y == ghost_y) {
        return EATING_PLAYER;
    }

    // Check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, return SEES_NOTHING
    if (player_x != ghost_x && player_y != ghost_y) {
        return SEES_NOTHING;
    }

    // Check when they are on the same row (horizontal sight)
    if (player_y == ghost_y) {
        // Check if the ghost is to the right of the player
        if (ghost_x < player_x) {
            // Iterate between the ghost's initial x position and the player's x position
            // Check if there's a wall between ghost and player
            // If so, return SEES_NOTHING
            for (int x = ghost_x + 1; x < player_x; x++) {
                if (map[ghost_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Return RIGHT
            return RIGHT;
        }   
        // Check if the ghost is to the left of the player
        if (ghost_x > player_x) {
            // Iterate between the player's x position and the ghost's initial x position
            // Check if there's a wall between ghost and player
            // If so, return SEES_NOTHING
            for (int x = player_x + 1; x < ghost_x; x++) {
                if (map[ghost_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Return LEFT
            return LEFT;
        }
    }

    // Check when they are on the same column (vertical sight)
    if (player_x == ghost_x) {
        // Check if the ghost is below the player
        if (ghost_y < player_y) {
            // Iterate between the ghost's initial y position and the player's y position
            // Check if there's a wall between ghost and player
            // If so, return SEES_NOTHING
            for (int y = ghost_y + 1; y < player_y; y++) {
                if (map[y * width + ghost_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Return DOWN
            return DOWN;
        }
        // Check if the ghost is above the player   
        if (ghost_y > player_y) {
            // Iterate between the player's y position and the ghost's initial y position
            // Check if there's a wall between ghost and player
            // If so, return SEES_NOTHING
            for (int y = player_y + 1; y < ghost_y; y++) {
                if (map[y * width + ghost_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Return UP
            return UP;
        }
    }

    // Return SEES_NOTHING
    return SEES_NOTHING;
}

int move_player(int * y, int * x, char direction) {
    // Set new coordinates to pointers
    int new_y = *y;
    int new_x = *x;

    // Move the ghost in the specified direction or default return MOVED_INVALID_DIRECTION
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
        default:
            return MOVED_INVALID_DIRECTION;
    }

    // check if the new coordinates point outside the map (also a wall)
    // If so, return MOVED_WALL
    if (new_x > (width -1) || new_x < 0 || new_y > (height-1) || new_y < 0){
        return MOVED_WALL;
    }

    // Check if the new coordinates point to a wall
    // If so, return MOVED_WALL
    if(is_wall(new_y, new_x) == YES_WALL) {
        return MOVED_WALL;
    }

    // Remove player from the old position and replace with EMPTY
    map[*y*width + *x] = EMPTY;

    // Set PLAYER in the new position in map
    map[new_y*width + new_x] = PLAYER;

    // update the x/y coordinate pointers
    *y = new_y;
    *x = new_x;

    // Set EMPTY in the new position in dot_map
    dot_map[*y*width + *x] = EMPTY;

    // Return MOVED_OKAY    
    return MOVED_OKAY;
}

int move_ghost(int * y, int * x, char direction) {
    // Set new coordinates to pointers
    int new_y = *y;
    int new_x = *x;

    // Move the ghost in the specified direction or default return MOVED_INVALID_DIRECTION
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
        default:
            return MOVED_INVALID_DIRECTION;
    }

    // check if the new coordinates point outside the map (also a wall)
    // If so, return MOVED_WALL
    if (new_x > (width -1) || new_x < 0 || new_y > (height-1) || new_y < 0){
        return MOVED_WALL;
    }

    // Check if the new coordinates point to a wall
    // If so, return MOVED_WALL
    if(is_wall(new_y, new_x) == YES_WALL) {
        return MOVED_WALL;
    }

    // Set temp value to the old position in the dot_map (either EMPTY or DOT)
    char temp = dot_map[*y*width + *x];

    // Remove ghost from the old position and replace with what was in dot_map
    map[*y*width + *x] = temp;

    // Set GHOST in the new position in map
    map[new_y*width + new_x] = GHOST;

    // update the x/y coordinate pointers
    *y = new_y;
    *x = new_x;

    // Return MOVED_OKAY
    return MOVED_OKAY;
}
