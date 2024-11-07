#include <stdio.h>
#include <math.h>

// Function prototypes
double function(double x);
void selectFunction();
void bisection(double a, double b, double tolerance, int max_iterations);

// Global variable to hold the selected function
int selectedFunction = 0;

// Define different functions for demonstration
double function(double x) {
    switch (selectedFunction) {
        case 1: return x * x * x - 8*x + 5;                  // Example: x^3 - 8x + 5
        case 2: return x * x * x * x - 12 * x * x -10;           // Example: x^4 - 12x^2 - 10
        case 3: return x - exp(-x);                          // Example: x-e^-x
        case 4: return 4 * exp(-x) * sin(x) - 1;             // Example: 4e^-x * sin(x) -1
		default: return x * x * x - x - 1;          // Default: x^3 - x - 1
    }
}

// Function to select which function to use
void selectFunction() {
    printf("Select a function to find its root:\n");
    printf("1. f(x) = x^3 - 8x + 5\n");
    printf("2. f(x) = x^4 - 12x^2 - 10\n");
    printf("3. f(x) = x-e^-x\n");
	printf("4. f(x) = 4e^-x * sin(x) -1\n");
    printf("Enter choice (1, 2, 3 or 4): ");
    scanf("%d", &selectedFunction);
}

// Bisection method function
void bisection(double a, double b, double tolerance, int max_iterations) {
    double x, f_x, f_a, f_b;
    int n = 1;

    printf("n\t   a(+)    \t    b(-)    \t    x      \t     f(x)\n");
    printf("-------------------------------------------------------------\n");

    do {
        x = (a + b) / 2.0;     // Midpoint
        f_x = function(x);      // Value of function at x
        f_a = function(a);
        f_b = function(b);

        printf("%d\t%.6f\t%.6f\t%.6f\t%.6f\n", n, a, b, x, f_x);

        // Check which subinterval contains the root
        if (f_a * f_x < 0) {
            b = x;
        } else {
            a = x;
        }

        // Increment iteration count
        n++;

        // Stop if tolerance is met or max iterations reached
    } while (fabs(f_x) > tolerance && n <= max_iterations);

    printf("-------------------------------------------------------------\n");
    printf("Approximate root after %d iterations: %.6f\n", n-1, x);
}

int main() {
    double a, b, tolerance;
    int max_iterations;

    // Allow user to select the function
    selectFunction();

    // Get the interval and other parameters from the user
    printf("Enter the start of the interval (a): ");
    scanf("%lf", &a);
    printf("Enter the end of the interval (b): ");
    scanf("%lf", &b);
    printf("Enter the tolerance: ");
    scanf("%lf", &tolerance);
    printf("Enter the maximum number of iterations: ");
    scanf("%d", &max_iterations);

    // Check if root lies in the interval [a, b]
    if (function(a) * function(b) >= 0) {
        printf("The function does not have a root in the interval [%.2f, %.2f].\n", a, b);
    } else {
        bisection(a, b, tolerance, max_iterations);
    }

    return 0;
}
