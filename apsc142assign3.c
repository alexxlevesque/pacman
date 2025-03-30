#include <stdio.h>

// define rows and columns
#define ROWS 5
#define COLS 6

// declare functions
void populateArray(double array[], double start, double end, int N);
void populatePaceTable(double paceTable[ROWS][COLS], double pacesInMinutes[ROWS], double distances[COLS]);
void timeToString(char timeString[], double timeInMinutes);
void printPaceTable(double paceTable[ROWS][COLS], double distances[]);
void printPaceTable2(double paceTable[ROWS][COLS], double distances[]);

// main function to generate output from testing functions, code was given
int main() {
    double distances[COLS] = {1.0, 2.0, 5.0, 10.0, 21.1, 42.2}; // initializing distances array
    double pacesInMinutes[ROWS]; // initializes paces array
    double paceTable[ROWS][COLS]; // initializes 2d array for the table
    populateArray(pacesInMinutes, 6.0, 4.0, ROWS); // tries populateArray function with start and end values
    populatePaceTable(paceTable, pacesInMinutes, distances); // fills table using populatePaceTable with paces and distances
    printPaceTable(paceTable, distances); // prints first table using test function
    printPaceTable2(paceTable, distances); // prints second table using test function
    return 0;
}

void populateArray(double array[], double start, double end, int N){ // populates 1d array with evenly spaces values from set start and end
    double increment = (end-start)/(N-1); // creates increment step using the difference in end and start
    for (int i = 0; i < N; i++) { // loop through each index of array
        array[i] = start + i*increment; // compute value at each index
    }
}
void populatePaceTable(double paceTable[ROWS][COLS], double pacesInMinutes[ROWS], double distances[COLS]){ // populates 2d array while computing with paces and distances
    for (int i = 0; i < ROWS; i++) { // loop through each index in paces
        for (int j = 0; j < COLS; j++) { // loop through each index in distances
            paceTable[i][j] = pacesInMinutes[i]*distances[j]; // computes and stores values for each pace and distance
        }
    }
}
void timeToString(char timeString[], double timeInMinutes){ // function to convert hours, minutes, and seconds to h:mm:ss
    int tmi = (int) timeInMinutes; // converts timeInMinutes into an integer, removing any decimals or seconds
    int hours = tmi / 60; // divides tmi by 60 to get hours as an int
    timeString[0] = '0' + hours; // start at 0, and add hours to then be printed, assume hours < 10 to prevent weird ascii
    int minutes = tmi % 60; // gets remainder (tmi modulus 60), stored as an integer
    timeString[2] = '0' + (minutes/10); // start at 0, then add minutes divided by 10 as "tens" place of minutes
    timeString[3] = '0' + (minutes%10); // start at 0, then add minutes modulus 10 as "ones" place of minutes
    int seconds = (int)((timeInMinutes - tmi) * 60); // takes the decimals of timeInMinutes and converts to seconds
    timeString[5] = '0' + (seconds/10); // start at 0, then add seconds divided by 10 as "tens" place of seconds
    timeString[6] = '0' + (seconds%10); // start at 0, then add seconds modulus 10 as "ones" place of seconds
}

void printPaceTable(double paceTable[ROWS][COLS], double distances[]) { // given test function 1
    printf("This is the time in minutes that it would take to complete each distance:\n");
    for (int j = 0; j < COLS; j++) {
        printf("%5.1f km\t", distances[j]);
    }
    printf("\n----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%5.2f\t\t", paceTable[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void printPaceTable2(double paceTable[ROWS][COLS], double distances[]) { // given test function 2
    char timeString[] = "0:00:00";//A placeholder string for when the minutes are converted to h:mm:ss format
    printf("This is the time in h:mm:ss that it would take to complete each distance:\n");
    for (int j = 0; j < COLS; j++) {//using j for COLS but does not matter
        printf("%5.1f km\t", distances[j]);
    }
    printf("\n----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            timeToString(timeString, paceTable[i][j]);
            printf("%s\t\t", timeString);
        }
        printf("\n");
    }
    printf("\n");
}