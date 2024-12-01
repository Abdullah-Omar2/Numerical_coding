#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Function pointers for f(x) and g(x)
double (*f)(double);
double (*g)(double);

// Define some example functions
double f1(double x) { return pow(x, 3) - 8 * x + 5; }  // f(x) = x^3 - 8x + 5
double g11(double x) { return cbrt(8 * x - 5); }        // g(x) = ∛(8x - 5)
double g12(double x) { return (pow(x, 3) +5)/8; }        

double f2(double x) { return sin(x) - x / 2; }         // f(x) = sin(x) - x/2
double g21(double x) { return 2 * sin(x); }            // g(x) = 2sin(x)
double g22(double x) { return asin(x/2); }           


// Tolerance and iteration limit
#define TOLERANCE 1e-5
#define MAX_ITERATIONS 100

int main() {
    int fChoice, gChoice;  // Function choices
    double x0, x1;         // Initial guess and next value
    int iter = 0;

    // Ask the user to choose the function f(x)
    printf("Choose a function f(x):\n");
    printf("1. f(x) = x^3 - 8x + 5\n");
    printf("2. f(x) = sin(x) - x/2\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &fChoice);

    // Assign the chosen f(x)
    switch (fChoice) {
        case 1: 
		f = f1; 
		 printf("\nChoose a function g(x) for fixed-point iteration:\n");
    printf("1. g(x) = ∛(8x - 5)\n");
    printf("2. g(x) = (x^3 + 5) / 8\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &gChoice);

    // Assign the chosen g(x)
    switch (gChoice) {
        case 1: g = g11; break;
        case 2: g = g12; break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
		break;
        case 2: 
		f = f2; 
		printf("\nChoose a function g(x) for fixed-point iteration:\n");
    printf("1. g(x) = 2sin(x)\n");
    printf("2. g(x) = sin^-1(x/2)\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &gChoice);

    // Assign the chosen g(x)
    switch (gChoice) {
        case 1: g = g21; break;
        case 2: g = g22; break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
		break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

   

    // Ask the user for the initial guess
    printf("\nEnter the initial guess x0: ");
    scanf("%lf", &x0);

    printf("\nIter\t\tx\n");
    printf("---------------------------\n");

    // Perform the fixed-point iteration
    do {
        x1 = g(x0);  // Compute next iteration
        printf("%d\t\t%.6lf\n", iter, x1);  // Print the current iteration
        iter++;

        // Check for convergence
        if (fabs(x1 - x0) < TOLERANCE) {
            printf("\nRoot found: %.6lf\n", x1);
            return 0;
        }

        x0 = x1;  // Update x0 for the next iteration
    } while (iter < MAX_ITERATIONS);

    // If the loop exits without convergence
    printf("\nMethod did not converge within %d iterations.\n", MAX_ITERATIONS);
    return 1;
}
