// Include necessary libraries for printing and math
#include <math.h>
#include <stdio.h>

// I attest to the originality of my work.

// Declare functions
double expSquared (double x);
double inverseFactorial (int n);
double taylorSeries (double x, int numTerms);
double integralTaylorSeries (double lowerLimit, double upperLimit, int numTerms);
double riemannSum (double lowerLimit, double upperLimit, int numRectangles);

int main() {
    printf("What would you like to calculate?\n"
           "A: Analytical result of e^x^2\n"
           "B: Inverse factorial\n"
           "C: Taylor series approximation of e^x^2\n"
           "D: Analytic integral of the Taylor series approximation of e^x^2\n"
           "E: Riemann sum of e^x^2\n");
    char choice;
    scanf("%c", &choice);
    if (choice == 'A') {
        double inputs_a[5] = {-3.0, -1.5, 0.0, 0.5, 2.0};
        double results_a[5];
        for (int i = 0; i < 5; i++) {
            results_a[i] = expSquared(inputs_a[i]);
        }
        printf("x        | e^(x^2)\n");
        printf("-------------------\n");
        for (int i = 0; i < 5; i++) {
            printf("%-8.1f | %-10.4f\n", inputs_a[i], results_a[i]);
        }
        return 0;
    }

    if (choice == 'B') {
        int inputs_b[5] = {0, 1, 3, 5, 10};
        double results_b[5];
        for (int i = 0; i < 5; i++) {
            results_b[i] = inverseFactorial(inputs_b[i]);
        }
        // print table and display results
        printf("x        | 1/n!\n");
        printf("-------------------\n");
        for (int i = 0; i < 5; i++) {
            printf("%-8.0d | %-10.4f\n", inputs_b[i], results_b[i]);
        }
        return 0;
    }

    if (choice == 'C') {
        double inputs_c[8] = {-3.0, -1.5, -1.5, -1.5, -1.5, 0.0, 0.5, 2.0};
        int numTerms_c[8] = {100, 3, 5, 10, 100, 100, 100, 100};
        double results_c[8];
        for (int i = 0; i < 8; i++) {
            results_c[i] = taylorSeries(inputs_c[i], numTerms_c[i]);
        }
        printf("x        | numTerms |   taylorSeries\n");
        printf("-----------------------------------\n");
        for (int i = 0; i < 8; i++) {
            printf("%-8.1f | %-9.0d | %-10.4f\n", inputs_c[i], numTerms_c[i], results_c[i]);
        }
        return 0;
    }

    if (choice == 'D') {
        double lowerLimit_d[5] = {-2, -2, -2, -2, -0.5};
        double upperLimit_d[5] = {0, 0, 0, 0, 1.5};
        int numTerms_d[5] = {3, 5, 10, 100, 100};
        double results_d[5];
        for (int i = 0; i < 5; i++) {
            results_d[i] = integralTaylorSeries(lowerLimit_d[i], upperLimit_d[i], numTerms_d[i]);
        }
        printf("lowerLimit  |  upperLimit  |  numTerms |  integralTaylorSeries\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < 5; i++) {
            printf("%-8.1f | %-9.1f | %-10.0d | %-12.4f \n", lowerLimit_d[i], upperLimit_d[i], numTerms_d[i], results_d[i]);
        }
        return 0;
    }

    if (choice == 'E') {
        double lowerLimit_e[5] = {-2, -2, -2, -2, -0.5};
        double upperLimit_e[5] = {0, 0, 0, 0, 1.5};
        int numRectangles[5] = {3000, 5000, 10000, 100000, 100000};
        double results_e[5];
        for (int i = 0; i < 5; i++) {
            results_e[i] = riemannSum(lowerLimit_e[i], upperLimit_e[i], numRectangles[i]);
        }
        printf("lowerLimit  |  upperLimit  |  numTerms |  integralTaylorSeries\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < 5; i++) {
            printf("%-8.1f | %-9.0f | %-10.4d | %-12.4f \n", lowerLimit_e[i], upperLimit_e[i], numRectangles[i], results_e[i]);
        }
        return 0;
    }
}

// Function to compute e^(x^2)
double expSquared (double x) {
    double exp_a = pow(x,2);        // Compute x^2 and store it in exp_a
    double output_a = exp(exp_a);   // Compute e^(x^2) and store in output_a
    return output_a;                // Return the result
}

// Function to compute the inverse factorial 1/n!
double inverseFactorial (int n) {
    double output_b = 1;            // Initialize the result to 1
    for (int i = 1; i <= n; i++) {  // Loop from 1 to n
        output_b *= i;              // Multiply the result by i to compute n!
    }
    output_b = 1/output_b;          // Compute the inverse factorial 1/n!
    return output_b;                // Return the Inverse Factorial
}

// Function to approximate e^(x^2) using the Taylor series
double taylorSeries (double x, int numTerms) {
    double output_c = 0;            // Initialize result
    for (int i = 0; i<numTerms; i++) {                  // Loop to compute the Taylor series sum
        double taylor = inverseFactorial(i) * pow(x, 2 * i);    // Compute the i-th term of the series(x^(2*i)/i!
        output_c += taylor;                             // Add the term to the result
    }
    return output_c;                                    // Return the Taylor series approximation
}

// Function to compute the integral of the Taylor series approximation of e^(x^2)
// over the range [lowerLimit, upperLimit]
double integralTaylorSeries (double lowerLimit, double upperLimit, int numTerms) {
    double output_d = 0, termA, termB;      // Initialize output and two terms for intermediate calculations
    for (int i = 0; i < numTerms; i++) {    // Loop to compute the integral
        termA = pow(upperLimit, 2*i + 1)/(2*i + 1)     // Compute based on Equation 4
                - pow(lowerLimit, 2*i + 1)/(2*i + 1);
        termB = inverseFactorial(i) * termA;                // Compute based on Equation 4
        output_d += termB;                             // Add intermediate result to the final output
    }
    return output_d;                                   // Return the integral of the Taylor series approximation
}

// Function to calculate the Riemann sum of the given function
// over the range [lowerLimit, upperLimit]
double riemannSum (double lowerLimit, double upperLimit, int numRectangles) {
    double output_e = 0, deltaX;                        // Initialize the Riemann sum result
    deltaX = (upperLimit - lowerLimit)/numRectangles;   // Variable to store the width of the rectangles
    for (int i = 0; i < numRectangles; i++) {           // Loop to calculate the sum of the rectangle areas
        double xi = lowerLimit + i*deltaX;              // Calculate the left side x-coordinate
        output_e += expSquared(xi)*deltaX;              // Calculate the area of the rectangle and add it to the total
    }
    return output_e;                                    // Return the final Riemann sum
}