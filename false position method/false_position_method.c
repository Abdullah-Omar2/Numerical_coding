#include <stdio.h>
#include <math.h>

#define TOLERANCE 0.000001
#define MAX_ITER 100

// Global variable to store the selected function choice
int selectedFunction;

// Function definition with a switch statement to choose the function based on selectedFunction
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

// Function to perform the False Position method
void false_position(double a, double b) {
    if (function(a) * function(b) >= 0) {
        printf("Incorrect initial interval.\n");
        return;
    }

    double x, fx;
    int n = 0;

    printf("n\t   x\t\tf(x)\n");
    printf("------------------------------------\n");
    printf("%d\t%.6f\t%.6f\n", n, a, function(a));
    printf("%d\t%.6f\t%.6f\n", n + 1, b, function(b));

    do {
        // Calculate the intersection point using False Position formula
        x = (a * function(b) - b * function(a)) / (function(b) - function(a));
        fx = function(x);

        // Print the current values of n, x, and f(x)
        printf("%d\t%.6f\t%.6f\n", n + 2, x, fx);

        // Check if we've found the root or if the approximation is close enough
        if (fabs(fx) < TOLERANCE) {
            break;
        }

        // Update interval
        if (function(a) * fx < 0) {
            b = x;
        } else {
            a = x;
        }

        n++;
    } while (n < MAX_ITER);

    printf("\nRoot found: x = %.6f, f(x) = %.6f after %d iterations\n", x, fx, n + 2);
}

int main() {
    double a, b;

    // Select the function to use
    selectFunction();

    // Prompt user for the interval
    printf("Enter the interval [a, b]:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);

    // Call the false position method
    false_position(a, b);

    return 0;
}
