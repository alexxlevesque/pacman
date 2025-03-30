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

void print_map(void) {

    // start count, print full line of walls
    int count = 0;
    for (int i = 0; i < 11; i++) {
        printc(WALL);
        printf(" ");
    }

    // print new line, and first left-side wall barrier
    printf("\n");
    printc(WALL);
    printf(" ");

    // loop and print all characters in map array, while increasing a count
    for (int i = 0; i < 81; i++){
        printc(map[i]);
        printf(" ");
        count++;

        // if count is 9, meaning end of row, print a new line, a left-side wall barrier, and reset count
        if (count == 9) {
            printc(WALL);
            printf("\n");
            printc(WALL);
            printf(" ");
            count = 0;
        }
    }

    // print full line of walls
    for (int i = 0; i < 10; i++) {
        printc(WALL);
        printf(" ");
    }
    printf("\n");
}

//    FILE *fp;
//    fp = fopen("map.txt", "r");
//
//    char** arr = (char**)malloc(9*sizeof(char*));
//    for (int i = 0; i < 9; i++) {
//        arr[i] = (char*)malloc(9*sizeof(char));
//    }
//
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 24; j++) {
//            fscanf(fp, "%c", &arr[i][j]);
//            printf("%1c", arr[i][j]);
//        }
//    }
////    printc(PLAYER);
//
//    free(arr);
//    fclose(fp);

int is_wall(int y, int x) {
    if(y < 0 || y == height || x < 0 || x >= width) {
        return YES_WALL;
    }

    return (map[y*width + x] == WALL) ? YES_WALL : NOT_WALL;
}

char * load_map(char * filename, int *map_height, int *map_width) {
    return NULL;
}
