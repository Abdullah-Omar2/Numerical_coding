#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TOLERANCE 1e-9
#define MAX_ITER 100

// Define a global variable to hold the selected function type
int selectedFunction;

// Function prototypes for predefined functions
double f1(double x); // f(x) = x^3 - 8x + 5
double f2(double x); // f(x) = x - e^(-x)
double f3(double x); // f(x) = sin(x) - x/2

// General function pointer for the selected function
double (*f)(double);

// Function to calculate f(x) for the user-defined polynomial
double userDefinedFunction(double x) {
    static double coefficients[10];
    static int degree = -1;

    // Initialize the polynomial coefficients if not done yet
    if (degree == -1) {
        printf("Enter the degree of the polynomial: ");
        scanf("%d", &degree);
        printf("Enter the coefficients (from highest to lowest degree):\n");
        for (int i = 0; i <= degree; i++) {
            printf("Coefficient of x^%d: ", degree - i);
            scanf("%lf", &coefficients[i]);
        }
    }

    // Evaluate the polynomial using Horner's method
    double result = coefficients[0];
    for (int i = 1; i <= degree; i++) {
        result = result * x + coefficients[i];
    }
    return result;
}

// Secant Method implementation
void secantMethod(double a, double b) {
    double x0 = a, x1 = b, x2, fx0, fx1, fx2;
    int iteration = 0;

    printf("n\t\tx\t\tf(x)\n");
    printf("%d\t\t%.9lf\t%.9lf\n", iteration++, x0, f(x0));
    printf("%d\t\t%.9lf\t%.9lf\n", iteration++, x1, f(x1));

    do {
        fx0 = f(x0);
        fx1 = f(x1);

        // Calculate next approximation using the Secant Method formula
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        fx2 = f(x2);

        printf("%d\t\t%.9lf\t%.9lf\n", iteration++, x2, fx2);

        // Update values for the next iteration
        x0 = x1;
        x1 = x2;

    } while (fabs(fx2) > TOLERANCE && iteration < MAX_ITER);

    printf("Approximate root correct to 9 decimal places is %.9lf\n", x2);
}

int main() {
    double a, b;

    printf("Select the function:\n");
    printf("1. f(x) = x^3 - 8x + 5\n");
    printf("2. f(x) = x - e^(-x)\n");
    printf("3. f(x) = sin(x) - x/2\n");
    printf("4. Enter a custom polynomial\n");
    printf("Enter your choice: ");
    scanf("%d", &selectedFunction);

    switch (selectedFunction) {
        case 1:
            f = f1;
            break;
        case 2:
            f = f2;
            break;
        case 3:
            f = f3;
            break;
        case 4:
            f = userDefinedFunction;
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    printf("Enter the interval [a, b]:\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);

    printf("\nFinding root in the interval [%.9lf, %.9lf]\n\n", a, b);
    secantMethod(a, b);

    return 0;
}

// Predefined functions
double f1(double x) {
    return pow(x, 3) - 8 * x + 5;
}

double f2(double x) {
    return x - exp(-x);
}

double f3(double x) {
    return sin(x) - x / 2;
}
