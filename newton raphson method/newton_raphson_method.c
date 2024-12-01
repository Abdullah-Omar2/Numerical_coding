#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPSILON 1e-6 // Precision of the root
#define MAX_ITER 100 // Maximum number of iterations

// Function prototypes
double f(double x);      // The selected function f(x)
double f_prime(double x); // The derivative f'(x)

int selected_function = 0; // Global variable to store user's choice

// Function selection
void select_function() {
    printf("Select a function:\n");
    printf("1. f(x) = x^2 - 8x + 5\n");
    printf("2. f(x) = sin(x) - 0.5\n");
    printf("3. f(x) = e^x - 3x\n");
    printf("4. f(x) = log(x) - 2\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &selected_function);

    if (selected_function < 1 || selected_function > 4) {
        printf("Invalid choice. Exiting.\n");
        exit(1);
    }
}

// Define the function f(x) based on user's selection
double f(double x) {
    switch (selected_function) {
        case 1: return x * x - 8 * x + 5; // x^2 - 8x + 5
        case 2: return sin(x) - 0.5;      // sin(x) - 0.5
        case 3: return exp(x) - 3 * x;   // e^x - 3x
        case 4: return log(x) - 2;       // log(x) - 2
        default: return 0;               // Should not reach here
    }
}

// Define the derivative f'(x) based on user's selection
double f_prime(double x) {
    switch (selected_function) {
        case 1: return 2 * x - 8;        // Derivative of x^2 - 8x + 5
        case 2: return cos(x);           // Derivative of sin(x) - 0.5
        case 3: return exp(x) - 3;       // Derivative of e^x - 3x
        case 4: return 1 / x;            // Derivative of log(x) - 2
        default: return 0;               // Should not reach here
    }
}

// Newton-Raphson implementation
void newton_raphson(double x0) {
    double x = x0;
    int iter = 0;

    printf("\nNewton-Raphson Method:\n");
    printf("--------------------------------------\n");
    printf("| Iteration |     x     |   f(x)   |  f'(x)   |\n");
    printf("--------------------------------------\n");

    while (iter < MAX_ITER) {
        double fx = f(x);
        double fpx = f_prime(x);

        // Print the current iteration, x, f(x), and f'(x)
        printf("| %9d | %9.6f | %8.6f | %8.6f |\n", iter, x, fx, fpx);

        if (fabs(fx) < EPSILON) { // Root found
            printf("--------------------------------------\n");
            printf("Root found: x = %9.6f\n", x);
            return;
        }

        if (fabs(fpx) < EPSILON) { // Avoid division by zero
            printf("--------------------------------------\n");
            printf("Derivative near zero. No solution.\n");
            return;
        }

        // Update x using Newton-Raphson formula
        x = x - fx / fpx;
        iter++;
    }

    printf("--------------------------------------\n");
    printf("Maximum iterations reached. Solution may not converge.\n");
}

int main() {
    double initial_guess;

    // Ask the user to select a function
    select_function();

    // Get the initial guess from the user
    printf("Enter initial guess for the root: ");
    scanf("%lf", &initial_guess);

    // Perform Newton-Raphson method
    newton_raphson(initial_guess);

    return 0;
}
