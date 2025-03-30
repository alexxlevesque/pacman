#include <stdio.h>
#include <math.h>

#define cookieD 5.5
#define cookieH 1.25

int main() {
    //Assign Variables
    float L, W, H;
    //Get input from user
    printf("Input the length, width, height of the cookie box in cm");
    scanf("%f %f %f", &L, &W, &H);
    //Calculate Surface Area of the Box
    float SA = 2*(L*W + W*H + H*L);
    //Calculate cost of cardboard
    float cost = SA*0.002;
    //Calculate the volume of one cookie
    float cookieV = M_PI * pow((cookieD/2),2)*cookieH;
    // Calculate how many cookies fit per layer
    int cookiesPerLayer = (int)(L/cookieD) * (int)(W/cookieD);
    // Calculate how many layers fit in the height
    int layers = (int)(H / cookieH);
    // Calculate the total number of cookies
    int numC = cookiesPerLayer * layers;
    //Calculate the cost of a cookie
    float cookieC = cookieV*0.012;
    //Calculate total cookie cost
    float c = numC * cookieC;
    //Calculate total cost including cardboard
    float totalC = c + cost;
    //Calculate selling price with profit margin
    float price = totalC * 1.1;
    //Print final values
    printf("The cost of cardboard for the box is %.2f\n", cost);
    printf("%d cookies fit in the box\n", numC);
    printf("The cost to make the cookies is %.2f\n", c);
    printf("The total cost of the box of cookies is %.2f\n", totalC);
    printf("The box of cookies should be sold for %.2f\n", price);
    return 0;
}