#include <stdio.h>
#include <math.h>


int main(void) {
    //Declare question and flowers as char and int
    char question;
    int flowers;
    int cost = 0;

    //Ask user what they would like us to help them with today and list questions
    printf("What would you like us to help you with today?\n");
    printf("A: What are your hours?\n");
    printf("B: How long will it take my flowers to be ready?\n");
    printf("C: How much will my order cost?\n");

    //Read user input
    scanf("%c", &question);

    //Create a switch statement for each answer to the question
    switch (question) {
        case 'A':
            //Print the shop's hours
            printf("The flower shop is open Monday-Friday 10-7, and Saturday-Sunday 10-4\n");
            break;
        case 'B':
            //Ask the user how many flowers they would like to order
            printf("How many flowers would you like to order?\n");
            scanf("%d", &flowers);

            //Determine how long the order will cost depending on flowers
            if (flowers <= 5)
                printf("Your order will take 1 business day\n");

            else if (flowers <= 10)
                printf("Your order will take 3 business days\n");

            else if (flowers <= 20)
                printf("Your order will take 5 business days\n");

            else
                printf("Your order will take 10 business days\n");

            break;

        case 'C':
            //Ask the user how many flowers they would like to order
            printf("How many flowers would you like to order?\n");
            scanf("%d", &flowers);

            //Determine how much the order will cost
            if (flowers <= 5)
                cost = flowers * 4;

            else if (flowers <= 10)
                cost = (5*4) + ((flowers - 5) * 3);

            else if (flowers <= 20)
                cost = (5*4) + (5*3) + ((flowers - 10) * 2);

            else
                cost = (5*4) + (5*3) + (5*2) + (flowers - 20);
            printf("Your order will cost $%d\n", cost);
            break;

        default:
            printf("That is not a valid question\n");
            break;
    }
    return 0;
}
