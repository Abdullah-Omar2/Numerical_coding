#include <stdio.h>
#include <math.h>

// Function to calculate factorial
int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Function to calculate the value of y using Gauss forward interpolation
double gaussForwardInterpolation(double x[], double y[][10], int n, double value) {
    double h = x[1] - x[0]; // Interval size
    double p = (value - x[0]) / h;
    double result = y[0][0]; // First y value

    // Applying Gauss's formula
    double p_term = 1.0; // To store the cumulative p(p-1)(p-2)...
    for (int i = 1; i < n; i++) {
        p_term *= (p - (i - 1));
        result += (p_term * y[0][i]) / factorial(i);
    }
    return result;
}

int main() {
    int n; // Number of data points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[n], y[n][10]; // x values and forward difference table

    // Reading x and y values
    printf("Enter the x values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    printf("Enter the y values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i][0]);
    }

    // Creating the forward difference table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
        }
    }

    // Printing the forward difference table
    printf("\nForward Difference Table:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.4lf", x[i]); // x values
        for (int j = 0; j < n - i; j++) {
            printf("%10.4lf", y[i][j]); // y differences
        }
        printf("\n");
    }

    // Interpolation
    double value;
    printf("\nEnter the value of x for which you want to calculate y: ");
    scanf("%lf", &value);

    double result = gaussForwardInterpolation(x, y, n, value);
    printf("The interpolated value of y at x = %.4lf is %.4lf\n", value, result);

    return 0;
}
