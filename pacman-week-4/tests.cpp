// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "actor.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map


TEST_SUITE_END();

/* tests for actor.c */
TEST_SUITE_BEGIN("Actor tests");

// tests for sees_player

// Test sees_player for ghost eating player and seeing player from a distance
TEST_CASE("A test for sees_player handles eating player and no walls") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, DOT, PLAYER};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, EMPTY};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == EATING_PLAYER));
    
    // Test seeing player from a distance
    ghost_x = 0;
    player_x = 2;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == RIGHT));
}

// Test sees_player for vertical line of sight with ghost above player
TEST_CASE("A test for sees_player vertical line of sight") {
    int player_y = 2;
    int player_x = 0;
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, WALL,
                       DOT, WALL,
                       PLAYER, WALL};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           DOT, WALL,
                           EMPTY, WALL};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == DOWN));
}

// Test sees_player for ghost to the right of player
TEST_CASE("A test for sees_player ghost to right of player") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 0;
    int ghost_x = 2;
    char tiny_map[] = {PLAYER, DOT, GHOST};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, EMPTY};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == LEFT));
}

// Test sees_player for ghost below player
TEST_CASE("A test for sees_player ghost below player") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 2;
    int ghost_x = 0;
    char tiny_map[] = {PLAYER, WALL,
                       DOT, WALL,
                       GHOST, WALL};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           DOT, WALL,
                           EMPTY, WALL};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == UP));
}

// Test sees_player for ghost below player with wall between
TEST_CASE("A test for sees_player vertical wall between") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 2;
    int ghost_x = 0;
    char tiny_map[] = {PLAYER, WALL,
                       WALL, WALL,
                       GHOST, WALL};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           WALL, WALL,
                           EMPTY, WALL};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == SEES_NOTHING));
}

// Test sees_player for ghost and player with different x and y coordinates
TEST_CASE("A test for sees_player different x and y") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 1;
    int ghost_x = 1;
    char tiny_map[] = {PLAYER, DOT,
                       DOT, GHOST};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, EMPTY};
    dot_map = tiny_dot_map;
    // Test that when both x and y are different, ghost cannot see player
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == SEES_NOTHING));
}

// Test sees_player for ghost and player with wall between them
TEST_CASE("A test for sees_player wall between") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 0;
    int ghost_x = 2;
    char tiny_map[] = {PLAYER, WALL, GHOST};  // Wall between player and ghost
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, WALL, EMPTY};
    dot_map = tiny_dot_map;
    CHECK((sees_player(player_y, player_x, ghost_y, ghost_x) == SEES_NOTHING));
}

// Test move_ghost for moving over a dot and preserving it
TEST_CASE("A test for move_ghost over dot") {
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, DOT, WALL};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_OKAY));
    CHECK(map[0] == EMPTY);  // Check that ghost's old position shows what was in dot_map
    CHECK(map[1] == GHOST);  // Check that ghost moved to new position
    CHECK(dot_map[1] == DOT);  // Check that dot is preserved in dot_map
}

// Test move_player for moving right and hitting wall
TEST_CASE("A test for move_player right") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, DOT, WALL};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

// Test move_player for moving left and hitting wall
TEST_CASE("A test for move_player left") {
    int player_y = 0;
    int player_x = 2;
    char tiny_map[] = {WALL, DOT, PLAYER};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {WALL, DOT, EMPTY};
    dot_map = tiny_dot_map;
    char direction = LEFT;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

// Test move_player for moving down and hitting wall
TEST_CASE("A test for move_player down") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, WALL,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = DOWN;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

// Test move_player for moving up and hitting wall
TEST_CASE("A test for move_player up") {
    int player_y = 2;
    int player_x = 0;
    char tiny_map[] = {WALL, DOT,
                       DOT, DOT,
                       PLAYER, DOT};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {WALL, DOT,
                           DOT, DOT,
                           EMPTY, DOT};
    dot_map = tiny_dot_map;
    char direction = UP;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for invalid direction for move_player") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, DOT,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    direction = 'Q';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'L';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'Z';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
}

// tests for move_ghost

TEST_CASE("A test for move_ghost right") {
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, DOT, WALL};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_OKAY));
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_ghost left") {
    int ghost_y = 0;
    int ghost_x = 2;
    char tiny_map[] = {WALL, DOT, GHOST};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {WALL, DOT, EMPTY};
    dot_map = tiny_dot_map;
    char direction = LEFT;
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_OKAY));
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_ghost down") {
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, WALL,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = DOWN;
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_OKAY));
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_ghost up") {
    int ghost_y = 2;
    int ghost_x = 0;
    char tiny_map[] = {WALL, DOT,
                       DOT, DOT,
                       GHOST, DOT};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {WALL, DOT,
                           DOT, DOT,
                           EMPTY, DOT};
    dot_map = tiny_dot_map;
    char direction = UP;
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_OKAY));
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_WALL));
}


TEST_CASE("A test for invalid direction for move_ghost") {
    int ghost_y = 0;
    int ghost_x = 0;
    char tiny_map[] = {GHOST, DOT,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    direction = 'Q';
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'L';
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'Z';
    CHECK((move_ghost(&ghost_y, &ghost_x, direction) == MOVED_INVALID_DIRECTION));
}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// Test check_win for game in progress and win condition
TEST_CASE("A test for check_win") {
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    CHECK((check_win() == KEEP_GOING));

    // Reset map dimensions and dot_map for win condition
    height = 2;
    width = 2;
    char empty_tiny_dot_map[] = {EMPTY, EMPTY,
                                 EMPTY, EMPTY};
    dot_map = empty_tiny_dot_map;
    CHECK((check_win() == YOU_WIN));
}

// Test check_loss for player colliding with first ghost
TEST_CASE("Player loses by hitting a ghost") {
    int player_y = 1;
    int player_x = 1;
    int ghosts_y[NUM_GHOSTS] = {1, 3};
    int ghosts_x[NUM_GHOSTS] = {1, 4};

    // Player at (1,1) collides with ghost at (1,1)
    CHECK(check_loss(player_y, player_x, ghosts_y, ghosts_x) == 1);
}

// Test check_loss for player colliding with ghost at specific coordinates
TEST_CASE("Player collides with a ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 4};
    int ghosts_x[NUM_GHOSTS] = {3, 5};

    CHECK(check_loss(2, 3, ghosts_y, ghosts_x) == 1);
}

// Test check_loss for player not colliding with any ghost
TEST_CASE("Player does not collide with any ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 4};
    int ghosts_x[NUM_GHOSTS] = {3, 5};

    CHECK(check_loss(1, 1, ghosts_y, ghosts_x) == 0);
}

// Test check_loss for player colliding with second ghost
TEST_CASE("Player collides with another ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 6};
    int ghosts_x[NUM_GHOSTS] = {3, 7};

    CHECK(check_loss(6, 7, ghosts_y, ghosts_x) == 1);
}

TEST_SUITE_END();