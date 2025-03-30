#include <stdio.h>
#include <math.h>

int main(void) {
// declare variable for population
int initialPopulation;
int day = 1;
while (1) {
    printf("What is the initial population?\n");
    scanf("%d", &initialPopulation);
    if (initialPopulation >= 100 && initialPopulation <= 500) {
        break;
    } else {
        printf("The initial population given is incorrect\n");
        }
}
float totalPopulation = 0;
float currentPopulation = initialPopulation;
    for (;day <= 50; day++) {
        if (day%3 == 0){
            currentPopulation = round(currentPopulation*0.5);
        } else {
            currentPopulation = round(currentPopulation*1.66);
        }
        totalPopulation = totalPopulation+currentPopulation;
    }
printf("The population after 50 days is %.0f\n", currentPopulation);
while (currentPopulation >= 100) {
    currentPopulation = round(currentPopulation*0.84);
    day++;
    totalPopulation += currentPopulation;
}
printf("After %d days the population will return below 100\n", day);
float averagePopulation = ((float)totalPopulation)/day;
printf("On average there were %.2f cells in the colony\n", averagePopulation);

return 0;
}
