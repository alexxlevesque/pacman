// This code was written only by me and is my own work
// include necessary libraries and constants
#include <stdio.h>
#include <stdlib.h>
#define COLS 5
#define TOTALROWS 8

int main(void) {
    // open file from path, read file
    FILE *fp = fopen("houses.txt", "r");

    // check if file exists, exit code if not
    if (fp == NULL) {
        printf("File not found.");
        return 1;
    }

    // if first number on first line doesn't exist or is 0, exit code
    int numHouses;
    if (fscanf(fp, "%d", &numHouses) != 1 || numHouses == 0) {
        printf("No houses in the fie.");
        return 1;
    }

    // allocate memory to 2D array's rows, the loop for each col of each row
    int **pArray = (int **) malloc (TOTALROWS*sizeof(int*));
    for (int i = 0; i < TOTALROWS; i++) {
        pArray[i] = (int *)malloc(COLS*sizeof(int));
    }

    //  iteratee through columns with house numbers
    for (int i = 0; i < numHouses; i++) {

        // read numbers on each of the file's rows and columns, insert in array
        fscanf(fp, "%d %d %d", &pArray[i][0], &pArray[i][1], &pArray[i][2]);

        // calculate average income within loop for each row, pointers for readability
        int* numOfPeople = &pArray[i][1];
        int* totalAnnualIncome = &pArray[i][2];
        int* averageIncome = &pArray[i][3];

        // default 5th column value, might be changed later from linear search
        pArray[i][4] = 0;

        // calculate and store average income
        *averageIncome = *totalAnnualIncome / *numOfPeople;
    }

    // fill in last 3 house numbers separately to avoid any memory issues
    for (int i = numHouses; i < TOTALROWS; i++) {
        fscanf(fp, "%d", &pArray[i][0]);
        pArray[i][1] = 0;
        pArray[i][2] = 0;
        pArray[i][3] = 0;
        pArray[i][4] = 0;
    }

    // create count to determine number of valid rows, and rows in newArray
    int count = 0;

    // implement linear search algorithm to search for duplicate house number values
    for (int i = 0; i < numHouses; i++) {
        // get house number from column i
        int houseNumber = pArray[i][0];

        // find duplicate using variation of linear search algorithm
        for (int j = 0; j < TOTALROWS; j++) {

            // condition to avoid case where i = j
            if (i != j && pArray[j][0] == houseNumber) {
                pArray[i][4] = 1;
                count++;
                break;
            }
        }
    }

    // print data to console
    for (int i = 0; i < numHouses; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", pArray[i][j]);
        }
        printf("\n");
    }

    // make new array and allocate memory
    int **newArray = (int **) malloc (count*sizeof(int*));
    for (int i = 0; i < count; i++) {
        newArray[i] = (int *)malloc(COLS*sizeof(int));
    }

    // create valid row index count, applicable in new Array, and increases when a row has fifth column value of 1
    int validRowIndex = 0;
    // use loop to put values in new array if fifth column = 1
    for (int i = 0; i < TOTALROWS; i++){
        if (pArray[i][4] == 1) {
            for (int j = 0; j < COLS; j++) {
                newArray[validRowIndex][j] = pArray[i][j];
            }
            validRowIndex++;
        }
    }

    // sort newArray based on the magnitude of the average income
    // outer loop runs (count - 1) times
    for (int i = 0; i < count - 1; i++) {

        // inner loop compares and swaps rows if needed
        for (int j = 0; j < count - i - 1; j++) {

            // if column 3 value is greater than the next row's, swap them
            if (newArray[j][3] > newArray[j + 1][3]) {

                // Swap entire rows using pointers
                int *temp = newArray[j];
                newArray[j] = newArray[j + 1];
                newArray[j + 1] = temp;
            }
        }
    }

    // create editable file sorted.txt
    FILE *fp2 = fopen("sorted.txt", "w");

    // add column 0 values for sorted array
    for (int i = 0; i < count; i++) {
        fprintf(fp2, "%d\n", newArray[i][0]);
    }

    // free allocated memory for pArray for each row
    for (int i = 0; i < TOTALROWS; i++) {
        free(pArray[i]);
    }

    // free allocated memory for newArray for each row
    for (int i = 0; i < count; i++) {
        free(newArray[i]);
    }

    // free allocated memory for the array of row pointers
    free(pArray);
    free(newArray);

    // close files
    fclose(fp);
    fclose(fp2);
    return 0;
}
